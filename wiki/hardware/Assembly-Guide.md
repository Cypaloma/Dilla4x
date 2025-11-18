# Dilla4x Assembly Guide

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
   - Test each key in serial monitor/MIDI software

👉 Next: [Arduino Development Guide](Arduino-Development.md)
⚠️ **Important**: Complete software setup before first use!