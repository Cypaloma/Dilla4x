#ifndef DILLA4X_LEDCONTROLLER_H
#define DILLA4X_LEDCONTROLLER_H

#include <Arduino.h>

// LED Control using system-provided TX/RX LED macros for ATmega32U4
// TX LED = Activity (Green)
// RX LED = Octave Shifted (Yellow)

class LedController {
public:
  void init();
  
  // Set TX LED (Green) based on key activity
  // true = ON/Active, false = OFF
  void setActivity(bool active);
  
  // Set RX LED (Yellow) based on Octave state
  // true = Shifted (Warning), false = Center (Safe)
  void setShifted(bool shifted);
};

#endif // DILLA4X_LEDCONTROLLER_H
