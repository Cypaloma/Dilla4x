# Dilla4x MIDI Firmware (v0.3) Technical Documentation

Technical reference for the **Dilla4x Standard MIDI Firmware**.

> [!NOTE]
> **Scope**: This document covers the standalone MIDI firmware (`firmware/Dilla4x-MIDI`).
> Future firmwares (e.g., QMK) will be documented separately.
>
> **For user-facing instructions**, see [How to Use Your Dilla4x](../software/How-to-Use-Dilla4x-MIDI.md).  

> This document is for developers and technical users.

---

## Overview

The Dilla4x firmware implements a 16-key USB MIDI controller with chord-based octave shifting, optimized for low latency and accessibility.

**Key Specifications**:
- **Target Hardware**: Arduino Pro Micro (ATmega32U4 @ 16MHz, 5V)
- **MIDI Implementation**: Native MIDIUSB library (class-compliant USB MIDI)
- **Latency**: ~10ms total (debounce + USB polling)
- **Memory Footprint**: ~19KB flash, ~1.3KB SRAM
- **Design Philosophy**: Stateless, simple, robust

---

## Hardware Configuration

### Pin Assignments

16 keys mapped directly to digital pins with `INPUT_PULLUP`:

| Key | Position | Pin | Base Note | MIDI Note |
|-----|----------|-----|-----------|-----------|
| K1  | Row1 Col1 | 2   | C3  | 48 |
| K2  | Row1 Col2 | 3   | C#3 | 49 |
| K3  | Row1 Col3 | 4   | D3  | 50 |
| K4  | Row1 Col4 | 5   | D#3 | 51 |
| K5  | Row2 Col1 | 6   | G#2 | 44 |
| K6  | Row2 Col2 | 7   | A2  | 45 |
| K7  | Row2 Col3 | 8   | A#2 | 46 |
| K8  | Row2 Col4 | 9   | B2  | 47 |
| K9  | Row3 Col1 | 10  | E2  | 40 |
| K10 | Row3 Col2 | 16  | F2  | 41 |
| K11 | Row3 Col3 | 14  | F#2 | 42 |
| K12 | Row3 Col4 | 15  | G2  | 43 |
| K13 | Row4 Col1 | A0  | C2  | 36 |
| K14 | Row4 Col2 | A1  | C#2 | 37 |
| K15 | Row4 Col3 | A2  | D2  | 38 |
| K16 | Row4 Col4 | A3  | D#2 | 39 |

**Note Layout**: Chromatic scale, ascending from bottom-left (C2) to top-right (D#3).

**Wiring**:
- Button contact 1 → Digital pin
- Button contact 2 → GND
- Internal pullup resistors enabled (`INPUT_PULLUP`)
- Active-LOW logic (button press = pin reads LOW)

### LED Feedback

Built-in TX LED (active-LOW on PORTD bit 5):
- **Solid ON**: Key(s) pressed
- **OFF**: Idle
- **50ms blink**: Octave shift confirmed
- **Fast blink (100ms)**: Recovery mode

---

## Firmware Architecture

### Core Components

1. **Config.h**: Pin definitions, timing constants, chord masks
2. **ChordManager**: Octave shift detection state machine
3. **LedController**: TX LED manipulation via direct port access
4. **Utils**: Debouncing, time helpers
5. **main .ino**: Setup, loop, MIDI handling

### Key Design Decisions

**No EEPROM**: Device is stateless - always boots to octave 0  
**No Control_Surface library**: Custom MIDIUSB implementation for minimal latency  
**Direct port I/O for LED**: Bypasses Arduino digitalWrite() overhead  
**Watchdog timer**: 4-second timeout prevents soft-locks  

---

## MIDI Implementation

### Note Generation

**Channel**: 1 (MIDI channel 0 in code, 1-indexed in DAWs)  
**Velocity**: Fixed at 127 (maximum)  
**Note Range**: 36-51 base, expandable to 0-127 via octave shifting

**Octave Calculation**:
```cpp
transmitted_note = BASE_NOTES[key] + (octaveShift * 12)
```

Where `octaveShift` ranges from -3 to +3.

### Debouncing

**Algorithm**: Per-key timestamp-based debouncing  
**Threshold**: 30ms (configurable via `DEBOUNCE_MS`)  
**Logic**:
1. Raw pin read differs from stable state → Start timer
2. After 30ms of consistent state → Update stable state
3. Stable state change → Send MIDI event

This prevents ghost triggers from mechanical bounce while maintaining low latency.

---

## Octave Shifting System

### Chord Trigger Mechanism

**Concept**: Pressing 6+ keys on one side simultaneously shifts octave

**Configuration** (in Config.h):
```cpp
// Left half (columns 0-1): Keys 0,1,4,5,8,9,12,13
CHORD_MASK_DOWN = 0x3333

// Right half (columns 2-3): Keys 2,3,6,7,10,11,14,15  
CHORD_MASK_UP = 0xCCCC

CHORD_THRESHOLD = 6  // Minimum keys required
```

**Detection Logic**:
1. Count active keys matching each mask
2. If ≥6 keys on LEFT side → Octave down
3. If ≥6 keys on RIGHT side → Octave up
4. Release all keys → Reset detection (can re-trigger)

**Range Limits**:
- Minimum: -3 octaves (transmitted note ≥ 0)
- Maximum: +3 octaves (transmitted note ≤ 127)

**LED Feedback**: 50ms blink on shift, 300ms debounce before next shift

---

## State Machine (ChordManager)

```
IDLE ─────────────────┐
  │                    │
  │ Detect 6+ keys     │ Cancel threshold (< 2 keys)
  ▼                    │
DEBOUNCING ───────────┘
  │
  │ Hold threshold met
  ▼
TRIGGERED ────────────┐
  │                    │
  │ Send octave shift  │ Release detected
  │ Blink LED          │
  └────────────────────┘
```

**Thresholds**:
- **Trigger**: 6/8 keys on one side
- **Cancel**: < 2 keys (return to IDLE without triggering)
- **Hold time**: 300ms to prevent accidental shifts

---

## Recovery Mode

**Purpose**: Fail-safe for soft-bricked devices (e.g., USB takeover by MIDI)

**Trigger**: Hold keys 0 AND 15 during power-on  
**Behavior**:
- Enter infinite loop with fast LED blinking
- No MIDI or USB initialization
- Exposes CDC serial for Arduino IDE bootloader access
- Exit: Power cycle or successful firmware upload

**Implementation**:
```cpp
if (digitalRead(KEY_PINS[0]) == LOW && 
    digitalRead(KEY_PINS[15]) == LOW) {
  enterRecoveryMode();  // Never returns
}
```

---

## Timing & Performance

| Metric | Value | Notes |
|--------|-------|-------|
| Debounce time | 30ms | Per-key, tunable |
| Loop iteration | ~1ms | Varies with key count |
| MIDI transmission | Immediate | No buffering |
| Octave shift hold | 300ms | Prevents accidental triggers |
| Total latency | ~10-40ms | Debounce-dependent |

**Watchdog Timer**: 4 seconds, resets device on hang

---

## Diagnostic Utilities

The firmware repository includes testing tools (see `utils/` and `testing/`):

- **crosstalk_detector**: Tests Arduino header shorts before assembly
- **connection_scout**: Tests button connectivity and ground shorts
- **firmware_test**: Configurable test harness (toggle watchdog/MIDIUSB)

See [Diagnostic Utilities README](../../firmware/Dilla4x-MIDI/utils/README.md) for usage.

---

## Flashing Instructions

### Using Arduino IDE

1. **Install Dependencies**:
   - Arduino IDE 1.8.x or 2.x
   - Board: Arduino AVR Boards (built-in)
   - Library: MIDIUSB (via Library Manager)

2. **Configure**:
   - Tools → Board → "Arduino Leonardo" (Pro Micro compatible)
   - Tools → Port → Select your device (e.g., `/dev/ttyACM0`)

3. **Upload**:
   - Open `Dilla4x-MIDI.ino`
   - Verify (✓) to compile
   - Upload (→) to flash

### Using arduino-cli

```bash
cd firmware/Dilla4x-MIDI

# Compile
arduino-cli compile --fqbn arduino:avr:micro --warnings all ./

# Upload (replace port)
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./
```

### Using Makefile

```bash
cd firmware/Dilla4x-MIDI

make compile
make upload PORT=/dev/ttyACM0
```

**Expected Build Output**:
```
Sketch uses ~19KB (66%) of program storage space
Global variables use ~1.3KB (51%) of dynamic memory
```

---

## Configuration Parameters

All in `Config.h`:

| Constant | Value | Description |
|----------|-------|-------------|
| `NUM_KEYS` | 16 | Number of buttons |
| `DEBOUNCE_MS` | 30 | Debounce threshold (ms) |
| `OCTAVE_CHORD_HOLD_MS` | 300 | Minimum hold time for octave shift |
| `MIN_OCTAVE` | -3 | Lowest octave offset |
| `MAX_OCTAVE` | 3 | Highest octave offset |
| `MIDI_CHANNEL` | 0 | MIDI channel (0-indexed) |
| `CHORD_THRESHOLD` | 6 | Keys required for octave shift |

---

## Troubleshooting

### Compilation Errors

**"MIDIUSB.h not found"**  
→ Install MIDIUSB library via Arduino Library Manager

**"Board not found"**  
→ Install Arduino AVR Boards via Boards Manager

### Upload Failures

**"Device not detected"**  
→ Use manual reset: Touch RST to GND twice quickly

**"avrdude sync error"**  
→ Check USB cable (must be data cable), try different port

### Runtime Issues

**No MIDI output**  
→ Verify DAW shows "Arduino Leonardo" or "Pro Micro" as MIDI input

**Keys not responding**  
→ Run `connection_scout` utility to test hardware

**Octave shifts not working**  
→ Ensure pressing 6+ keys on one side simultaneously

---

## Version History

**v0.3 (Current)**:
- Removed Control_Surface dependency
- Native MIDIUSB implementation
- Optimized debouncing (~30% flash savings)
- Fixed LED interference with USB communication
- Improved octave shift reliability

**v0.2**:
- Added recovery mode
- Watchdog timer implementation

**v0.1**:
- Initial Control_Surface-based implementation

---

## References

- **Full Spec**: [`FIRMWARE_SPEC.md`](../../firmware/Dilla4x-MIDI/FIRMWARE_SPEC.md)
- **User Guide**: [How to Use Your Dilla4x](../software/How-to-Use-Dilla4x-MIDI.md)

- **Hardware Assembly**: [Assembly Guide](../hardware/Assembly-Guide.md)
- **Source Code**: `firmware/Dilla4x-MIDI/`

**License**: Apache 2.0 (see LICENSE)  
**Maintainer**: See repository contributors