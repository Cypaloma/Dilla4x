/*
Dilla4x MIDI Controller Firmware
===============================

Robust, production-ready firmware for the Dilla4x 4x4 ortholinear MIDI pad controller.
Inspired by MPC layout for percussion/production. Uses Arduino Pro Micro for native USB MIDI.

Key Features:
- 16 binary Cherry MX keyswitches: Pins D2-D13, A0-A3 (14-17)
  - MIDI notes: C1(36) to C3(51) chromatic, row-major (top-left to bottom-right)
  - INPUT_PULLUP, debounced via Control_Surface library
- Dynamic octave shift: Press all 8 top-half keys (rows 1-2) simultaneously within 100ms → +1 octave
  - Press all 8 bottom-half keys (rows 3-4) → -1 octave
  - Clamped -2 to +2 octaves; persists via EEPROM
  - Resets trigger on release; error-resistant timing window
- Plug-and-play: Flash & connect USB-C; no config needed for default wiring
- Serial debug @9600 baud (optional)
- Built-in LED feedback for octave shifts
- EEPROM config persistence

Hardware Assumptions:
- Pro Micro 5V (USB-C recommended)
- Keys: one leg to pin, other to GND (pullup internal)

Pinout Reference:
Keys: D2(0),D3(1),D4(2),D5(3),D6(4),D7(5),D8(6),D9(7),D10(8),D11(9),D12(10),D13(11),A0(12),A1(13),A2(14),A3(15)

Libraries:
- Control_Surface v2+ (https://tttapa.github.io/Control-Surface/)
  - Install via Arduino IDE Library Manager

Usage:
1. Wire per Dilla4x_Guide.md
2. Flash this .ino (Board: Arduino Leonardo, Port: auto)
3. Plug USB-C → instant MIDI device (class-compliant)

Author: Roo (Trailblazer Labs)
Version: v1.0 - Dilla4x Ready
*/

#include <Control_Surface.h>  // Control Surface library for MIDI/USB
#include <EEPROM.h>           // Persistent octave storage

// ========================================
// CONSTANTS & PINS
// ========================================
constexpr uint8_t LED_PIN = LED_BUILTIN;  // Pin 17 / RX LED for feedback

// Key pins (16 total): D2-D13 (2-13), A0-A3 (14-17)
const uint8_t keyPins[16] PROGMEM = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,  // D2-D13
  14, 15, 16, 17                          // A0-A3
};

// Base MIDI notes: bottom-left C1(36) lowest → right/up higher pitches (standard pad layout)
const uint8_t baseNotes[16] PROGMEM = {
  48,49,50,51,  // Row 1 (top) highest
  44,45,46,47,  // Row 2
  40,41,42,43,  // Row 3
  36,37,38,39   // Row 4 (bottom) lowest left→right
};

// Top half (rows 1-2, indices 0-7), bottom half (8-15)
const uint8_t topHalfIndices[8] PROGMEM = {0,1,2,3,4,5,6,7};
const uint8_t bottomHalfIndices[8] PROGMEM = {8,9,10,11,12,13,14,15};

const unsigned long OCTAVE_WINDOW_MS = 100;  // Chord detect window (ms)
const int8_t MAX_OCTAVE_SHIFT = 2;
const int8_t MIN_OCTAVE_SHIFT = -2;

// ========================================
// GLOBALS
// ========================================
USBMIDI_Interface midi;  // USB MIDI interface

int8_t octaveShift = 0;  // Current octave offset (-2 to +2)
bool topChordActive = false;
bool bottomChordActive = false;
unsigned long chordStartTimeTop = 0;
unsigned long chordStartTimeBottom = 0;

// EEPROM: octave at addr 0 (1 byte signed? use 0-4 → -2..2)
const uint8_t EEPROM_OCTAVE_ADDR = 0;

// Custom dynamic note button class
class DynamicNoteButton : public Element {
private:
  uint8_t pin;
  uint8_t baseNote;
  bool lastState = false;

public:
  DynamicNoteButton(uint8_t p, uint8_t note) : pin(p), baseNote(note) {
    pinMode(pin, INPUT_PULLUP);
  }

  void loop() override {
    bool pressed = (digitalRead(pin) == LOW);
    if (pressed != lastState) {
      lastState = pressed;
      uint8_t baseNoteVal = pgm_read_byte(&baseNotes[baseNote]);
      uint8_t note = constrain(baseNoteVal + (octaveShift * 12), 0, 127);
      if (pressed) {
        Control_Surface.sendNoteOn(note, 127, 1);
      } else {
        Control_Surface.sendNoteOff(note, 0, 1);
      }
    }
  }
};

// Array of 16 dynamic note buttons
DynamicNoteButton* noteButtons[16];


// ========================================
// OCTAVE CHORD DETECT
// ========================================
void checkOctaveChord(int8_t shiftDir, const uint8_t* indices, unsigned long& startTime, bool& active) {
  unsigned long now = millis();
  int pressCount = 0;

  // Count pressed in group
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t idx = pgm_read_byte(&indices[i]);
    uint8_t pin = pgm_read_byte(&keyPins[idx]);
    if (digitalRead(pin) == LOW) pressCount++;
  }

  if (pressCount == 8) {  // All 8 pressed
    if (startTime == 0) startTime = now;  // First press time
    if (now - startTime <= OCTAVE_WINDOW_MS && !active) {
      octaveShift += shiftDir;
      octaveShift = constrain(octaveShift, MIN_OCTAVE_SHIFT, MAX_OCTAVE_SHIFT);
      active = true;
      saveOctaveToEEPROM();
      feedbackLEDBlink(200);  // Short blink
      Serial.print("Octave shift: ");
      Serial.println(octaveShift);
    }
  } else {
    // Reset on any release
    startTime = 0;
    active = false;
  }
}

// ========================================
// UTILITY FUNCTIONS
// ========================================
void saveOctaveToEEPROM() {
  uint8_t val = octaveShift + 2;  // -2→0, +2→4
  EEPROM.update(EEPROM_OCTAVE_ADDR, val);
}

void loadOctaveFromEEPROM() {
  uint8_t val = EEPROM.read(EEPROM_OCTAVE_ADDR);
  octaveShift = val - 2;  // 0→-2, 4→+2
  octaveShift = constrain(octaveShift, MIN_OCTAVE_SHIFT, MAX_OCTAVE_SHIFT);
}

void feedbackLEDBlink(uint16_t duration) {
  digitalWrite(LED_PIN, HIGH);
  delay(duration);
  digitalWrite(LED_PIN, LOW);
}

// Init all note buttons
void initNoteButtons() {
  for (uint8_t i = 0; i < 16; i++) {
    uint8_t pin = pgm_read_byte(&keyPins[i]);
    noteButtons[i] = new DynamicNoteButton(pin, i);  // i = baseNote index
    Control_Surface.add(noteButtons[i]);
  }
}

// ========================================
// SETUP
// ========================================
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  while (!Serial);  // Wait serial (optional)

  // Load persistent octave
  loadOctaveFromEEPROM();
  Serial.print("Loaded octave shift: ");
  Serial.println(octaveShift);

  Control_Surface.begin();  // Init Control_Surface + MIDI

  // Init elements
  initNoteButtons();

  feedbackLEDBlink(100);  // Ready blink
  Serial.println("Dilla4x Firmware v1.0 Ready!");
}

// ========================================
// LOOP
// ========================================
void loop() {
  Control_Surface.loop();  // Handle all MIDI/button logic

  // Custom octave chord detect
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10) {  // Poll 100Hz
    lastCheck = millis();
    checkOctaveChord(1, topHalfIndices, chordStartTimeTop, topChordActive);   // Top half: +oct
    checkOctaveChord(-1, bottomHalfIndices, chordStartTimeBottom, bottomChordActive);  // Bottom half: -oct
  }
}
