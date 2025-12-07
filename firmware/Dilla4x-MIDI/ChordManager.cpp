#include "ChordManager.h"

ChordEvent ChordManager::update(unsigned long currentMillis, uint16_t pinMask) {
  // Check DOWN chord (Left 8 keys)
  if ((pinMask & CHORD_MASK_DOWN) == CHORD_MASK_DOWN) {
    if (downChordStartTime == 0) {
      downChordStartTime = currentMillis;
      downTriggered = false;
    } else if (!downTriggered && (currentMillis - downChordStartTime >= OCTAVE_CHORD_HOLD_MS)) {
      downTriggered = true;
      return ChordEvent::OCTAVE_DOWN;
    }
  } else {
    downChordStartTime = 0;
    downTriggered = false;
  }

  // Check UP chord (Right 8 keys)
  if ((pinMask & CHORD_MASK_UP) == CHORD_MASK_UP) {
    if (upChordStartTime == 0) {
      upChordStartTime = currentMillis;
      upTriggered = false;
    } else if (!upTriggered && (currentMillis - upChordStartTime >= OCTAVE_CHORD_HOLD_MS)) {
      upTriggered = true;
      return ChordEvent::OCTAVE_UP;
    }
  } else {
    upChordStartTime = 0;
    upTriggered = false;
  }

  return ChordEvent::NONE;
}
