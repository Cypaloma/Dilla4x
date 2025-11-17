# Dilla4x MIDI Controller Wiki

Welcome to the Dilla4x MIDI Controller documentation! This wiki contains comprehensive guides and technical information for building, using, and customizing your Dilla4x 4x4 MIDI controller.

## 🎵 What is Dilla4x?

The Dilla4x is a minimalist 4x4 ortholinear MIDI controller inspired by classic MPC (Music Production Center) layouts. It features:

- **16 Cherry MX keyswitches** in a 4x4 grid layout
- **Octave shift functionality** via chord triggers (top 8 keys = +1 octave, bottom 8 keys = -1 octave)
- **Plug-and-play USB MIDI** - works with any DAW or MIDI-compatible software
- **Open source hardware and firmware** - fully customizable and hackable
- **Accessible design** - designed with anti-ableist principles for maximum inclusivity

## 🚀 Quick Start

New to Dilla4x? Start here:

1. **[Getting Started Guide](Getting-Started.md)** - Step-by-step assembly instructions
2. **[Firmware Setup](Firmware.md)** - Flashing and configuring your controller
3. **[First Use](First-Use.md)** - Getting your Dilla4x working with music software

## 📚 Documentation

### Building & Assembly
- **[Getting Started Guide](Getting-Started.md)** - Complete build instructions
- **[Hardware Guide](Hardware.md)** - Detailed component information
- **[Wiring Guide](Wiring.md)** - Electronics and connections

### Software & Configuration
- **[Firmware](Firmware.md)** - Installation and customization
- **[Technical Specifications](Technical-Specifications.md)** - In-depth technical details
- **[Software Integration](Software-Integration.md)** - Using with DAWs and music software

### Troubleshooting & Support
- **[Troubleshooting Guide](Troubleshooting.md)** - Common issues and solutions
- **[FAQ](FAQ.md)** - Frequently asked questions

### Development
- **[Contributing](Contributing.md)** - How to contribute to the project
- **[Customization](Customization.md)** - Advanced modifications and expansions

## 🛠️ Features

### Core Functionality
- **16 Velocity-Free Buttons**: Binary on/off keyswitches arranged in a 4x4 grid
- **Chromatic Layout**: Notes arranged chromatically from C1 (36) to C3 (51)
- **Octave Shifting**: Press all 8 top keys for +1 octave, all 8 bottom keys for -1 octave
- **MIDI Channel 1**: Transmits on MIDI channel 1 by default
- **USB Class Compliance**: No drivers needed - works on Windows, Mac, Linux, iOS, Android

### Technical Specifications
- **Microcontroller**: Arduino Pro Micro (ATmega32U4)
- **Connectivity**: USB-C (data and power)
- **Keyswitches**: 16x Cherry MX compatible (hot-swappable)
- **Power**: 5V via USB
- **Dimensions**: Compact 3D-printed enclosure
- **MIDI Implementation**: USB MIDI via Control_Surface library

## 🎧 Creative Uses

The Dilla4x is perfect for:
- **Beat Making**: Classic MPC-style drum programming
- **Melody Creation**: Chromatic note layout for basslines and melodies
- **Live Performance**: Compact and reliable stage controller
- **Music Production**: DAW control and instrument triggering
- **Sound Design**: Triggering samples and effects
- **Accessibility**: Alternative input method for music creation

## 👥 Course & Community

This Dilla4x project is part of a closed course run. The documentation and code will be contributed to an open source repository for future use by the broader community.

- **Course Participants**: This documentation supports the current course run
- **Future Open Source**: All materials will be released as open source after the course
- **Inclusive Design**: Created with anti-ableist principles for maximum accessibility

## 🔧 Customization

The Dilla4x is designed to be fully customizable:
- **Firmware**: Open source code that you can modify and extend
- **Hardware**: Expandable design with breadboard and multiplexer support
- **Enclosure**: 3D printable case with multiple design options
- **Keyswitches**: Standard Cherry MX switches - choose your preferred feel
- **Keycaps**: Compatible with any Cherry MX keycaps

## 📖 Quick Reference

### Octave Controls
- **+1 Octave**: Hold all 8 top keys (rows 1-2) simultaneously for 100ms
- **-1 Octave**: Hold all 8 bottom keys (rows 3-4) simultaneously for 100ms
- **Range**: -2 to +2 octaves from base (4 total octave range)
- **Memory**: Octave position saved to EEPROM

### Note Layout
```
Row 1: C#5(50) D5(51)  D#5(52) E5(53)
Row 2: C5(48)  C#5(49) D5(50)  D#5(51)  
Row 3: A#4(46) B4(47)  C5(48)  C#5(49)
Row 4: A4(44)  A#4(45) B4(46)  C5(47)
```

## 📄 Legal & Licensing

- **Hardware**: Open source hardware design
- **Firmware**: Apache 2.0 License
- **Documentation**: Creative Commons Attribution
- **3D Models**: Open source design files

---

**Ready to get started?** 🎵 → [Begin with the Getting Started Guide](Getting-Started.md)

**Questions?** 💬 → [Check the FAQ](FAQ.md) or consult your course materials

**Future contributors:** 🤝 → This documentation will be available for the open source community