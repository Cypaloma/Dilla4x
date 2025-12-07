/*
 * Dilla4x - Connection Scout
 * Scans all digital pins to identify active button connections.
 * 
 * WHEN TO USE:
 *   - After assembling top button section with bottom Arduino section
 *   - To verify button wiring matches Config.h expectations
 *   - When debugging "button not working" issues
 *   - During production QA of fully assembled units
 * 
 * WHAT IT TESTS:
 *   - TOP SECTION: Button connections to Arduino
 *   - Run AFTER crosstalk_detector verifies bottom section is clean
 * 
 * EXPECTED OUTPUT:
 *   - Clean: Only shows activity when you press buttons
 *   - Issue: Pins stuck LOW (short to ground) or no response (broken connection)
 * 
 * OUTPUT FORMAT:
 *   - Heartbeat blink every 500ms (device is alive)
 *   - "ACTIVITY DETECTED ON PIN: X" when button pressed
 *   - Periodic scan summary showing all pin states
 */

#include <Arduino.h>

// Macros for Pro Micro LEDs (Heartbeat indicator)
#ifndef TXLED0
#define TXLED0 PORTD &= ~(1<<5)
#define TXLED1 PORTD |= (1<<5)
#define RXLED0 PORTB &= ~(1<<0)
#define RXLED1 PORTB |= (1<<0)
#endif

// Configuration
constexpr uint8_t FIRST_PIN = 2;   // Skip 0,1 (Serial)
constexpr uint8_t LAST_PIN = 21;   // Pro Micro max usable pin
constexpr unsigned long DEBOUNCE_MS = 100;  // Debounce display output
constexpr unsigned long SCAN_SUMMARY_MS = 2000;  // Full scan summary interval

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  
  // Initialize LEDs for heartbeat
  DDRD |= (1<<5); 
  DDRB |= (1<<0);
  TXLED1; 
  RXLED1;

  // Set all pins to INPUT_PULLUP
  for (uint8_t i = FIRST_PIN; i <= LAST_PIN; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  
  Serial.println("\n=== DILLA4X CONNECTION SCOUT ===");
  Serial.println("Scanning pins " + String(FIRST_PIN) + "-" + String(LAST_PIN));
  Serial.println("Press buttons to identify pin assignments");
  Serial.println();
}

void loop() {
  static unsigned long lastScanTime = 0;
  const unsigned long currentMillis = millis();
  
  bool activityDetected = false;
  
  // Heartbeat blink (500ms period)
  if ((currentMillis / 500) % 2 == 0) {
    TXLED0;  // ON
  } else {
    TXLED1;  // OFF
  }
  
  // ========================================
  // ACTIVE DETECTION: Report pressed buttons
  // ========================================
  for (uint8_t i = FIRST_PIN; i <= LAST_PIN; i++) {
    if (digitalRead(i) == LOW) {
      Serial.print("ACTIVITY DETECTED ON PIN: ");
      Serial.print(i);
      
      // Highlight if this is a known key pin from Config.h
      // Known pins: 2,3,4,5,6,7,8,9,10,16,14,15,A0,A1,A2,A3
      const uint8_t knownPins[] = {2,3,4,5,6,7,8,9,10,16,14,15,18,19,20,21};
      bool isKnown = false;
      for (uint8_t j = 0; j < sizeof(knownPins); j++) {
        if (i == knownPins[j]) {
          isKnown = true;
          break;
        }
      }
      
      if (isKnown) {
        Serial.println(" ✓ [Expected Key Pin]");
      } else {
        Serial.println(" ⚠ [NOT in Config.h - Check wiring]");
      }
      
      activityDetected = true;
    }
  }
  
  // Debounce output if activity detected
  if (activityDetected) {
    delay(DEBOUNCE_MS);
  }
  
  // ========================================
  // PERIODIC SCAN SUMMARY: Show all pin states
  // ========================================
  if (currentMillis - lastScanTime > SCAN_SUMMARY_MS) {
    lastScanTime = currentMillis;
    
    Serial.print("SCAN: ");
    bool anyPressed = false;
    
    for (uint8_t i = FIRST_PIN; i <= LAST_PIN; i++) {
      int state = digitalRead(i);
      
      if (state == LOW) {
        Serial.print("[PIN ");
        Serial.print(i);
        Serial.print(":0!] ");
        anyPressed = true;
      }
    }
    
    if (!anyPressed) {
      Serial.print("(All pins HIGH - No buttons pressed)");
    }
    
    Serial.println();
  }
  
  delay(10);  // Small delay to prevent serial flooding
}
