# Dilla4x Diagnostic Utilities

Central hub for hardware diagnostics and firmware testing tools.

## Quick Decision Tree

**What are you doing?**

1. **Just finished soldering Arduino to headers (bottom section only)**
   - Use: [`crosstalk_detector`](#crosstalk_detector)
   - Purpose: Check for solder bridges between pins

2. **Assembled full unit (buttons attached to Arduino)**
   - Use: [`connection_scout`](#connection_scout)
   - Purpose: Verify button connections and pin mapping

3. **Device won't flash / USB not responding**
   - Use: [`recovery`](#recovery)
   - Purpose: Unbrick device with minimal firmware

4. **Debugging firmware logic (debounce, MIDI, etc.)**
   - Use: [`testing/firmware_test`](#firmware-test)
   - Purpose: Test firmware with configurable modes

---

## Production Testing Workflow

```
┌─────────────────────────────────────────┐
│ 1. Bottom Section QA                    │
│    ├─ Solder Arduino Pro Micro to headers│
│    └─ Run: crosstalk_detector           │
│       ✓ Clean = No shorts detected      │
│       ✗ Issue = Fix solder bridges      │
└─────────────────────────────────────────┘
                   ↓
┌─────────────────────────────────────────┐
│ 2. Full Assembly QA                     │
│    ├─ Attach top button section          │
│    └─ Run: connection_scout              │
│       ✓ Clean = All buttons respond     │
│       ✗ Issue = Check button wiring     │
└─────────────────────────────────────────┘
                   ↓
┌─────────────────────────────────────────┐
│ 3. Functional Test                      │
│    └─ Flash main firmware                │
│       ✓ Pass = Device ready for use     │
│       ✗ Bricked = Use recovery tool     │
└─────────────────────────────────────────┘
```

---

## Utility Reference

### `crosstalk_detector`
**Tests**: Bottom section (Arduino + headers)  
**Detects**: Solder bridges between pins

**When to use**:
- After soldering Arduino Pro Micro
- Before attaching buttons
- When ghost presses occur (multiple keys at once)

**Expected output**:
- ✅ **Clean**: `Status: Clean (No Crosstalk Detected)`
- ❌ **Issue**: `SHORT DETECTED: Pin X <---> Pin Y`

**Location**: [`utils/crosstalk_detector/`](file:///home/morp/Documents/coding/projects/Dilla4x/firmware/Dilla4x-MIDI/utils/crosstalk_detector/)

---

### `connection_scout`
**Tests**: Top section (button connections)  
**Detects**: Button-to-pin mappings and connection integrity

**When to use**:
- After full assembly
- When a button doesn't respond
- To verify Config.h pin mapping

**Expected output**:
- ✅ **Clean**: Only shows activity when buttons pressed
- ❌ **Issue**: Pins stuck LOW or no response

**Location**: [`utils/connection_scout/`](file:///home/morp/Documents/coding/projects/Dilla4x/firmware/Dilla4x-MIDI/utils/connection_scout/)

---

### `recovery`
**Purpose**: Unbrick device when main firmware crashes  
**Includes**: Auto-flash script for automated recovery

**When to use**:
- Device won't show up in Arduino IDE
- USB enumeration fails
- Main firmware locks up device

**How to use**:
1. Flash `recovery.ino` to device
2. If upload fails, run `./auto_flash.sh`
3. Device will blink TX LED (confirmed recovery mode)
4. Flash desired firmware

> [!NOTE]
> **Recovery vs Firmware Recovery Mode**  
> - **This tool** (`recovery/`): Separate minimal sketch for unbricking
> - **Firmware recovery mode**: Hold Keys 0+15 at boot (built into main firmware)

> [!IMPORTANT]
> **Sometimes recovery firmware must be flashed first** if the current firmware utilizes the USB interface, preventing normal uploads.

**Location**: [`utils/recovery/`](file:///home/morp/Documents/coding/projects/Dilla4x/firmware/Dilla4x-MIDI/utils/recovery/)

---

### `firmware_test`
**Purpose**: Configurable test harness for debugging firmware  
**Located in**: [`testing/firmware_test/`](file:///home/morp/Documents/coding/projects/Dilla4x/firmware/Dilla4x-MIDI/testing/firmware_test/)

**Test modes** (configure in source):
- `TEST_WATCHDOG`: Enable/disable watchdog timer
- `TEST_MIDIUSB`: Enable/disable MIDIUSB library (tests pin conflicts)
- `TEST_VERBOSE`: Detailed trace logging

**When to use**:
- Debugging debounce logic
- Testing if MIDIUSB causes issues
- Validating firmware changes

**See**: [`testing/README.md`](file:///home/morp/Documents/coding/projects/Dilla4x/firmware/Dilla4x-MIDI/testing/README.md) for full testing documentation

---

## Manual Reset Button Access

> [!WARNING]
> **Current limitation**: Reset button requires disassembly to access (must jump reset pin to ground with screwdriver).
> 
> **Future improvement** (see [ROADMAP.md](file:///home/morp/Documents/coding/projects/Dilla4x/ROADMAP.md)):  
> Add small hole in bottom plate for tac switch, allowing reset access with assembly screwdriver.

---

## Troubleshooting

### "Device not detected by Arduino IDE"
1. Check USB cable (must be data cable, not charge-only)
2. Try [`recovery`](#recovery) tool with auto-flash script
3. Manually jump reset to ground twice quickly (bootloader mode)

### "Multiple buttons trigger at once"
- Run [`crosstalk_detector`](#crosstalk_detector) on bottom section
- Look for solder bridges between pins

### "One button doesn't work"
- Run [`connection_scout`](#connection_scout)
- Check if pin shows activity when button pressed
- Verify pin matches Config.h mapping

### "Firmware behaves strangely"
- Use [`firmware_test`](#firmware-test) to isolate issue
- Test with MIDIUSB disabled, watchdog disabled, etc.

---

## Contributing

When adding new utilities:
1. Create subdirectory in `utils/`
2. Add standardized header comment (see existing utilities)
3. Create `README.md` in utility directory
4. Update this central README with decision tree entry

**See**: [ROADMAP.md](file:///home/morp/Documents/coding/projects/Dilla4x/ROADMAP.md) for planned improvements
