/*
 * Dilla4x - Crosstalk Detector
 * Definitively finds pin-to-pin shorts (solder bridges/whiskers) automatically.
 * 
 * WHEN TO USE:
 *   - After soldering Arduino Pro Micro to headers (BOTTOM SECTION only)
 *   - Before attaching top button section
 *   - When debugging ghost button presses or multiple keys triggering together
 *   - During production QA of bottom assemblies
 * 
 * WHAT IT TESTS:
 *   - BOTTOM SECTION: Arduino pins and header connections for physical shorts
 *   - Run BEFORE attaching top buttons, then use connection_scout for full assembly
 * 
 * EXPECTED OUTPUT:
 *   - Clean: "Status: Clean (No Crosstalk Detected)"
 *   - Issue: "SHORT DETECTED: Pin X <---> Pin Y" (solder bridge found)
 * 
 * Logic:
 * 1. Sets all pins to INPUT_PULLUP (Safe state).
 * 2. One by one, turns a Pin into OUTPUT LOW (Simulating a press).
 * 3. Scans all OTHER pins. If any read LOW, they are physically shorted to the active pin.
 * 4. Reports any bridges found.
 */

#include <Arduino.h>

// ========================================
// PIN DEFINITIONS (Self-Contained)
// ========================================
const uint8_t NUM_KEYS = 16;
const uint8_t KEY_PINS[NUM_KEYS] = {
  2, 3, 4, 5,     // Row 0
  6, 7, 8, 9,     // Row 1
  10, 16, 14, 15, // Row 2
  A0, A1, A2, A3  // Row 3
};

// ========================================
// LOGIC
// ========================================

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); } // Wait for USB Serial
  
  Serial.println("\n\n=== DILLA4X CROSSTALK DETECTOR ===");
  Serial.println("Starting Short Circuit Scan...");

  
  // 1. Initial Safety: All Inputs Pulled Up
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
  }
}

void loop() {
  bool foundShort = false;
  
  Serial.println("--- Scanning ---");

  for (uint8_t driverIdx = 0; driverIdx < NUM_KEYS; driverIdx++) {
    uint8_t driverPin = KEY_PINS[driverIdx];
    
    // A. Drive this pin LOW
    pinMode(driverPin, OUTPUT);
    digitalWrite(driverPin, LOW);
    
    // Small delay to let voltage settle
    delayMicroseconds(50);
    
    // B. Check all OTHER pins
    for (uint8_t readerIdx = 0; readerIdx < NUM_KEYS; readerIdx++) {
      if (driverIdx == readerIdx) continue; // Don't check self
      
      uint8_t readerPin = KEY_PINS[readerIdx];
      
      // If we read LOW on a neighbor, it's being pulled down by the driver -> SHORT!
      if (digitalRead(readerPin) == LOW) {
        // Debounce read to be sure
        delayMicroseconds(50);
        if (digitalRead(readerPin) == LOW) {
           Serial.print("SHORT DETECTED: Pin ");
           Serial.print(driverPin);
           Serial.print(" (Key ");
           Serial.print(driverIdx);
           Serial.print(") <---> Pin ");
           Serial.print(readerPin);
           Serial.print(" (Key ");
           Serial.print(readerIdx);
           Serial.println(")");
           foundShort = true;
        }
      }
    }
    
    // C. Reset Driver to Input Pullup
    pinMode(driverPin, INPUT_PULLUP);
    // Delay to let pullup restore voltage
    delayMicroseconds(50); 
  }

  if (!foundShort) {
    Serial.println("Status: Clean (No Crosstalk Detected)");
  }
  
  delay(1000); // Scan once per second
}
