/*
 * Dilla4x Firmware - Zero Latency Implementation
 * Optimized for immediate response and simple feedback.
 */

#include <avr/wdt.h>
#include <MIDIUSB.h>
#include "Config.h"
#include "Utils.h"
#include "ChordManager.h"
#include "LedController.h"

// ========================================
// GLOBALS
// ========================================

// Button state tracking
uint16_t g_lastButtonState = 0;   // The state we last SENT to MIDI
uint16_t g_stableButtonState = 0; // The debounced physical state
unsigned long g_lastDebounceTime[NUM_KEYS] = {0};
constexpr int16_t NOTE_NONE = -1;
int16_t g_activeNotes[NUM_KEYS];

// Octave transposition
int8_t g_octaveOffset = 0; // -3 to +3 octaves

// Modules
ChordManager g_chordMgr;
LedController g_led;

// ========================================
// MIDI HELPERS
// ========================================

// Queue MIDI message (flushed at end of loop)
void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
  midiEventPacket_t noteOn = {0x09, uint8_t(0x90 | (channel & 0x0F)), note, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void sendNoteOff(uint8_t note, uint8_t channel) {
  midiEventPacket_t noteOff = {0x08, uint8_t(0x80 | (channel & 0x0F)), note, 0};
  MidiUSB.sendMIDI(noteOff);
}

void sendAllNotesOff() {
  midiEventPacket_t cc = {0x0B, uint8_t(0xB0 | (MIDI_CHANNEL & 0x0F)), 0x7B, 0};
  MidiUSB.sendMIDI(cc);
}

// ========================================
// LOGIC
// ========================================

void handleButtonChange(uint8_t keyIndex, bool pressed) {
  // Calculate transposed note - clamp to valid MIDI range [0, 127]
  int16_t rawNote = BASE_NOTES[keyIndex] + (g_octaveOffset * SEMITONES_PER_OCTAVE);
  int8_t note = (rawNote < 0) ? 0 : (rawNote > 127 ? 127 : rawNote);
  
  if (pressed) {
    g_activeNotes[keyIndex] = note;
    sendNoteOn(note, 127, MIDI_CHANNEL);
  } else {
    int16_t storedNote = g_activeNotes[keyIndex];
    if (storedNote != NOTE_NONE) {
      sendNoteOff(static_cast<uint8_t>(storedNote), MIDI_CHANNEL);
      g_activeNotes[keyIndex] = NOTE_NONE;
    }
  }
}

void handleOctaveShift(const int8_t direction) {
  const int8_t newOctaveOffset = g_octaveOffset + direction;
  
  if (newOctaveOffset >= MIN_OCTAVE && newOctaveOffset <= MAX_OCTAVE) {
    // Octave takes precedence; shift immediately, then stop any held notes at original pitches
    g_octaveOffset = newOctaveOffset;
    uint16_t heldMask = g_stableButtonState;
    for (uint8_t i = 0; i < NUM_KEYS; i++) {
      if ((heldMask & (1U << i)) == 0) continue;
      int16_t storedNote = g_activeNotes[i];
      if (storedNote != NOTE_NONE) {
        sendNoteOff(static_cast<uint8_t>(storedNote), MIDI_CHANNEL);
        g_activeNotes[i] = NOTE_NONE;
      }
    }
    // Safety CC for hosts that rely on it
    sendAllNotesOff();
    MidiUSB.flush();
  }
}

// ========================================
// RECOVERY MODE (Unchanged)
// ========================================
// ... (Keeping the original recovery mode logic as it was robust)

static bool checkRecoveryMode() {
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) pinMode(RECOVERY_PINS[i], INPUT_PULLUP);
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) if (digitalRead(RECOVERY_PINS[i]) != LOW) return false;
  delay(RECOVERY_DEBOUNCE_MS);
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) if (digitalRead(RECOVERY_PINS[i]) != LOW) return false;
  return true;
}

void enterRecoveryMode() {
  Serial.begin(9600);
  TX_RX_LED_INIT;
  RXLED1;
  while (true) {
    TXLED0; delay(100);
    TXLED1; delay(100);
    if (Serial.available()) Serial.read();
  }
}

// ========================================
// MAIN
// ========================================

void setup() {
  wdt_disable();
  initPinMappings();
  for (uint8_t i = 0; i < NUM_KEYS; i++) pinMode(KEY_PINS[i], INPUT_PULLUP);
  for (uint8_t i = 0; i < NUM_KEYS; i++) g_activeNotes[i] = NOTE_NONE;
  
  g_led.init();
  Serial.begin(115200);

  if (checkRecoveryMode()) enterRecoveryMode();

  wdt_enable(WDTO_4S);
}

void loop() {
  wdt_reset();
  const unsigned long currentMillis = millis();
  
  // 1. Read Inputs
  const uint16_t rawPinMask = readPins();
  
  bool anyActivity = false;
  bool midiTraffic = false;

  // 2. Debounce & Process Keys
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    bool rawState = (rawPinMask & (1U << i)) != 0;
    
    // Check if state changed
    if (rawState != ((g_stableButtonState & (1U << i)) != 0)) {
       // Only process if stable for DEBOUNCE_MS
       if ((currentMillis - g_lastDebounceTime[i]) > DEBOUNCE_MS) {
         g_lastDebounceTime[i] = currentMillis;
         
         if (rawState) {
           g_stableButtonState |= (1U << i);
         } else {
           g_stableButtonState &= ~(1U << i);
         }
       }
    }
    
    // Fire MIDI immediately on state change confirmation
    bool confirmedState = (g_stableButtonState & (1U << i)) != 0;
    bool lastState = (g_lastButtonState & (1U << i)) != 0;
    
    if (confirmedState != lastState) {
      handleButtonChange(i, confirmedState);
      
      if (confirmedState) {
        g_lastButtonState |= (1U << i);
      } else {
        g_lastButtonState &= ~(1U << i);
      }
      midiTraffic = true;
    }
    
    if (confirmedState) anyActivity = true;
  }

  // 3. Absolute Priority: Flush MIDI Traffic BEFORE any other logic
  if (midiTraffic) {
    MidiUSB.flush();
  }

  // 4. Background Chord Check (Does not block MIDI)
  ChordEvent chord = g_chordMgr.update(currentMillis, g_stableButtonState);
  if (chord == ChordEvent::OCTAVE_UP) handleOctaveShift(1);
  if (chord == ChordEvent::OCTAVE_DOWN) handleOctaveShift(-1);

  // 5. Update LEDs (Activity on RX, Octave on TX)
  g_led.setActivity(anyActivity); 
  g_led.setShifted(g_octaveOffset != 0);
}
