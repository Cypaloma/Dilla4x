#include "LedController.h"

void LedController::init() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_ACTIVE_LOW ? HIGH : LOW);
}

unsigned long LedController::getInterval(LedPattern pattern) const {
  switch (pattern) {
    case LedPattern::BLINK_SLOW: return LED_SLOW_MS;
    case LedPattern::BLINK_FAST: return LED_FAST_MS;
    default: return 0;  // Non-blinking patterns don't use intervals
  }
}

void LedController::setPattern(LedPattern pattern, unsigned long currentMillis) {
  if (currentPattern != pattern) {
    currentPattern = pattern;
    
    // Start with LED OFF for blinking patterns (prevents flash)
    if (pattern == LedPattern::BLINK_SLOW || pattern == LedPattern::BLINK_FAST) {
      ledState = false;
      digitalWrite(LED_PIN, LED_ACTIVE_LOW ? HIGH : LOW);
      lastToggle = currentMillis;
    } else {
      // Apply immediate state for non-blinking patterns
      ledState = (pattern != LedPattern::OFF);
      digitalWrite(LED_PIN, LED_ACTIVE_LOW ? !ledState : ledState);
      lastToggle = 0;
    }
  }
}

void LedController::update(unsigned long currentMillis) {
  // Only update for blinking patterns
  if (currentPattern != LedPattern::BLINK_SLOW && currentPattern != LedPattern::BLINK_FAST) {
    return;
  }
  
  // Call getInterval() directly (caching was premature optimization)
  const unsigned long interval = getInterval(currentPattern);
  
  if ((unsigned long)(currentMillis - lastToggle) >= interval) {
    ledState = !ledState;
    digitalWrite(LED_PIN, LED_ACTIVE_LOW ? !ledState : ledState);
    lastToggle = currentMillis;
  }
}
