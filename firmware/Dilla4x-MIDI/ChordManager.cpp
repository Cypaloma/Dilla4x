#include "ChordManager.h"

ChordEvent ChordManager::update(unsigned long currentMillis, uint16_t pinMask) {
  // Determine current input based on pin mask
  const uint8_t downCount = __builtin_popcount(CHORD_MASK_DOWN & pinMask);
  const uint8_t upCount = __builtin_popcount(CHORD_MASK_UP & pinMask);
  
  // Store for reuse in TRIGGERED state
  lastDownCount = downCount;
  lastUpCount = upCount;
  
  const bool downPressed = (downCount >= CHORD_THRESHOLD);
  const bool upPressed = (upCount >= CHORD_THRESHOLD);
  
  // Ignore ambiguous input (both sides pressed simultaneously)
  if (downPressed && upPressed) {
    // Don't change state during ambiguous input
    return ChordEvent::NONE;
  }

  // Determine input chord (NONE, DOWN, or UP)
  ChordRequest inputChord = ChordRequest::NONE;
  if (downPressed) {
    inputChord = ChordRequest::DOWN;
  } else if (upPressed) {
    inputChord = ChordRequest::UP;
  }
  
  switch (state) {
    case ChordState::IDLE:
      if (inputChord != ChordRequest::NONE) {
        state = ChordState::DEBOUNCE;
        stateStart = currentMillis;
        pendingChord = inputChord;
      }
      return ChordEvent::NONE;
      
    case ChordState::DEBOUNCE: {
      // If input changed or lost, reset to IDLE
      if (inputChord != pendingChord) {
        state = ChordState::IDLE;
        pendingChord = ChordRequest::NONE;
        return ChordEvent::NONE;
      }
      
      // Input still matches - check if hold time elapsed (overflow-safe)
      if ((unsigned long)(currentMillis - stateStart) >= OCTAVE_CHORD_HOLD_MS) {
        state = ChordState::TRIGGERED;
        return (pendingChord == ChordRequest::UP) ? ChordEvent::OCTAVE_UP : ChordEvent::OCTAVE_DOWN;
      }
      return ChordEvent::NONE;
    }
      
    case ChordState::TRIGGERED: {
      // Reuse already-calculated counts instead of recalculating
      uint8_t activeCount = (pendingChord == ChordRequest::DOWN) ? lastDownCount : lastUpCount;
      
      // Separate two cancel conditions:
      // 1. User switched to opposite chord (inputChord != pendingChord && inputChord != NONE)
      // 2. User released keys below threshold (activeCount < CHORD_CANCEL_THRESHOLD)
      bool chordSwitched = (inputChord != ChordRequest::NONE && inputChord != pendingChord);
      bool keysReleased = (activeCount < CHORD_CANCEL_THRESHOLD);
      
      if (chordSwitched || keysReleased) {
        state = ChordState::IDLE;
        pendingChord = ChordRequest::NONE;
      }
      return ChordEvent::NONE;
    }
  }
  
  return ChordEvent::NONE;
}
