# Arduino Development Setup (MIDI Firmware)

Guide for setting up the development environment for the **Dilla4x Standard MIDI Firmware (v0.3)**.

> [!NOTE]
> This guide is specific to the `firmware/Dilla4x-MIDI` codebase. Other firmwares (e.g., QMK) will use different toolchains.

## Official Resources
- [Arduino IDE Download](https://docs.arduino.cc/software/ide/)
- [Getting Started with Arduino IDE 2](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started-ide-v2)
- [Downloading and Installing Guide](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing)

## Language References
- [Programming Guide](https://docs.arduino.cc/programming/)
- [Language Reference](https://docs.arduino.cc/language-reference/)
- [Getting Started with Arduino](https://docs.arduino.cc/learn/starting-guide/getting-started-arduino/)

## Basic Setup
1. Install Arduino IDE
2. Select Board: Arduino Leonardo
3. Install **MIDIUSB** library (not Control_Surface)
4. Upload firmware from `firmware/Dilla4x-MIDI/Dilla4x-MIDI.ino`

## Step-by-Step Firmware Upload
1. Download firmware from GitHub
2. Open `Dilla4x.ino` in Arduino IDE
3. Select Tools > Board > Arduino Leonardo
4. Select correct USB port
5. Click Upload button (→ icon)

## Next Steps
- [Firmware Configuration](Dilla4x_Firmware.md)
- [Advanced Development with VSCodium](VSCodium-PlatformIO-MIDI-Guide.md)