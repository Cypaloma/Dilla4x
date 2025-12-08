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

### Dilla4x-QMK (v0.1.0)

#### Default Keymap
**File**: `dilla4x-qmk-default-v0.1.0.hex`

- MIDI notes (same as MIDI firmware)
- No VIA support
- Smaller firmware size

#### VIA Keymap (Recommended)
**File**: `dilla4x-qmk-via-v0.1.0.hex`

- Fully programmable via VIA configurator
- MIDI mode support
- N-Key Rollover (gaming)
- Mouse keys and media control
- Real-time remapping without reflashing
- [Usage Guide](../wiki/software/How-to-Use-Dilla4x-QMK.md)

**Best for**: Gaming, productivity, macros, accessibility

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
