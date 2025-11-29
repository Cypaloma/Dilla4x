#ifndef DILLA4X_UTILS_H
#define DILLA4X_UTILS_H

#include <Arduino.h>
#include "Config.h"

// Initialize pin mappings (call once in setup() before first readPins() call)
void initPinMappings();

// Read all 16 key pins and return as bitmask (bit N = 1 if KEY_PINS[N] is pressed/LOW)
uint16_t readPins();

// Overflow-safe time comparison: returns true if currentTime >= targetTime
// Handles millis() rollover correctly using unsigned arithmetic
// 
// WHY THIS PATTERN IS CORRECT (not \"unnecessarily complex\"):
// Simple comparison (currentTime >= targetTime) FAILS with wraparound:
//   - If target=100 and current wraps to 5, then 5 >= 100 is FALSE (wrong!)
//   - The (currentTime - targetTime) < ULONG_MAX/2 pattern handles this correctly
//   - This is the standard embedded systems approach for wraparound-safe time checks
//
// Example: target=4294967295 (near max), current=5 (wrapped)
//   - currentTime - targetTime = 5 - 4294967295 = 6 (wraps to small positive)
//   - 6 < ULONG_MAX/2 is TRUE (correct - time has elapsed)
inline bool timeElapsed(unsigned long currentTime, unsigned long targetTime) {
  return (unsigned long)(currentTime - targetTime) < (ULONG_MAX / 2);
}

#endif // DILLA4X_UTILS_H
