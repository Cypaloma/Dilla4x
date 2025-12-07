# Connection Scout

Scans all digital pins to identify active button connections and verify wiring.

## Purpose

Tests **TOP SECTION** (buttons) after bottom section passes crosstalk detection.

## When to Use

- ✅ After assembling full device (buttons attached to Arduino)
- ✅ Debugging "button not responding" issues  
- ✅ Verifying pin mapping matches Config.h
- ✅ Production QA of assembled units

## How It Works

1. Configures all pins (2-21) as INPUT_PULLUP
2. Continuously scans for LOW signals (pressed buttons)
3. Reports active pins with Config.h validation
4. Shows periodic scan summary

## Expected Output

### Clean Operation
```
=== DILLA4X CONNECTION SCOUT ===
Scanning pins 2-21
Press buttons to identify pin assignments

ACTIVITY DETECTED ON PIN: 2 ✓ [Expected Key Pin]
ACTIVITY DETECTED ON PIN: 5 ✓ [Expected Key Pin]
SCAN: (All pins HIGH - No buttons pressed)
```

### Issue: Unexpected Pin
```
ACTIVITY DETECTED ON PIN: 13 ⚠ [NOT in Config.h - Check wiring]
```
**Action**: Verify wiring - this pin shouldn't have a button

### Issue: Pin Stuck LOW
```
SCAN: [PIN 7:0!] [PIN 7:0!] [PIN 7:0!] 
```
**Action**: Pin 7 shorted to ground or button stuck - check soldering/button

## Usage

```bash
# Navigate to utility
cd firmware/Dilla4x-MIDI/utils/connection_scout/

# Upload to device (replace port as needed)
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./

# Open serial monitor
arduino-cli monitor -p /dev/ttyACM0
```

## Visual Indicators

- **TX LED blinks** every 500ms (heartbeat - device is alive)
- **Serial output** shows button activity in real-time

## Config.h Pin Reference

Expected button pins:
```
Row 0: 2, 3, 4, 5
Row 1: 6, 7, 8, 9
Row 2: 10, 16, 14, 15
Row 3: A0(18), A1(19), A2(20), A3(21)
```

## Related Tools

- **Before this**: Run [`crosstalk_detector`](../crosstalk_detector/) on bottom section
- **After this**: Flash main firmware for functional testing
- **If bricked**: Use [`recovery`](../recovery/) tool

---

[← Back to Utils](../README.md)
