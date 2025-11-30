/*
 * Minimal blink for Arduino Pro Micro (ATmega32U4).
 * Uses the TX LED macros (active low) so only one LED blinks; RX stays off.
 */

void setup() {
  TX_RX_LED_INIT;  // set LED pins as outputs
  TXLED1;          // ensure TX LED off (active low)
  RXLED1;          // keep RX LED off
}

void loop() {
  TXLED0;  // on
  delay(150);
  TXLED1;  // off
  delay(150);
}
