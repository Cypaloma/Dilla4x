# Dilla4x Platform Release v0.3.1

This release includes the latest firmware and tools for the Dilla4x platform.

## 📥 Download Release v0.3.1
Visit the [Releases Page](https://github.com/Cypaloma/Dilla4x/releases/tag/v0.3.1) to download.

## 📦 Included Components

| Component | Version | Description |
| :--- | :--- | :--- |
| **Dilla4x-MIDI** | `v0.3.0` | Dedicated performance firmware |
| **Dilla4x-QMK** | `v0.1.0` | Programmable keyboard firmware |
| **Web-Dilla4x** | `v0.3.1` | Offline sampler/synth app |

---

## 🎵 Dilla4x-MIDI (v0.3.0)
**File**: `dilla4x-midi-v0.3.0.hex`

- Dedicated MIDI controller with chord-based octave shifting
- Class-compliant USB MIDI
- [Usage Guide](../wiki/software/How-to-Use-Dilla4x-MIDI.md)

**Best for**: Music production, DAWs, live performance

## ⌨️ Dilla4x-QMK (v0.1.0)
**File**: `dilla4x-qmk-v0.1.0.hex`

- Standard QMK firmware with VIA support enabled by default
- Fully programmable keys and layers
- [Usage Guide](../wiki/software/How-to-Use-Dilla4x-QMK.md)

**Best for**: Gaming, productivity, macros

## 🎹 Web-Dilla4x (v0.3.1)
**File**: `dilla4x-web-v0.3.1.zip`

- Offline version of the web sampler/synth
- Extract and open `index.html` in any browser
- No internet connection required

**Flashing QMK Firmware:**
1. Put device in bootloader mode (reset button twice).
2. Flash using QMK Toolbox or CLI:
   ```bash
   qmk flash dilla4x-qmk-v0.1.0.hex
   # OR with avrdude manually if needed (see above)
   ```

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
