/*
 * Dilla4x Firmware
 * Version number is defined in Config.h
 * Designed for Arduino Pro Micro/Leonardo (ATmega32U4) only.
 */

#include <avr/wdt.h>
#include <Control_Surface.h>
#include "Config.h"
#include "Utils.h"
#include "ChordManager.h"
#include "LedController.h"

// ========================================
// GLOBALS
// ========================================

USBMIDI_Interface g_midi;
Transposer<MIN_MIDI_NOTE, MAX_MIDI_NOTE> g_transposer(0);

// NoteButtons array indices must match order of KEY_PINS and BASE_NOTES arrays
// NOTE: Control_Surface library automatically configures pinMode for all NoteButton pins
// when Control_Surface.begin() is called. Explicit pinMode() calls are NOT needed.
Bankable::NoteButton buttons[] = {
  {g_transposer, KEY_PINS[0], {BASE_NOTES[0], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[1], {BASE_NOTES[1], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[2], {BASE_NOTES[2], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[3], {BASE_NOTES[3], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[4], {BASE_NOTES[4], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[5], {BASE_NOTES[5], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[6], {BASE_NOTES[6], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[7], {BASE_NOTES[7], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[8], {BASE_NOTES[8], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[9], {BASE_NOTES[9], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[10], {BASE_NOTES[10], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[11], {BASE_NOTES[11], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[12], {BASE_NOTES[12], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[13], {BASE_NOTES[13], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[14], {BASE_NOTES[14], MIDI_CHANNEL}},
  {g_transposer, KEY_PINS[15], {BASE_NOTES[15], MIDI_CHANNEL}}
};

ChordManager g_chordMgr;
LedController g_led;

// Feedback state: 0 = inactive, >0 = end timestamp
static unsigned long g_feedbackEndTime = 0;

// ========================================
// HELPERS
// ========================================

// Send All Notes Off (CC 123) before octave shifts to prevent stuck notes.
// NOTE: Control_Surface library guarantees MIDI interface is initialized by the time
// this function can be called (it's only called from loop() after Control_Surface.begin()).
void sendAllNotesOff() {
  g_midi.sendControlChange({0x7B, MIDI_CHANNEL}, 0);
}

// ========================================
// LOGIC
// ========================================

void handleOctaveShift(const int8_t direction) {
  const int8_t currentTransposition = g_transposer.getTransposition();
  const int8_t newTransposition = currentTransposition + (direction * SEMITONES_PER_OCTAVE);
  const int8_t newOctave = newTransposition / SEMITONES_PER_OCTAVE;
  
  // Check octave range first (simpler, catches edge cases)
  if (newOctave < MIN_OCTAVE || newOctave > MAX_OCTAVE) return;
  
  sendAllNotesOff();
  g_transposer.setTransposition(newTransposition);
  g_feedbackEndTime = millis() + LED_FEEDBACK_TIMEOUT_MS;
}

// ========================================
// RECOVERY MODE
// ========================================
// DESIGN NOTE: Recovery mode is an infinite loop with NO timeout by design.
// This is intentional - it provides a "safe idle state" for firmware upload when
// the device is soft-bricked due to USB/MIDI stack failure. The only exit is
// power cycle or successful firmware upload. This is NOT a bug.

static bool checkRecoveryMode() {
  // Try Active-Low first (buttons pull to GND with internal pullup)
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) {
    pinMode(RECOVERY_PINS[i], INPUT_PULLUP);
  }
  
  // First read - check if ALL recovery pins are LOW
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) {
    if (digitalRead(RECOVERY_PINS[i]) != LOW) {
      // Not all pins LOW, try Active-High detection
      // NOTE: Active-High detection is commented out until hardware is confirmed.
      // If your buttons connect to VCC (Active-High), uncomment the block below.
      
      /*
      // Try Active-High (buttons pull to VCC, no internal pulldown on 32u4)
      // This requires external pulldown resistors
      for (uint8_t j = 0; j < RECOVERY_PINS_COUNT; j++) {
        pinMode(RECOVERY_PINS[j], INPUT);  // High-Z input
      }
      delay(RECOVERY_DEBOUNCE_MS);
      
      bool allHigh = true;
      for (uint8_t j = 0; j < RECOVERY_PINS_COUNT; j++) {
        if (digitalRead(RECOVERY_PINS[j]) != HIGH) {
          allHigh = false;
          break;
        }
      }
      
      if (allHigh) return true;  // Active-High buttons pressed
      */
      
      return false;  // Neither Active-Low nor Active-High detected
    }
  }
  
  // All pins are LOW - debounce
  delay(RECOVERY_DEBOUNCE_MS);
  
  // Second read - verify all pins still LOW
  for (uint8_t i = 0; i < RECOVERY_PINS_COUNT; i++) {
    if (digitalRead(RECOVERY_PINS[i]) != LOW) return false;
  }
  
  return true;  // Active-Low buttons confirmed
}

// Safe idle state for bootloader access during firmware flashing.
// Blinks TX LED rapidly and exposes CDC Serial (/dev/ttyACM*) for uploads.
// NOTE: This is an infinite loop BY DESIGN. Watchdog is never enabled when this
// function is called (see setup() below), so there is no watchdog reset issue.
void enterRecoveryMode() {
  // Initialize USB Serial (CDC) so device enumerates as /dev/ttyACM*
  // This makes the device flashable via arduino-cli upload or auto_flash.sh
  Serial.begin(9600);
  
  // Initialize LEDs using the same macros as LedController
  TX_RX_LED_INIT;
  RXLED1;  // Keep RX LED off permanently
  
  // Infinite loop with rapid TX LED blink for visual confirmation
  while (true) {
    TXLED0;  // TX LED on
    delay(100);
    TXLED1;  // TX LED off
    delay(100);
    
    // Keep CDC Serial alive by processing any incoming data
    if (Serial.available()) {
      Serial.read();
    }
  }
}

// ========================================
// MAIN
// ========================================

void setup() {
  wdt_disable();
  
  // Initialize pin mappings once at startup
  initPinMappings();
  
  g_led.init();

  // Check for recovery mode BEFORE enabling watchdog or initializing Control_Surface.
  // If recovery mode is active, enterRecoveryMode() never returns (infinite loop),
  // so the watchdog is never enabled and there is no watchdog reset issue.
  if (checkRecoveryMode()) {
    enterRecoveryMode();
  }

  // Control_Surface.begin() initializes MIDI and configures pinMode for all NoteButton pins.
  // Explicit pinMode() calls for KEY_PINS are NOT required.
  Control_Surface.begin();
  
  // Enable watchdog AFTER recovery check. If we're in recovery mode, we never reach here.
  wdt_enable(WDTO_4S);
}

void loop() {
  wdt_reset();
  Control_Surface.loop();
  
  const unsigned long currentMillis = millis();
  const uint16_t pinMask = readPins();
  
  // --- Chord Logic ---
  const ChordEvent event = g_chordMgr.update(currentMillis, pinMask);
  
  // Handle actionable events (OCTAVE_UP/DOWN)
  if (event == ChordEvent::OCTAVE_UP || event == ChordEvent::OCTAVE_DOWN) {
    const int8_t direction = (event == ChordEvent::OCTAVE_UP) ? 1 : -1;
    handleOctaveShift(direction);
  }
  
  // --- LED Logic ---
  LedPattern targetPattern = LedPattern::OFF;
  
  // Feedback (Transient) - use centralized time utility
  // NOTE: timeElapsed() correctly handles millis() wraparound. Setting g_feedbackEndTime
  // to millis() + timeout is safe even near ULONG_MAX because unsigned arithmetic wraps
  // correctly and timeElapsed() uses the (a - b) < ULONG_MAX/2 pattern for comparison.
  if (g_feedbackEndTime != 0) {
    if (timeElapsed(currentMillis, g_feedbackEndTime)) {
      g_feedbackEndTime = 0;  // Expired
    } else {
      targetPattern = LedPattern::BLINK_FAST;
    }
  }
  
  // Active User Input (Meaningful Keys Pressed)
  if (targetPattern == LedPattern::OFF && __builtin_popcount(pinMask) >= MIN_MEANINGFUL_KEYS) {
    targetPattern = LedPattern::ON;
  }
  
  g_led.setPattern(targetPattern, currentMillis);
  g_led.update(currentMillis);
}

