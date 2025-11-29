#ifndef DILLA4X_CONFIG_H
#define DILLA4X_CONFIG_H
#include <Arduino.h>
#include <Control_Surface.h>

// ========================================
// VERSION
// ========================================
constexpr uint8_t FIRMWARE_VERSION_MAJOR = 0;
constexpr uint8_t FIRMWARE_VERSION_MINOR = 3;
constexpr uint8_t FIRMWARE_VERSION_PATCH = 0;

// ========================================
// HARDWARE CONSTANTS
// ========================================
constexpr uint8_t NUM_KEYS = 16;
constexpr uint8_t LED_PIN = LED_BUILTIN;
constexpr bool LED_ACTIVE_LOW = true;

// ========================================
// TIMING CONSTANTS (ms)
// ========================================
constexpr unsigned long LED_SLOW_MS = 128;
constexpr unsigned long LED_FAST_MS = 64;

// Feedback visibility duration - long enough for user confirmation in live performance
constexpr unsigned long LED_FEEDBACK_TIMEOUT_MS = 512;

// Debounce time for chord gestures - prevents accidental triggers during normal playing
constexpr unsigned long OCTAVE_CHORD_HOLD_MS = 300;

// Recovery mode debounce delay
constexpr unsigned long RECOVERY_DEBOUNCE_MS = 50;

// ========================================
// LOGIC CONSTANTS
// ========================================
constexpr int8_t MIN_OCTAVE = -3;
constexpr int8_t MAX_OCTAVE = 3;
constexpr uint8_t SEMITONES_PER_OCTAVE = 12;
constexpr auto MIDI_CHANNEL = Channel_1;

// MIDI note range: required by Transposer<MIN, MAX> template parameter
constexpr uint8_t MIN_MIDI_NOTE = 0;
constexpr uint8_t MAX_MIDI_NOTE = 127;

// ========================================
// PIN DEFINITIONS
// ========================================
constexpr uint8_t KEY_PINS[NUM_KEYS] = {
  2, 3, 4, 5,   // Row 0
  6, 7, 8, 9,   // Row 1
  10, 16, 14, 15, // Row 2
  A0, A1, A2, A3  // Row 3
};

// Recovery mode: Hold all 4 corner buttons at power-on to enter safe idle state
// for firmware upload if USB/MIDI stack fails. LED blinks rapidly when active.
constexpr uint8_t RECOVERY_PINS_COUNT = 4;
constexpr uint8_t RECOVERY_PINS[RECOVERY_PINS_COUNT] = {
  KEY_PINS[0],   // Top-Left
  KEY_PINS[3],   // Top-Right
  KEY_PINS[12],  // Bottom-Left
  KEY_PINS[15]   // Bottom-Right
};

// ========================================
// MIDI MAPPING
// ========================================
// Row 0: C3-D#3, Row 1: G#2-B2, Row 2: E2-G2, Row 3: C2-D#2
constexpr uint8_t BASE_NOTES[NUM_KEYS] = {
  48, 49, 50, 51,
  44, 45, 46, 47,
  40, 41, 42, 43,
  36, 37, 38, 39
};

// ========================================
// CHORD DEFINITIONS
// ========================================
// Left half (Cols 0,1): Keys 0,4,8,12 (col 0) and 1,5,9,13 (col 1)
constexpr uint16_t CHORD_MASK_DOWN = 
  (1U << 0) | (1U << 4) | (1U << 8) | (1U << 12) |  // Column 0
  (1U << 1) | (1U << 5) | (1U << 9) | (1U << 13);  // Column 1

// Right half (Cols 2,3): Keys 2,6,10,14 (col 2) and 3,7,11,15 (col 3)
constexpr uint16_t CHORD_MASK_UP = 
  (1U << 2) | (1U << 6) | (1U << 10) | (1U << 14) |  // Column 2
  (1U << 3) | (1U << 7) | (1U << 11) | (1U << 15);  // Column 3

// Chord threshold: all 8 keys on one side must be pressed
constexpr uint8_t CHORD_THRESHOLD = 8;
// Cancel threshold with margin: prevents accidental re-trigger during hand repositioning
constexpr uint8_t CHORD_CANCEL_THRESHOLD = 3;
constexpr uint8_t MIN_MEANINGFUL_KEYS = 6;

// ========================================
// VALIDATION & DERIVED CONSTANTS
// ========================================

// Pin validation for ATmega32U4 (pins 2-23, excluding serial pins 0-1)
static_assert(KEY_PINS[0] >= 2 && KEY_PINS[0] <= 23, "KEY_PINS[0] out of range");
static_assert(KEY_PINS[1] >= 2 && KEY_PINS[1] <= 23, "KEY_PINS[1] out of range");
static_assert(KEY_PINS[2] >= 2 && KEY_PINS[2] <= 23, "KEY_PINS[2] out of range");
static_assert(KEY_PINS[3] >= 2 && KEY_PINS[3] <= 23, "KEY_PINS[3] out of range");
static_assert(KEY_PINS[4] >= 2 && KEY_PINS[4] <= 23, "KEY_PINS[4] out of range");
static_assert(KEY_PINS[5] >= 2 && KEY_PINS[5] <= 23, "KEY_PINS[5] out of range");
static_assert(KEY_PINS[6] >= 2 && KEY_PINS[6] <= 23, "KEY_PINS[6] out of range");
static_assert(KEY_PINS[7] >= 2 && KEY_PINS[7] <= 23, "KEY_PINS[7] out of range");
static_assert(KEY_PINS[8] >= 2 && KEY_PINS[8] <= 23, "KEY_PINS[8] out of range");
static_assert(KEY_PINS[9] >= 2 && KEY_PINS[9] <= 23, "KEY_PINS[9] out of range");
static_assert(KEY_PINS[10] >= 2 && KEY_PINS[10] <= 23, "KEY_PINS[10] out of range");
static_assert(KEY_PINS[11] >= 2 && KEY_PINS[11] <= 23, "KEY_PINS[11] out of range");
static_assert(KEY_PINS[12] >= 2 && KEY_PINS[12] <= 23, "KEY_PINS[12] out of range");
static_assert(KEY_PINS[13] >= 2 && KEY_PINS[13] <= 23, "KEY_PINS[13] out of range");
static_assert(KEY_PINS[14] >= 2 && KEY_PINS[14] <= 23, "KEY_PINS[14] out of range");
static_assert(KEY_PINS[15] >= 2 && KEY_PINS[15] <= 23, "KEY_PINS[15] out of range");

static_assert(SEMITONES_PER_OCTAVE == 12, "SEMITONES_PER_OCTAVE must be 12");
static_assert((CHORD_MASK_DOWN & CHORD_MASK_UP) == 0, "Chord masks overlap");
static_assert(sizeof(BASE_NOTES) == NUM_KEYS, "BASE_NOTES size mismatch");
static_assert(sizeof(KEY_PINS) == NUM_KEYS, "KEY_PINS size mismatch");
static_assert(CHORD_THRESHOLD > CHORD_CANCEL_THRESHOLD, "Chord threshold must exceed cancel threshold");
static_assert(CHORD_THRESHOLD > 0 && CHORD_THRESHOLD <= 8, "Chord threshold must be 1-8");
static_assert(CHORD_CANCEL_THRESHOLD > 0, "Chord cancel threshold must be positive");
static_assert(LED_FEEDBACK_TIMEOUT_MS > 0, "LED feedback timeout must be positive");
static_assert(__builtin_popcount(CHORD_MASK_DOWN) == 8, "CHORD_MASK_DOWN must have exactly 8 keys");
static_assert(__builtin_popcount(CHORD_MASK_UP) == 8, "CHORD_MASK_UP must have exactly 8 keys");
// Validate chord masks only reference valid bit positions (0-15 for 16 keys)
static_assert((CHORD_MASK_DOWN & ~((1UL << NUM_KEYS) - 1)) == 0, "CHORD_MASK_DOWN references invalid key positions");
static_assert((CHORD_MASK_UP & ~((1UL << NUM_KEYS) - 1)) == 0, "CHORD_MASK_UP references invalid key positions");

#endif // DILLA4X_CONFIG_H
