#ifndef DILLA4X_LEDCONTROLLER_H
#define DILLA4X_LEDCONTROLLER_H

#include <Arduino.h>
#include "Config.h"

enum class LedPattern {
  OFF,
  ON,
  BLINK_SLOW,
  BLINK_FAST
};

class LedController {
public:
  void init();
  void update(unsigned long currentMillis);
  void setPattern(LedPattern pattern, unsigned long currentMillis);
  
private:
  LedPattern currentPattern = LedPattern::OFF;
  unsigned long lastToggle = 0;
  bool ledState = false;  // Logical LED state (may differ from physical pin state)
  
  unsigned long getInterval(LedPattern pattern) const;

};

#endif // DILLA4X_LEDCONTROLLER_H

