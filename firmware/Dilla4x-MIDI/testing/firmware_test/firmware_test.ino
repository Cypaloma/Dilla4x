/*
 * Dilla4x - Firmware Test Harness
 * Configurable test utility for debugging main firmware issues.
 * Refactored from pin_debug.ino with toggleable test modes.
 * 
 * WHEN TO USE:
 *   - Debugging firmware logic (debounce, state machine, etc.)
 *   - Testing if MIDIUSB library causes pin conflicts
 *   - Testing if watchdog timer interferes with operation
 *   - Validating firmware changes before deployment
 * 
 * TEST MODES (Configure below):
 *   - TEST_WATCHDOG: Enable/disable watchdog timer
 *   - TEST_MIDIUSB: Enable/disable MIDIUSB library
 *   - TEST_VERBOSE: Enable/disable detailed trace logging
 * 
 * EXPECTED OUTPUT:
 *   - [DEBOUNCE] messages when keys stabilize
 *   - [MIDI] messages when MIDI events would fire
 *   - Periodic RAW/STABLE/LAST state summaries
 */

#include <Arduino.h>

// ========================================
// TEST CONFIGURATION - Toggle these flags
// ========================================
#define TEST_WATCHDOG 0        // 1=Enable watchdog, 0=Disable
#define TEST_MIDIUSB 0         // 1=Include MIDIUSB, 0=Exclude (tests pin conflicts)
#define TEST_VERBOSE 1         // 1=Detailed logging, 0=Minimal output

// Conditional includes
#if TEST_WATCHDOG
#include <avr/wdt.h>
#endif

#if TEST_MIDIUSB
#include <MIDIUSB.h>
#endif

// ========================================
// EXACT COPY FROM Config.h
// ========================================
constexpr uint8_t NUM_KEYS = 16;
constexpr unsigned long DEBOUNCE_MS = 30;

constexpr uint8_t KEY_PINS[NUM_KEYS] = {
  2, 3, 4, 5,
  6, 7, 8, 9,
  10, 16, 14, 15,
  A0, A1, A2, A3
};

// ========================================
// STATE (EXACT COPY FROM MAIN)
// ========================================
uint16_t g_lastButtonState = 0;
uint16_t g_stableButtonState = 0;
unsigned long g_lastDebounceTime[NUM_KEYS] = {0};

// ========================================
// readPins (EXACT COPY)
// ========================================
uint16_t readPins() {
  uint16_t reading = 0;
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    if (digitalRead(KEY_PINS[i]) == LOW) {
      reading |= (1U << i);
    }
  }
  return reading;
}

// ========================================
// SETUP
// ========================================
void setup() {
  #if TEST_WATCHDOG
  wdt_disable();  // Disable during setup
  #endif
  
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
  }
  
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  
  Serial.println("\n=== DILLA4X FIRMWARE TEST HARNESS ===");
  Serial.println("Configuration:");
  Serial.print("  Watchdog: ");
  Serial.println(TEST_WATCHDOG ? "ENABLED" : "DISABLED");
  Serial.print("  MIDIUSB: ");
  Serial.println(TEST_MIDIUSB ? "ENABLED" : "DISABLED");
  Serial.print("  Verbose: ");
  Serial.println(TEST_VERBOSE ? "ENABLED" : "DISABLED");
  Serial.print("  Debounce: ");
  Serial.print(DEBOUNCE_MS);
  Serial.println(" ms");
  Serial.println();
  
  #if TEST_WATCHDOG
  wdt_enable(WDTO_4S);
  Serial.println("Watchdog timer: 4 second timeout");
  #endif
}

// ========================================
// LOOP - EXACT COPY OF MAIN LOGIC + TRACING
// ========================================
void loop() {
  #if TEST_WATCHDOG
  wdt_reset();
  #endif
  
  const unsigned long currentMillis = millis();
  const uint16_t rawPinMask = readPins();
  
  bool anyChange = false;
  
  for (uint8_t i = 0; i < NUM_KEYS; i++) {
    bool rawState = (rawPinMask & (1U << i)) != 0;
    bool stableState = (g_stableButtonState & (1U << i)) != 0;
    
    // EXACT debounce logic from main firmware
    if (rawState != stableState) {
       if ((currentMillis - g_lastDebounceTime[i]) > DEBOUNCE_MS) {
         g_lastDebounceTime[i] = currentMillis;
         
         if (rawState) {
           g_stableButtonState |= (1U << i);
         } else {
           g_stableButtonState &= ~(1U << i);
         }
         
         #if TEST_VERBOSE
         // TRACE: State change confirmed
         Serial.print("[DEBOUNCE] Key ");
         Serial.print(i);
         Serial.print(" -> ");
         Serial.println(rawState ? "PRESSED" : "RELEASED");
         #endif
       }
    }
    
    // EXACT MIDI trigger logic from main firmware
    bool confirmedState = (g_stableButtonState & (1U << i)) != 0;
    bool lastState = (g_lastButtonState & (1U << i)) != 0;
    
    if (confirmedState != lastState) {
      // TRACE: Would send MIDI here
      Serial.print("[MIDI] Key ");
      Serial.print(i);
      Serial.print(" (Pin ");
      Serial.print(KEY_PINS[i]);
      Serial.print(") -> ");
      Serial.println(confirmedState ? "NOTE ON" : "NOTE OFF");
      
      if (confirmedState) {
        g_lastButtonState |= (1U << i);
      } else {
        g_lastButtonState &= ~(1U << i);
      }
      anyChange = true;
    }
  }
  
  // Periodic status if no changes
  #if TEST_VERBOSE
  static unsigned long lastStatusTime = 0;
  if (!anyChange && (currentMillis - lastStatusTime) > 1000) {
    lastStatusTime = currentMillis;
    Serial.print("RAW: 0x");
    Serial.print(rawPinMask, HEX);
    Serial.print(" STABLE: 0x");
    Serial.print(g_stableButtonState, HEX);
    Serial.print(" LAST: 0x");
    Serial.println(g_lastButtonState, HEX);
  }
  #endif
  
  delay(10); // Small delay to prevent serial flood
}
