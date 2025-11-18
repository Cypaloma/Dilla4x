# Dilla4x Firmware Documentation

## Overview

`firmware/Dilla4x.ino` is the ready, plug-and-play USB MIDI firmware for the Dilla4x controller.

- **MIDI Notes**: 16 keys, chromatic C1 (36) bottom-left → ascending right/up to ~C3 (51) top-right.
- **Octave Shift**: Chord-trigger: All 8 top-half keys (rows 1-2) within 100ms → +1 octave; bottom-half → -1. Range -2/+2, EEPROM persistent, LED feedback.
- **Serial Debug**: 9600 baud for octave/ready messages.
- **Class-compliant**: No drivers; appears as MIDI device on connect.

## Hardware Pinout

| Key |        Position         | Pin | MIDI Base Note |
|-----|-------------------------|-----|----------------|
| K1  | Row1 Col1 (top-left)    |  2  |       48       |
| K2  | Row1 Col2               |  3  |       49       |
| K3  | Row1 Col3               |  4  |       50       |
| K4  | Row1 Col4 (top-right)   |  5  |       51       |
| K5  | Row2 Col1               |  6  |       44       |
| K6  | Row2 Col2               |  7  |       45       |
| K7  | Row2 Col3               |  8  |       46       |
| K8  | Row2 Col4               |  9  |       47       |
| K9  | Row3 Col1               |  10 |       40       |
| K10 | Row3 Col2               |  11 |       41       |
| K11 | Row3 Col3               |  12 |       42       |
| K12 | Row3 Col4               |  13 |       43       |
| K13 | Row4 Col1 (bottom-left) |  A0 |       36       |
| K14 | Row4 Col2               |  A1 |       37       |
| K15 | Row4 Col3               |  A2 |       38       |
| K16 | Row4 Col4 (bottom-right)|  A3 |       39       |

**Wiring**:
- Keyswitch: Leg1 → Pin, Leg2 → GND (internal pullup).

**Pro Micro Notes**: Uses D2-D13 (digital), A0-A3 (analog-as-digital).

## Features Breakdown

### Dynamic Notes
Custom [`DynamicNoteButton`](firmware/Dilla4x.ino#L97) class:
- `INPUT_PULLUP`, edge-triggered note on/off.
- Octave offset applied realtime: `note = base + (octaveShift * 12)`.

### Octave Chord Mode
`checkOctaveChord()` polls 100Hz:
- Detects exactly 8/8 pressed in half-grid within [`OCTAVE_WINDOW_MS`](firmware/Dilla4x.ino#L78)=100ms.
- Resets on release/miss.
- LED blink, serial log.

### Persistence
EEPROM addr0: `octaveShift + 2` (0-4 → -2/+2).

## Flashing Instructions

1. **Arduino IDE**:
   - Install [`Control_Surface`](https://tttapa.github.io/Control-Surface/) via Library Manager.
   - Open [`Dilla4x.ino`](firmware/Dilla4x.ino).
   - Tools > Board > **Arduino Leonardo**.
   - Tools > Port > Select Pro Micro port.
   - Verify (✓) → Upload (→).

2. **Expected Output** (Serial Monitor 9600):
   ```
   Loaded octave shift: 0
   Dilla4x Firmware v1.0 Ready!
   Octave shift: 1  // On chord trigger
   ```

3. **Test**:
   - Connect USB-C → MIDI input in DAW.
   - Keys → notes C1-C3 (octave shiftable).

## Code Structure

```cpp
// [Includes, Pins, Globals]

// Custom DynamicNoteButton class
class DynamicNoteButton : public Element { ... }

// Utils: save/load EEPROM, LED blink, init buttons

void setup() { ... }  // Serial, load EEPROM, Control_Surface.begin(), add elements

void loop() { ... }   // Control_Surface.loop(), poll octave chords
```

**Compile Size**: Minimal, fits Pro Micro (32KB flash).

## Troubleshooting

- **No MIDI**: Check port/board; reflash; try MIDI-OX/Monitor.
- **Keys Silent**: Wiring GND? Pullup? Serial check states.
- **Octave Fail**: Press **simultaneously** <100ms; release resets.
- **Compile Error**: Control_Surface v2+ installed?

**Version**: v1.0
**License**: Apache 2.0 (see LICENSE)
**Pinout Diagram**: [PGH52004alpha.tif](../PGH52004alpha.tif) prototype scan.