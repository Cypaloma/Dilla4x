#ifndef DILLA4X_CHORDMANAGER_H
#define DILLA4X_CHORDMANAGER_H

#include <Arduino.h>
#include "Config.h"

enum class ChordEvent : uint8_t {
  NONE,
  OCTAVE_UP,
  OCTAVE_DOWN
};

class ChordManager {
public:
  // Check for chord hold completion. Non-blocking.
  ChordEvent update(unsigned long currentMillis, uint16_t pinMask);
  
private:
  unsigned long downChordStartTime = 0;
  unsigned long upChordStartTime = 0;
  bool downTriggered = false;
  bool upTriggered = false;
};

#endif // DILLA4X_CHORDMANAGER_H
