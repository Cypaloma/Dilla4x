# VSCodium + PlatformIO Guide

## Installation
1. **Install VSCodium**:
   - Download from [https://vscodium.com](https://vscodium.com)
   - Follow OS-specific installation instructions

2. **Add PlatformIO IDE**:
   - Open Extensions view (Ctrl+Shift+X)
   - Search for "PlatformIO IDE" and install
   - Restart VSCodium when prompted

## Project Setup
1. **Create New Project**:
   - Open PlatformIO Home (click alien icon)
   - Select "Arduino Leonardo" as board
   - Choose "Arduino" framework

2. **Import Existing Code**:
   - Copy your `.ino` file contents into `src/main.cpp`
   - Place libraries in `lib/` directory

## PlatformIO Resources
- [Official Documentation](https://docs.platformio.org/en/latest/)
- [Arduino Debugging Tutorial](https://docs.platformio.org/en/stable/tutorials/espressif32/arduino_debugging_unit_testing.html)
- [VSCode Integration Guide](https://docs.platformio.org/en/latest/integration/ide/vscode.html)

## Workflow
- Build: Checkmark icon
- Upload: Right arrow icon
- Clean: Recycle bin icon
- Serial Monitor: Plug icon