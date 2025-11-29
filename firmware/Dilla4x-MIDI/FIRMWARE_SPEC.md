# Dilla4x Firmware Specification (v0.3)

## 1. Design Philosophy
- **Simplicity**: The codebase prioritizes readability and maintainability. Complex algorithms are avoided.
- **Statelessness**: The device is explicitly designed to be stateless. It resets to a known good state (Octave 0) on every power cycle. This eliminates flash wear, EEPROM corruption risks, and the need for complex factory reset procedures.
- **Robustness**: The device must never enter a state that requires external hardware to fix. "Unbrickability" is a core requirement.
- **Predictability**: State changes occur only on explicit, debounced user actions.

## 2. Hardware Abstraction
### 2.1 Pin Mapping
The firmware targets the **Arduino Pro Micro / Leonardo (ATmega32U4)**.
- **Keys**: 16 keys arranged in a 4x4 physical grid but wired directly to digital pins.
    - **Row 0**: Pins 2, 3, 4, 5
    - **Row 1**: Pins 6, 7, 8, 9
    - **Row 2**: Pins 10, 16, 14, 15
    - **Row 3**: Pins A0, A1, A2, A3
- **LED**: Built-in LED on `LED_BUILTIN` (Pin 13).

### 2.2 Input Handling
- **Method**: Direct `digitalRead` in a loop.
- **Debouncing**: Handled by `Control_Surface` library for notes, and custom state machine for Chords.

## 3. Functional Logic

### 3.1 MIDI Note Generation
- **Library**: `Control_Surface` handles USB MIDI.
- **Mapping**: Each key maps to a specific MIDI note on Channel 1.
- **Transposition**: Global `Transposer` modifies output based on Octave.

### 3.2 Octave Shifting (Chord System)
- **Trigger**: All 8 keys on one side held for >300ms.
    - **Octave Down**: Left half (Cols 0-1) - all 8 keys.
    - **Octave Up**: Right half (Cols 2-3) - all 8 keys.
- **Threshold**: All 8 keys required (no partial chord support).
- **Range**: -3 to +3 octaves.
- **State Machine**:
    1.  **IDLE**: Monitoring.
    2.  **DEBOUNCING**: Valid mask detected.
    3.  **TRIGGERED**: Held for ≥300ms. Action fires once.
- **Safety**: Sends Note Off for all keys before shifting.

### 3.3 LED Feedback
- **Recovery Mode**: Fast continuous blinking (100ms).
- **Feedback Blink**: Short blink (50ms) on Octave Shift.
- **Key Press**: Solid ON.
- **Idle**: OFF.
- **Responsiveness**: Feedback timeout is set to **300ms** to ensure the LED is ready for subsequent inputs during rapid octave shifting.

### 3.4 Recovery Mode
- **Purpose**: Fail-safe to restore device if main app crashes.
- **Trigger**: Holding **Key 0 (Pin 2)** and **Key 15 (Pin A3)** during power-up.
- **Behavior**: Enters infinite loop with LED blinking. Exposes USB CDC for Arduino IDE to trigger bootloader.
- **Note**: This is distinct from a "Factory Reset" (which is not needed as there is no persistent state).

## 4. Data Persistence
- **None**: The device does not use EEPROM.
- **Rationale**:
    - **Longevity**: Eliminates EEPROM write cycles, ensuring the flash memory never wears out.
    - **Simplicity**: Removes complex code for wear leveling, CRC validation, and atomic writes.
    - **Reliability**: A power cycle is guaranteed to fix any logical state issue (except firmware corruption, handled by Recovery Mode).

## 5. Watchdog
- **Enabled**: Watchdog timer is enabled with a 4-second timeout to reset the device in case of a hang.

## 6. Out of Scope (DO NOT OVER-ENGINEER)

The following scenarios are explicitly **out of scope** and require NO firmware handling:

### 6.1 USB Disconnection
- **Reality**: USB disconnection removes power from the device. The device turns off.
- **Action**: None. The `Control_Surface` library handles USB stack. Firmware does not detect or respond to USB states.

### 6.2 "MIDI Failures"
- **Reality**: The `Control_Surface` library abstracts the USB MIDI stack and handles all protocol details.
- **Action**: None. If MIDI doesn't work, it's a library issue or host driver issue, not a firmware concern.

### 6.3 Hardware Faults
- **Reality**: If a key physically breaks, a solder joint fails, or the PCB is damaged, no amount of firmware can fix it.
- **Action**: None. Hardware faults require physical repair.

### 6.4 Memory/Stack Corruption
- **Reality**: If memory corruption occurs, the watchdog will reset the device. If the watchdog itself is corrupted, the device is already non-functional.
- **Action**: None beyond the existing watchdog timer. Do not add redundant checks.

### 6.5 External Error Recovery
- **Reality**: This is a simple USB MIDI controller, not a safety-critical system.
- **Action**: If the device is in a bad state, the user can unplug it. That is sufficient.

## 7. Directory Structure
- `Config.h`: Constants and pin definitions.
- `Utils.h/cpp`: Hardware helpers.
- `ChordManager.h/cpp`: Chord logic.
- `LedController.h/cpp`: LED logic.
- `Dilla4x.ino`: Main entry point.
- **Deleted**: `StateManager.h/cpp` (Removed in v0.3).

---

## 8. Common Misconceptions (For Code Reviewers)

This section addresses common false critiques that arise from misunderstanding embedded development:

### 8.1 "Missing pinMode Configuration"
**FALSE**. The Control_Surface library automatically configures pinMode for all NoteButton pins when `Control_Surface.begin()` is called. Explicit pinMode() calls are NOT needed and would be redundant. See lines 22-39 and line 127 in Dilla4x.ino.

### 8.2 "Watchdog Kills Recovery Mode"
**FALSE**. The watchdog is enabled at line 128 AFTER the recovery mode check at line 123. If recovery mode is active, `enterRecoveryMode()` never returns (it's an infinite loop), so the watchdog enable code is never reached. There is no watchdog reset issue.

### 8.3 "Recovery Mode Should Have Timeout"
**FALSE - THIS IS BY DESIGN**. Recovery mode is an infinite loop with NO timeout by design. It provides a "safe idle state" for firmware upload when the device is soft-bricked. The only exits are power cycle or successful firmware upload. This is intentional, not a bug.

### 8.4 "timeElapsed() is Unnecessarily Complex"
**FALSE**. Simple comparison `(currentTime >= targetTime)` FAILS with wraparound. If target=100 and current wraps to 5, then `5 >= 100` is FALSE (wrong!). The `(a - b) < ULONG_MAX/2` pattern is the CORRECT and STANDARD way to handle unsigned time wraparound in embedded systems. See Utils.h for detailed explanation.

### 8.5 "LED Feedback Has Race Condition"
**FALSE**. Setting `g_feedbackEndTime = millis() + timeout` is safe even near ULONG_MAX because unsigned arithmetic wraps correctly and `timeElapsed()` uses the wraparound-safe comparison pattern. This is not a race condition.

### 8.6 "No MIDI Validation"
**FALSE**. The Control_Surface library handles all MIDI initialization and validation. If `Control_Surface.begin()` fails, it's a library bug, not a firmware issue. We don't need additional validation.

### 8.7 "Port Optimization is Premature"
**FALSE**. Direct port access is STANDARD PRACTICE in professional embedded systems. For 16 pins read every loop iteration, this matters for responsiveness. The lookup tables are computed at compile time (zero runtime cost). This is how production Arduino MIDI controllers are written.

### 8.8 "Ambiguous Chord Detection Creates Undefined Behavior"
**FALSE**. When both chords are pressed simultaneously (line 16-18 in ChordManager.cpp), returning NONE without state change is correct behavior. The state machine remains in its current state, which is well-defined. When the ambiguity resolves, normal state transitions resume.
