# Dilla4x MIDI Controller Wiki

Welcome to the Dilla4x MIDI Controller documentation! This comprehensive guide covers everything from building to customizing your 4x4 MIDI controller.

## 🎵 What is Dilla4x?
The Dilla4x is a minimalist 4x4 ortholinear MIDI controller inspired by classic MPC layouts. It features:
- **16 Cherry MX keyswitches** in a 4x4 grid
- **Octave shift functionality** via chord triggers
- **Plug-and-play USB MIDI** compatibility
- **Open source** hardware and firmware
- **Accessible design** following anti-ableist principles

## 🚀 Quick Start Guide
1. 🧰 [Verify Kit Contents](hardware/Kit-Contents.md)
2. 🔧 [Assemble Hardware](hardware/Assembly-Guide.md)
3. 💻 [Setup Software](development/Arduino-Development.md)
4. 🎛️ [Upload Firmware](development/Dilla4x_Firmware.md)
5. 🎵 [Start Making Music](software/How-to-Use-Dilla4x-MIDI.md)


## 📚 Documentation

### Development
- [Arduino Setup](development/Arduino-Development.md)
- [VSCodium + PlatformIO (MIDI Firmware)](development/VSCodium-PlatformIO-MIDI-Guide.md)
- [Dilla4x MIDI Firmware Guide](development/Dilla4x_Firmware.md)

### Hardware
- [Complete Parts List](hardware/Kit-Contents.md)
- [Step-by-Step Assembly](hardware/Assembly-Guide.md)
- [Troubleshooting](../Troubleshooting.md)

### 🧠 Software & Manuals
- **[How to Use Dilla4x-MIDI](software/How-to-Use-Dilla4x-MIDI.md)** - Complete usage guide for the MIDI firmware (v0.3.0)
- **[How to Use Dilla4x-QMK](software/How-to-Use-Dilla4x-QMK.md)** - Complete usage guide for the QMK firmware (v0.1.1-alpha - UNTESTED)
- **[Web Dilla4x Manual](software/Web-Dilla4x-Manual.md)** - Browser-based sampler/synth companion app

### Sound & Music
- [Music Making Overview](sound/Music-Making-Overview.md)
- [Beginner's Guide](sound/Beginner-Guide.md)

### Mental Health & Accessibility
- **[Bio-Debugger](Bio-Debugger-Page-1.md)** - Access-first protocol for technical overwhelm (3-page guide)

## 🛠️ Technical Specifications
- **Microcontroller**: Arduino Pro Micro (ATmega32U4)
- **Connectivity**: USB-C
- **Keyswitches**: 16x Cherry MX compatible
- **MIDI Implementation**: USB MIDI via Control_Surface library
- **Dimensions**: Compact 3D-printed enclosure

## 🔧 Assembly Overview
The hardware build has three phases:
1. **Enclosure Assembly** - 3D printed case
2. **Electronics Installation** - Arduino & wiring
3. **Final Assembly** - Closing the housing

👉 [Full Assembly Guide](hardware/Assembly-Guide.md) (30-60 minutes)

## 💻 Software Setup
Choose your environment:
- **Beginner**: [Arduino IDE](development/Arduino-Development.md)
- **Advanced**: [VSCodium + PlatformIO](development/VSCodium-PlatformIO-MIDI-Guide.md)

## 🎧 Creative Uses
- Beat making and drum programming
- Melody and bassline creation
- Live performance control
- DAW integration
- Accessible music creation

## ⚙️ Customization
- Modify firmware key mappings
- Add LED feedback
- Create custom overlays
- Expand with additional hardware

## 👥 Community & Course
This project is part of a closed course that will be released as open source. All materials will be available for community contribution.

## 📖 Quick Reference
- **Octave Controls**:
  - Top 8 keys: +1 octave
  - Bottom 8 keys: -1 octave
  - Range: -2 to +2 octaves
- **Note Layout**: Chromatic from C1 (36) to C3 (51)

---
**Need Help?**
Check our [Troubleshooting Guide](Troubleshooting.md) or ask in the community forum!

**Contributors Welcome!**
This documentation will be available for open source community contributions.