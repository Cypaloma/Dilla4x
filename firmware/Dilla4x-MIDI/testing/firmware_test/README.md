# Firmware Test Harness

Configurable test utility for debugging main firmware with toggleable features.

## Purpose

Tests firmware debounce and MIDI logic in isolation with configurable modes to identify conflicts.

## Test Modes

Configure at top of `firmware_test.ino`:

```cpp
#define TEST_WATCHDOG 0    // 1=Enable watchdog, 0=Disable
#define TEST_MIDIUSB 0     // 1=Include MIDIUSB, 0=Exclude
#define TEST_VERBOSE 1     // 1=Detailed logging, 0=Minimal
```

### Mode Descriptions

**TEST_WATCHDOG**:
- Tests if watchdog timer interferes with pin reading
- Disable if you suspect watchdog causing resets

**TEST_MIDIUSB**:
- Tests if MIDIUSB library conflicts with digitalRead
- Disable to isolate USB/pin interaction issues

**TEST_VERBOSE**:
- Enable: Shows debounce state transitions and periodic status
- Disable: Only shows MIDI events

## Expected Output

### With TEST_VERBOSE=1
```
=== DILLA4X FIRMWARE TEST HARNESS ===
Configuration:
  Watchdog: DISABLED
  MIDIUSB: DISABLED
  Verbose: ENABLED
  Debounce: 30 ms

[DEBOUNCE] Key 0 -> PRESSED
[MIDI] Key 0 (Pin 2) -> NOTE ON
RAW: 0x1 STABLE: 0x1 LAST: 0x1
[DEBOUNCE] Key 0 -> RELEASED
[MIDI] Key 0 (Pin 2) -> NOTE OFF
```

### With TEST_VERBOSE=0
```
[MIDI] Key 3 (Pin 5) -> NOTE ON
[MIDI] Key 3 (Pin 5) -> NOTE OFF
```

## Common Test Scenarios

### Test 1: Isolate MIDIUSB Pin Conflict
```cpp
#define TEST_WATCHDOG 0
#define TEST_MIDIUSB 0    // Disable MIDIUSB
#define TEST_VERBOSE 1
```
**Goal**: See if buttons work without MIDIUSB library

### Test 2: Test Watchdog Impact
```cpp
#define TEST_WATCHDOG 1    // Enable watchdog
#define TEST_MIDIUSB 0
#define TEST_VERBOSE 1
```
**Goal**: See if watchdog causes resets during operation

### Test 3: Production-like Environment
```cpp
#define TEST_WATCHDOG 1
#define TEST_MIDIUSB 1
#define TEST_VERBOSE 0
```
**Goal**: Test configuration matching main firmware

## Usage

```bash
cd firmware/Dilla4x-MIDI/testing/firmware_test/

# Edit firmware_test.ino to set test flags

# Upload
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./

# Monitor output
arduino-cli monitor -p /dev/ttyACM0
```

## Interpreting Results

| Output | Meaning | Action |
|--------|---------|--------|
| `[DEBOUNCE]` messages | Keys stabilizing correctly | ✅ Debounce logic working |
| `[MIDI]` messages | MIDI events firing | ✅ State machine working |
| `RAW != STABLE` for long time | Debounce not settling | ❌ Check DEBOUNCE_MS value |
| No output on press | Pin not reading LOW | ❌ Check hardware with connection_scout |

## Relationship to Main Firmware

This test harness uses **EXACT COPY** of:
- `Config.h` constants
- `readPins()` function
- Debounce state machine logic
- MIDI trigger logic

**Differences**:
- Adds serial trace output
- Makes watchdog/MIDIUSB toggleable
- No actual MIDI output (just traces)

## Next Steps

After identifying issue:
1. Fix main firmware based on findings
2. Re-test with this harness
3. Deploy to device
4. Validate with [`connection_scout`](../../utils/connection_scout/)

---

[← Back to Testing](../README.md)
