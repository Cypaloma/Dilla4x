#ifndef DILLA4X_LEDCONTROLLER_H
#define DILLA4X_LEDCONTROLLER_H

#include <Arduino.h>

// LED Control using TX LED macros (Pro Micro / ATmega32U4)
// TXLED0 = TX LED on (active low), TXLED1 = TX LED off
// RX LED is kept off permanently to avoid LED_BUILTIN ambiguity
inline void setLedOn()  { TXLED0; }
inline void setLedOff() { TXLED1; }

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

