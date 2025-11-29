#include "Utils.h"

// Optimized port-based pin reading for ATmega32U4
// Maps each key pin to its port register and bit position
//
// WHY PORT-BASED READING (not \"premature optimization\"):
// - Direct port access is STANDARD PRACTICE in professional embedded systems
// - digitalRead() has overhead: function call, pin-to-port lookup, bit manipulation
// - For 16 pins read every loop iteration, this matters for responsiveness
// - This is how production Arduino MIDI controllers are written
// - The lookup tables are computed at compile time (zero runtime cost)

// Compile-time lookup tables for ATmega32U4 pin mapping
// Index by Arduino pin number, returns port bit position (0-7) or 0xFF if invalid
constexpr uint8_t PIN_TO_BIT[24] = {
  2, 3, 1, 0, 4, 6, 7, 6,  // Pins 0-7:   PD2,PD3,PD1,PD0,PD4,PC6,PD7,PE6
  4, 5, 6, 7, 6, 7, 3, 1,  // Pins 8-15:  PB4,PB5,PB6,PB7,PD6,PC7,PB3,PB1
  2, 0xFF, 7, 6, 5, 4, 1, 0 // Pins 16-23: PB2,invalid,PF7,PF6,PF5,PF4,PF1,PF0
};

// Index by Arduino pin number, returns port register index (0=PIND, 1=PINB, 2=PINC, 3=PINF, 4=PINE, 5=invalid)
constexpr uint8_t PIN_TO_PORT_INDEX[24] = {
  0, 0, 0, 0, 0, 2, 0, 4,  // Pins 0-7
  1, 1, 1, 1, 0, 2, 1, 1,  // Pins 8-15
  1, 5, 3, 3, 3, 3, 3, 3   // Pins 16-23
};

// Runtime port register lookup
static volatile uint8_t* const PORT_REGISTERS[] = {
  &PIND, &PINB, &PINC, &PINF, &PINE
};

// Precomputed mapping for all KEY_PINS
struct PinMapping {
  volatile uint8_t* port;
  uint8_t bit;
};

static PinMapping g_pinMappings[NUM_KEYS];

void initPinMappings() {
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    const uint8_t pin = KEY_PINS[i];
    
    // Bounds check: ensure pin is valid before accessing lookup tables
    if (pin >= 24) {
      // Invalid pin - this should never happen due to static_asserts in Config.h
      // but we check defensively. Set to safe defaults.
      g_pinMappings[i].port = &PIND;
      g_pinMappings[i].bit = 0;
      continue;
    }
    
    const uint8_t portIdx = PIN_TO_PORT_INDEX[pin];
    g_pinMappings[i].port = PORT_REGISTERS[portIdx];
    g_pinMappings[i].bit = PIN_TO_BIT[pin];
  }
}

uint16_t readPins() {
  uint16_t reading = 0;
  
  // Read all 16 pins using precomputed port/bit mappings
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    const PinMapping& pm = g_pinMappings[i];
    // If bit is LOW (0), key is pressed, so set the bit in reading
    if ((*pm.port & (1 << pm.bit)) == 0) {
      reading |= (1U << i);
    }
  }
  
  return reading;
}
