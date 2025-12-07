# Crosstalk Detector

Systematically detects physical shorts (solder bridges) between pins.

## Purpose

Tests **BOTTOM SECTION** (Arduino + headers) for crosstalk before attaching buttons.

## When to Use

- ✅ After soldering Arduino Pro Micro to headers
- ✅ **Before** attaching top button section
- ✅ When multiple buttons trigger simultaneously (ghost presses)
- ✅ Production QA of bottom assemblies

## How It Works

1. Sets all pins to INPUT_PULLUP (safe state)
2. Drives each pin LOW one at a time
3. Checks if any other pins get pulled LOW
4. Reports physical shorts between pins

## Expected Output

### Clean Board
```
=== DILLA4X CROSSTALK DETECTOR ===
Starting Short Circuit Scan...
--- Scanning ---
Status: Clean (No Crosstalk Detected)
```

### Solder Bridge Detected
```
--- Scanning ---
SHORT DETECTED: Pin 3 (Key 1) <---> Pin 4 (Key 2)
SHORT DETECTED: Pin 8 (Key 7) <---> Pin 9 (Key 8)
```

**Action**: Inspect solder joints between reported pins - likely solder bridge or whisker

## Usage

```bash
# Navigate to utility
cd firmware/Dilla4x-MIDI/utils/crosstalk_detector/

# Upload to device
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./

# Open serial monitor
arduino-cli monitor -p /dev/ttyACM0
```

## What It Tests

- ✅ All 16 key pins from Config.h
- ✅ Pins: 2,3,4,5,6,7,8,9,10,16,14,15,A0,A1,A2,A3

## Interpreting Results

| Output | Meaning | Action |
|--------|---------|--------|
| `Status: Clean` | No shorts detected | ✅ Proceed to button assembly |
| `SHORT DETECTED` | Physical bridge between pins | ❌ Fix solder joint, retest |

## Common Causes of Shorts

1. **Solder bridges**: Excess solder connecting adjacent header pins
2. **Whiskers**: Thin solder strands bridging pins
3. **Flux residue**: Conductive flux (rare with modern flux)

## Testing Frequency

- **Always** after soldering headers
- **Always** after rework/repair
- **Once** per production unit (QA)

## Related Tools

- **After this**: Run [`connection_scout`](../connection_scout/) on full assembly
- **Before this**: Visual inspection of solder joints

---

[← Back to Utils](../README.md)
