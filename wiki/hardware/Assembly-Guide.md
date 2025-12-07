# Dilla4x Assembly Guide

> **Before starting:**
> - Ensure you have the [latest 3D printed parts](3D-Printing-Guide.md)
> - Verify all pieces are clean and undamaged

## Step 1: Assembling the 3D Printed Shell

### Check the Parts
1. **Inspect All Pieces**:
   - Examine the top and bottom plates
   - Ensure all heated inserts (metal pieces inside the plates) are present and properly placed

2. **Clean the Parts**:
   - Remove any leftover material from printing (small blobs/strings) to ensure smooth assembly

### Assemble the Plates
1. **Position the Plates**:
   - Place the top plate on top of the bottom plate, aligning them correctly
   - Match all screw hole positions precisely

2. **Secure with Screws**:
   - Use M3 screws through heated inserts
   - Tighten in diagonal pattern (like lug nuts) for even pressure
   - Tighten firmly but avoid over-tightening to prevent damaging plates

### Final Checks
- **Stability**: Ensure plates are securely attached with no wobble
- **Accessibility**: Confirm USB-C port is fully exposed and aligned
- **Inspection**: Verify no cracks or deformations in plastic

## Step 2: Electronic Components Setup

### Component Overview
1. **Arduino Pro Micro**:
   - The brain of your MIDI controller (ATmega32U4 @ 16MHz)
   - Handles all key inputs and MIDI communication

2. **Cherry MX Keyswitches**:
   - Mechanical switches with 4mm travel distance
   - Linear Red variant (no tactile bump)

3. **Dupont Connectors**:
   - Jumper wires for solderless connections
   - Secure crimp connections for reliable operation

### Quality Assurance Testing (Critical for DIY Builds)

Two types of shorts can occur during assembly, and each has its own diagnostic tool:

---

#### **BOTTOM SECTION TEST: Arduino Header Shorts** (Crosstalk Detector)

> [!IMPORTANT]
> **Run this test IMMEDIATELY after soldering headers** - before installing Arduino in bottom tray, before attaching any buttons.

**What This Tests**: Solder bridges between Arduino Pro Micro header pins

**Why It Matters**:
- Solder whiskers/bridges under rubber spacers are invisible from top
- Header shorts cause multiple keys to trigger together ("crosstalk")
- Testing before assembly = easy fix; testing after = full disassembly required
- **Real failure mode**: Under magnification, header joints may look clean, but traces can be shorted underneath the board on the OTHER side

**Testing Procedure**:

1. **Upload `crosstalk_detector.ino`**:
   - Located in firmware utilities folder
   - Upload to freshly-soldered Arduino (no buttons attached yet)
   - Open Serial Monitor at 115200 baud

2. **Read the Results**:
   - **✅ PASS**: `Status: Clean (No Crosstalk Detected)` → Safe to install in tray
   - **❌ FAIL**: `SHORT DETECTED: Pin X <---> Pin Y` → Rework needed

3. **If Shorts Detected**:
   - Check BOTH sides of the board (top solder joints AND traces underneath)
   - Remove solder bridges with desoldering wick/braid
   - Inspect under rubber spacers for hidden shorts
   - Re-test until completely clean
   - Flash main firmware only after passing

**How it works**: Systematically drives each pin LOW and checks if neighboring pins follow (indicating physical connection). Detects solder blobs, whiskers, flux contamination, and PCB trace damage.

> [!WARNING]
> **Even if solder joints look perfect**, shorts can exist underneath. The rubber spacers on Arduino boards can hide damaged traces. Always run this test.


### Mount Arduino Pro Micro
1. **Placement**:
   - Insert into designated space on bottom plate
   - Orient USB-C port toward housing opening
   - Ensure no components contact metal inserts

2. **Securing**:
   - Apply small dots of hot glue to board edges
   - Avoid covering USB port, reset button, or components
   - Let glue cure for 5 minutes before handling

### Connect Keyswitches

**Complete Pin Assignments**:
| Key | Pin | Key | Pin  |
|-----|-----|-----|------|
| K1  | 2   | K9  | 10   |
| K2  | 3   | K10 | 11   |
| K3  | 4   | K11 | 12   |
| K4  | 5   | K12 | 13   |
| K5  | 6   | K13 | A0   |
| K6  | 7   | K14 | A1   |
| K7  | 8   | K15 | A2   |
| K8  | 9   | K16 | A3   |

**Detailed Wiring Instructions**:
1. **Main Keys (K1-K12)**:
   - Connect each key to its digital pin using Dupont connectors:
     - Example: K1 → Pin 2 (attach female connector to switch, male to Arduino)
   - Follow numerical order from left to right, top to bottom
   - Keep wires taut but not stretched

2. **Analog Keys (K13-K16)**:
   - Connect to analog pins:
     - K13 → A0 (white wire recommended)
     - K14 → A1 (green wire recommended)
     - K15 → A2 (blue wire recommended)
     - K16 → A3 (yellow wire recommended)
   - Route these wires separately from digital lines

3. **Cable Management**:
   - Use small zip ties every 2 inches
   - Route wires along channel edges
   - Leave slight service loop near Arduino
   - Ensure no wires are pinched or under tension

## Step 3: Final Assembly

### Install Keyswitches
1. **Mount Switches**:
   - Press Cherry MX switches into top plate until they click
   - Confirm all switches sit flush with plate
   - Verify proper orientation (LED notch facing correct direction)

2. **Attach Keycaps**:
   - Align keycap stems with switch tops
   - Press firmly until they snap into place
   - Test each key for smooth operation

### Housing Closure
1. **Pre-Close Checklist**:
   - Verify no pinched wires
   - Confirm Arduino position is maintained
   - Test all key actions before sealing
   - Ensure USB cable can be inserted/removed freely

2. **Secure Housing**:
   - Align plates precisely
   - Insert and tighten all 16 screws gradually in star pattern
   - Final torque check after 24 hours (retighten if needed)

## Post-Assembly Verification
1. **Physical Test**:
   - All keys press smoothly with 4mm travel
   - No creaking or flex in housing
   - USB cable inserts/removes easily
   - No visible gaps between plates

2. **Electrical Test**:
   - Connect to computer - verify power LED illuminates
   - Check for unexpected warmth from components
   - Listen for any buzzing or crackling sounds
   
3. **Functional Testing**:
   
   **Quick Test**: Flash main firmware and test each key in your DAW or MIDI monitor software
   
   **Thorough QA** (Recommended for builders):
   - The firmware utilities include a tool called **`connection_scout`** for systematic testing
   - Upload it to your assembled device (see "Reflashing" below if main firmware is already loaded)
   - Open serial monitor (115200 baud)
   - Press each button - it will show which pin activated
   - Verify all 16 keys respond and map to correct pins
   - Check for "ghost triggers" (buttons activating without being pressed)
   
   **Expected result**: Each button press should show `ACTIVITY DETECTED ON PIN: X` with the correct pin number for that button position.
   
   If buttons don't respond or trigger wrong pins, check your Dupont connector wiring against the pin assignment table above.

---

## Troubleshooting: Keyswitch Ground Shorts

> [!WARNING]
> **TOP SECTION SHORTS - Common production issue**

**Problem**: Keyswitch positive pin shorted to ground, causing key to be "always pressed" or completely dead.

**Causes**:
- **Bare ground wire retaining heat**: Sinks through hot glue, contacts positive pin
- **Solid core wire overheating**: Wire melts through switch housing, shorting internally
- **Poor strain relief**: Hot glue not fully bonding, allowing wire movement and contact

**Symptoms**:
- Key appears "stuck" (always triggered)
- Key completely unresponsive
- Random triggering without physical press

#### **TOP SECTION TEST: Keyswitch Ground Shorts** (Connection Scout)

> [!IMPORTANT]
> Run this AFTER full assembly if keys behave strangely

**Testing Procedure**:

1. **Upload `connection_scout.ino`**:
   - May require manual reset (see "Reflashing" below)
   - Open Serial Monitor at 115200 baud

2. **Observe Behavior**:
   - **✅ GOOD**: Pin only shows activity when button physically pressed
   - **❌ BAD**: Pin shows continuous `[PIN X:0!]` without button press = shorted to ground

3. **Fix Ground Shorts**:
   - Disassemble housing
   - Inspect suspect keyswitch solder joints
   - Check for:
     - Bare ground wire touching positive pin
     - Wire sunk into switch housing
     - Failed hot glue strain relief
   - Re-solder with proper insulation and strain relief
   - Allow ALL joints to fully cool before moving wires

---

## Reflashing Diagnostic Utilities (Manual Reset Procedure)

> [!CAUTION]
> **If main firmware is already running**, the device may "soft-brick" - USB taken over by MIDI, preventing normal uploads.

**When you need this**: Uploading `crosstalk_detector` or `connection_scout` after main firmware is installed

**Manual Reset Procedure**:

1. **Open the Device**:
   - Remove screws from housing
   - Separate top and bottom sections
   - Locate Arduino Pro Micro

2. **Access Reset Pin**:
   - Find RST pad/pin on Arduino (near USB port)
   - Find GND pad/pin or any ground point

3. **Trigger Bootloader**:
   - Have upload ready in Arduino IDE (click Upload button)
   - **Quickly touch RST to GND TWICE** (double-tap within 1 second)
   - Arduino enters bootloader mode (8 second window)
   - IDE should detect port and upload immediately

4. **Alternative Method**:
   - Touch RST to GND once to reset
   - Within 8 seconds, click Upload in IDE
   - Repeat if timeout occurs

> [!TIP]
> **Use a bent paperclip or spare wire** to bridge RST and GND. Practice the timing before having a sketch ready to upload.

> [!NOTE]
> **Future hardware improvement**: Roadmap includes adding a reset button access hole in bottom plate to eliminate disassembly requirement.

👉 Next: [Arduino Development Guide](../development/Arduino-Development.md) or [How to Use Your Dilla4x](../sound/How-to-Use-Dilla4x-MIDI.md)
⚠️ **Important**: Complete software setup before first use!