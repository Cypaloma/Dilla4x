# Dilla4x Firmware Releases

This directory contains pre-compiled firmware files for easy installation.

## 📥 Download Latest Release

Visit the [Releases Page](https://github.com/Cypaloma/Dilla4x/releases) to download the latest firmware.

## 🎵 Available Firmwares

### Dilla4x-MIDI (v0.3.0)
**File**: `dilla4x-midi-v0.3.0.hex`

- Dedicated MIDI controller with chord-based octave shifting
- Class-compliant USB MIDI
- Chromatic notes C2-D#3
- Accessibility-focused design
- [Usage Guide](../wiki/software/How-to-Use-Dilla4x-MIDI.md)

**Best for**: Music production, DAWs, live performance

### QMK Firmware

Due to the customizable nature of QMK and strict compilation environment requirements, we recommend building the QMK firmware from source to ensure it matches your specific layout needs.

**How to Build:**
1. Install QMK: [QMK Setup Guide](https://docs.qmk.fm/#/newbs_getting_started)
2. Setup your QMK environment (`qmk setup`).
3. Link the Dilla4x directory to QMK:
   ```bash
   ln -s /path/to/Dilla4x/firmware/qmk/dilla4x ~/qmk_firmware/keyboards/dilla4x
   ```
4. Compile:
   ```bash
   qmk compile -kb dilla4x -km default
   # or for VIA support:
   qmk compile -kb dilla4x -km via
   ```
5. Flash the resulting `.hex` file.

## 🔧 How to Flash

### Using QMK Toolbox (Windows/Mac - Easiest)

1. Download [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
2. Download your desired `.hex` file from Releases
3. Open QMK Toolbox
4. Click "Open" and select the `.hex` file
5. Check "Auto-Flash"
6. Enter bootloader on Dilla4x:
   - Hold top-left key while plugging in USB, OR
   - Bridge RST to GND twice quickly
7. Wait for "Flash complete"

### Using arduino-cli (MIDI firmware only)

```bash
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo -i dilla4x-midi-v0.3.0.hex
```

### Using qmk CLI (QMK firmware only)

```bash
qmk flash dilla4x-qmk-via-v0.1.0.hex
```

## 🆘 Troubleshooting

**Can't enter bootloader?**
- See [Recovery Guide](../firmware/Dilla4x-MIDI/utils/recovery/README.md)

**Wrong firmware flashed?**
- Just flash the other one - they're interchangeable

**Want to modify firmware?**
- See [MIDI Development Guide](../wiki/development/Dilla4x_Firmware.md)
- See [QMK README](../firmware/qmk/dilla4x/readme.md)

## 🔨 Building from Source

Instead of using pre-compiled releases, you can build the firmware yourself:

```bash
# Clone repository
git clone https://github.com/Cypaloma/Dilla4x.git
cd Dilla4x

# Run build script (requires arduino-cli and/or qmk)
./build_release.sh
```

Firmware files will be in `release_builds/` directory.

## 📋 Changelog

### v0.3.0 (MIDI) - December 2025
- Semantic versioning
- Recovery mode improvements
- Cross-platform recovery scripts

### v0.1.0 (QMK) - December 2025
- Initial QMK port
- VIA support (v3 compatible)
- Modern 2025 QMK standards
- Community layout support
- Apache 2.0 licensed
