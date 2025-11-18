# Dilla4x Kit Contents

## Complete Package Overview

### Core Components
- **Enclosure System**:
  - Top Plate: Precision-milled ABS for Cherry MX keyswitches
  - Bottom Plate: Reinforced PETG with component mounting points
  - 16x M3 Screws & Brass Threaded Inserts (pre-installed)

- **Input System**:
  - 16x Cherry MX Mechanical Keyswitches (Linear Red)
  - 16x Custom Keycaps (Dye-sublimated PBT)
  - Silicone dampeners for silent operation

### Electronics Package
- **Control Board**:
  - Arduino Pro Micro (ATmega32U4 @ 16MHz)
  - 74HC4051 8-Channel Analog Multiplexer
  
- **Connectivity**:
  - USB-C Cable (1.8m braided nylon)
  - 40x Dupont Jumper Wires (M-M, 20cm)
  - Solderless Breadboard (400 tie-points)

### Tools & Accessories
- Included Tools:
  - Precision Screwdriver (PH1/PZ0)
  - Spare M3 Screws (Stainless Steel)

- Recommended Tools:
  - Hot Glue Gun (Low-Temp)
  - Flush Cutters (for wire trimming)
  - Digital Multimeter

## Technical Specifications

### Pin Assignments
- **Digital Inputs** (K1-K12):
  ```
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
  ```
- **Analog Inputs** (K13-K16):
  ```
  A0, A1, A2, A3
  ```

### Electrical Specifications
- Operating Voltage: 5V DC
- Current Draw: 100mA (idle), 500mA (max)
- USB Compliance: USB 2.0 Full Speed
- Debounce: 100ms hardware filtering

## Starting Assembly
1. **Component Verification**: Cross-check with this list
2. **Workspace Preparation**: Clean, well-lit area
3. **Firmware Ready**: Download from [Dilla4x Releases](https://github.com/yourrepo/releases)
4. **Driver Setup**: Install Arduino Leonardo drivers

👉 Proceed to [Step-by-Step Assembly Guide](Assembly-Guide.md)