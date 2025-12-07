#include "Utils.h"

// Reverting to standard digitalRead for reliability.
// The previous direct port manipulation tables contained a mapping error
// which caused most pins to fail.
// Latency cost is negligible (~5-10us per loop) compared to correct function.

void initPinMappings() {
  // No pre-computation needed for digitalRead
}

uint16_t readPins() {
  uint16_t reading = 0;
  
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    // If pin reads LOW (0), key is pressed
    if (digitalRead(KEY_PINS[i]) == LOW) {
      reading |= (1U << i);
    }
  }
  
  return reading;
}
