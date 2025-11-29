#ifndef DILLA4X_CHORDMANAGER_H
#define DILLA4X_CHORDMANAGER_H

#include <Arduino.h>
#include "Config.h"

enum class ChordEvent : uint8_t {
  NONE,
  OCTAVE_UP,
  OCTAVE_DOWN
};

enum class ChordRequest : uint8_t {
  NONE,
  DOWN,
  UP
};

class ChordManager {
public:
  ChordEvent update(unsigned long currentMillis, uint16_t pinMask);
  
private:
  enum class ChordState { IDLE, DEBOUNCE, TRIGGERED };
  
  ChordState state = ChordState::IDLE;
  unsigned long stateStart = 0;
  ChordRequest pendingChord = ChordRequest::NONE;
  uint8_t lastDownCount = 0;
  uint8_t lastUpCount = 0;
};

#endif // DILLA4X_CHORDMANAGER_H

