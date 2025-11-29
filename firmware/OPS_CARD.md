# Dilla4x Operations Card (v0.2.0)

## Physical Layout

```
Pad Grid (4x4, Row-Major):
┌────┬────┬────┬────┐
│ 1  │ 2  │ 3  │ 4  │
├────┼────┼────┼────┤
│ 5  │ 6  │ 7  │ 8  │
├────┼────┼────┼────┤
│ 9  │ 10 │ 11 │ 12 │
├────┼────┼────┼────┤
│ 13 │ 14 │ 15 │ 16 │
└────┴────┴────┴────┘

Octave DOWN Chord: Left Half (1,2,5,6,9,10,13,14)
Octave UP Chord:   Right Half (3,4,7,8,11,12,15,16)
Recovery Chord:    Hold 1 + 16 (diagonal corners)
```

**Pin Mapping:**
- Pads 1-4: Arduino D2-D5
- Pads 5-8: Arduino D6-D9
- Pads 9-12: Arduino D10, MISO (D16), MOSI (D14), SCK (D15)
  - Note: Pins 10,14,15,16 use SPI hardware pins. Pull-up resistors prevent
    interference with potential SPI peripherals. Currently safe for button use.
- Pads 13-16: Arduino A0-A3

---

## 1. Modes & Recovery

### Normal Boot
- **Behavior**: LED blinks **N times** on startup to show current octave:
  - **1 blink** = Octave -2
  - **2 blinks** = Octave -1
  - **3 blinks** = Octave 0 (default)
  - **4 blinks** = Octave +1
  - **5 blinks** = Octave +2
- **USB Name**: "Dilla4x" (as configured by Control_Surface library)
- **Safety**: 
  - All stuck notes from previous sessions are cleared on boot (via CC 123)
  - Note: Some MIDI devices may not support CC 123; use your DAW's panic/reset if needed
  - Power-On Self-Test (POST) validates hardware integrity
  - Watchdog timer protects against firmware hangs
  - EEPROM version checking enables future data migration

### Verbose Diagnostic Mode
- **Entry**: Hold **Pad 1** (top-left) while plugging in USB
- **Behavior**: Enables detailed serial logging at 115200 baud
- **Output**:
  - Reset source (watchdog, brownout, power-on, external)
  - Octave loading and saving events
  - EEPROM write counts and warnings
  - POST results
  - General operational diagnostics
- **Use Case**: Troubleshooting unexpected behavior or verifying hardware

### Recovery Mode (Safe Mode)

**Entry Methods:**
1. **Manual Entry**: Hold **Pad 1** (top-left) and **Pad 16** (bottom-right) while plugging in USB
2. **Auto-Entry**: Device automatically enters recovery after **3 consecutive firmware crashes** (watchdog resets)
   - Note: Brownout resets (low voltage) do NOT count as crashes
   - Only actual firmware hangs/crashes trigger auto-recovery

**Recovery Behavior:**
- **LED Pattern**: Double Blink Loop (Blink-Blink... Pause... repeat)
- **USB MIDI**: Disabled
- **Serial Port**: Active at 115200 baud
- **Watchdog Timer**: Active with 8-second timeout (device resets if unresponsive)
  - **IMPORTANT**: You must send serial commands or press buttons within 8 seconds
  - If no activity for 8+ seconds, device automatically reboots to normal mode
  - This prevents recovery mode hangs but requires timely user interaction
- **Auto-Timeout**: Recovery mode automatically exits after 30 seconds
- **Crash Counter**: Automatically cleared on recovery entry to prevent infinite loops
- **Failsafes**: Multiple redundant reset mechanisms prevent bricking

**Exit Methods:**
1. **Serial Command**: Send `r` via Serial Monitor, device will reboot
2. **Force Reboot**: Hold diagonal corners (Pads 1+16) for 5 seconds
3. **Auto-Timeout**: Wait 30 seconds, device auto-reboots to normal mode
4. **Note**: Crash counter is cleared on recovery entry, so next boot will be normal mode

**Serial Commands:**
- `?` - Show help and firmware version
- `v` - Show version number only
- `r` - Reboot to normal mode (crash counter already cleared)
- `d` - Diagnostics dump (crash counter, EEPROM writes, free RAM)

---

## 2. LED Codes

| Pattern | Meaning |
| :--- | :--- |
| **Solid ON** | Key(s) currently held down |
| **1-5 Blinks (Boot)** | Current octave setting (1 blink = -2, 2 = -1, 3 = 0, 4 = +1, 5 = +2) |
| **2 Blinks (Loop)** | Recovery Mode Active |
| **1 Short Blink** | Octave Shift Applied |
| **Rapid Blink (2-3s)** | **2 seconds**: EEPROM corruption detected and auto-repaired<br>**2.5 seconds**: EEPROM at 75% capacity warning (45,000 writes)<br>**3 seconds**: EEPROM write limit reached (60,000 writes), saves disabled |

---

## 3. Controls

### Octave Shifting
- **Octave UP**: Hold **Right Half (at least 6 of Pads 3,4,7,8,11,12,15,16)** simultaneously for 0.5 seconds
- **Octave DOWN**: Hold **Left Half (at least 6 of Pads 1,2,5,6,9,10,13,14)** simultaneously for 0.5 seconds
- **Range**: -2 to +2 octaves from base notes (5 total octaves)
- **Feedback**: LED blinks once when shift is applied
- **Persistence**: 
  - Settings are automatically saved 2 seconds after last octave change
  - Reduces EEPROM wear (rated for ~100,000 write cycles)
  - Current EEPROM writes are tracked internally
  - All notes are silenced during octave shifts to prevent stuck notes

---

## 4. Technical Notes

### Base Note Layout (Octave 0)
```
Pads send these MIDI notes when octave = 0:
┌────┬────┬────┬────┐
│ C3 │C#3 │ D3 │D#3 │  (48-51)
├────┼────┼────┼────┤
│G#2 │ A2 │A#2 │ B2 │  (44-47)
├────┼────┼────┼────┤
│ E2 │ F2 │F#2 │ G2 │  (40-43)
├────┼────┼────┼────┤
│ C2 │C#2 │ D2 │D#2 │  (36-39)
└────┴────┴────┴────┘
```

### Crash Protection
- Device uses a **4-second watchdog timer** in normal mode (8s in recovery mode)
- After 3 consecutive crashes (watchdog resets), automatically enters Recovery Mode
- **Brownout resets** (low USB voltage) are distinguished from crashes and don't trigger recovery
- Counter is cleared after device runs stably for 5 seconds
- Crash counter persists across normal power cycles

### EEPROM Safety & Wear Leveling
- **Wear Leveling**: Octave settings use a **marker-based ring buffer** across 16 EEPROM addresses.
  - Eliminates "hotspots" (static rotation pointers) for true uniform wear.
- **Debouncing**: 2-second delay before saving to prevent excessive writes
- **Write Counter**: Tracks total EEPROM operations (internally monitored, saturates at 65,534)
- **Auto-Repair**: Corrupted EEPROM values are automatically repaired to defaults with LED warning
- **Lifespan**: With wear leveling, ~1.6 million octave changes possible (16× improvement)
- **Write Limit**: Device stops saving after 60,000 writes and shows rapid blink warning

### MIDI Behavior
- All notes are sent on **MIDI Channel 1**
- **Boot Sequence**: Sends "All Notes Off" (CC 123) to clear any stuck notes
  - Individual Note Offs are NOT sent on boot (reduces USB MIDI flooding)
- **Octave Shifts**: Send Note Off for all 16 pads across all 5 octaves (80 messages) to prevent stuck notes
- **Note Bounds**: All MIDI notes are constrained to 0-127 range for safety
- This approach prevents stuck notes while avoiding USB buffer overflow during boot

### Firmware Version
- **Current**: v0.2.0 (Production Ready)
- **EEPROM Version**: 1 (tracked separately for data migration)
- Query version via Serial in Recovery or Verbose Mode with `v` command
- Version is embedded in firmware and displayed on boot (verbose) or recovery entry

### Watchdog Timer
- **Boot Mode**: 8-second timeout (WDTO_8S) during boot sequence for safe initialization
  - Protects against: USB enumeration hangs, POST failures, verbose mode initialization
  - Switched to 4s after successful boot
- **Normal Mode**: 4-second timeout (WDTO_4S) for runtime protection
- **Recovery Mode**: 8-second timeout (WDTO_8S) - longer to allow for Serial operations
- **Status**: Active at all times with periodic wdt_reset() calls to prevent unwanted resets
- **Safe Reset**: Uses 15ms watchdog timeout (WDTO_15MS) for rapid, reliable device reset
- **Protection**: Prevents firmware hangs from entering infinite loops or stack overflows

---

## 5. Troubleshooting

### Device enters Recovery Mode unexpectedly
- Check USB cable quality (poor cables cause brownouts)
- Try different USB port (some ports have voltage drops)
- If persists after Serial reset (`r` command), may indicate firmware bug

### Octave setting not saving
- Wait 2+ seconds after last octave change before unplugging
- If EEPROM is corrupted, device auto-repairs to octave 0 (3 blinks on boot)

### Stuck notes after unplugging
- This should not happen in v0.2.0+ (fixed with boot-time Note Off)
- If it occurs, indicates MIDI host didn't receive Note Off messages
- Most DAWs have a "Panic" button to clear stuck notes

### LED doesn't light during key presses
- Check if LED is in a special pattern (blink animation)
- LED only shows solid during key press when not animating
- This is normal behavior

### Rapid blinking LED on boot
- **2 seconds**: EEPROM corruption detected and auto-repaired to octave 0
  - Octave setting was invalid and has been reset to default
  - Device will function normally with corrected value
- **2.5 seconds**: EEPROM at 75% capacity (45,000 writes reached)
  - Early warning that EEPROM is approaching write limit
  - Device continues functioning normally
  - Consider reducing octave changes to extend EEPROM lifespan
- **3 seconds**: EEPROM write limit (60,000 writes) reached, octave saves disabled  
  - Device continues functioning normally
  - Octave changes work during current session but won't persist after reboot
  - This protects EEPROM from wear beyond rated endurance

---

## 6. Changelog

### v0.2.0 (Current - All Critique Fixes Applied)
**Critical Fixes:**
- **Fixed**: EEPROM wear leveling imbalance (Write Counter pool increased from 4 to 16)
- **Fixed**: Diagnostics command reading legacy/unused address for write counter
- **Fixed**: Memory map overlap potential by moving flags to higher addresses
- **Fixed**: POST failure logic now enters recovery mode (was bypassing checks after threshold)
- **Fixed**: safeReset() millis() rollover using TIME_ELAPSED macro with proper casting
- **Fixed**: EEPROM full flag written at 99.99% capacity (prevents power-loss race condition)
- **Fixed**: Write counter corruption now assumes 75% full (conservative safety approach)
- **Fixed**: LED pattern race condition - digitalWrite moved outside critical section
- **Fixed**: Integer promotion bugs in TIME_ELAPSED macro (cast inputs before arithmetic)
- **Fixed**: Free RAM calculation uses volatile to prevent compiler optimization
- **Fixed**: Factory reset counter now saturates at 255 instead of rolling over
- **Fixed**: Stack overflow in recovery mode now triggers LED reset instead of Serial crash
- **Fixed**: POST EEPROM test is now read-only to prevent unnecessary wear
- **Fixed**: USB enumeration wait reduced to 500ms for faster boot
- **Fixed**: Chord detection now allows 2 missed keys (threshold 6/8) for better ergonomics
- **Fixed**: Watchdog reset in safeReset() - removed premature disable
- **Fixed**: EEPROM write counter saturation with persistent full flag and LED warning
- **Fixed**: POST failure infinite loop protection with failure counter
- **Fixed**: Race condition in LED pattern setting (atomic updates)
- **Fixed**: Brownout + watchdog flag handling (no more false crash counts)
- **Fixed**: millis() rollover bugs - all comparisons now use signed arithmetic
- **Fixed**: Serial buffer overflow with null termination
- **Fixed**: Pin state cache race condition for reliable LED feedback
- **Fixed**: Recovery mode now has 8s watchdog for hang protection
- **Fixed**: Free RAM calculation platform detection (requires ATmega32U4)
- **Fixed**: MIDI note bounds checking for defense in depth
- **Fixed**: EEPROM wear leveling hotspots (removed static rotation pointers)
- **Fixed**: MIDI stuck notes during octave shift (explicit Note Offs sent before transpose)
- **Fixed**: Factory reset aggression (now only wipes managed area 0-200)
- **Fixed**: Serial buffer flushing logic in recovery mode

**Improvements:**
- **Improved**: Octave rotation happens on every save (predictable wear, no persistent counter)
- **Improved**: SPCR check runs once (was incorrectly inside pin loop)
- **Improved**: Verbose mode debounce uses delays (saves power vs busy-wait)
- **Improved**: Stack canary checked in loop() for runtime overflow detection
- **Improved**: WARN_EEPROM_WRITES auto-calculated as 75% of max (maintainability)
- **Improved**: Recovery pin constants renamed for clarity (RECOVERY_DIAGONAL_PIN_*)
- **Improved**: All delay magic numbers replaced with named constants
- **Improved**: Globals wrapped in anonymous namespace (prevents library conflicts)
- **Improved**: Reduced redundant watchdog petting in EEPROM operations
- **Improved**: Bootloader flash size validation (compile-time check for <28KB)

**Documentation:**
- **Clarified**: CC 123 support limitations (not all MIDI devices implement it)
- **Clarified**: Recovery mode 8-second watchdog requires user activity
- **Clarified**: Recovery mode watchdog behavior and auto-reboot on inactivity

**New Features:**
- **New**: Verbose diagnostic mode (hold top-left on boot)
- **New**: Power-On Self-Test (POST) validates hardware on boot
- **New**: EEPROM versioning for future data migration
- **New**: Diagnostics command in recovery mode (`d`)
- **New**: Rapid blink LED pattern for EEPROM corruption/full warnings
- **New**: Cached EEPROM values for improved performance
- **New**: Hardware platform detection (warns if not Pro Micro/Leonardo)
- **New**: Immediate LED feedback (not throttled) for <5ms latency

**Simplified:**
- **Simplified**: Recovery escape hatch - now single 5s diagonal hold (was double press)
- **Simplified**: Consistent global variable naming with g_ prefix

**Performance Improvements:**
- **Optimized**: LED update throttling (100Hz max for patterns, immediate for button feedback)
- **Optimized**: EEPROM read caching eliminates redundant 3.3ms reads
- **Optimized**: Reduced boot MIDI flood (CC 123 only, not 80+ Note Offs)
- **Optimized**: Pin reading moved to top of main loop
- **Optimized**: Watchdog pets before EEPROM writes prevent timeout

**Architecture Improvements:**
- **Enhanced**: Comprehensive inline documentation for all constants
- **Enhanced**: EEPROM memory map fully documented with POST failure tracking
- **Enhanced**: Improved serial baud consistency (115200 everywhere)
- **Enhanced**: Firmware size validation comments for flash limits
- **Enhanced**: SPI pin usage documented (pins 10,14,15,16)

### v0.1.5 (Initial Release Bugfixes)
- Removed panic chord (recovery entry only)
- Fixed WDT-based crash detection logic
- Added octave visual feedback on boot
- EEPROM write debouncing
- Individual Note Off messages
- Non-blocking boot animation
- Version reporting over serial
