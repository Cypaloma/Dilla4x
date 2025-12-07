#include "LedController.h"

void LedController::init() {
  TX_RX_LED_INIT;  // Initialize LED pins
  TXLED1;          // TX LED off (Active Low, 1=Off, 0=On)
  RXLED1;          // RX LED off (Active Low, 1=Off, 0=On)
}

// Activity on RXLED (Stable, User Control)
void LedController::setActivity(bool active) {
  if (active) {
    RXLED0; // ON
  } else {
    RXLED1; // OFF
  }
}

// Octave Status on TXLED (Shared with USB)
void LedController::setShifted(bool shifted) {
  if (shifted) {
    TXLED0; // ON
  } else {
    TXLED1; // OFF
  }
}
