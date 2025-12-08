# Dilla4x

A 4x4 ortholinear MIDI controller and macro pad with VIA support.

* Keyboard Maintainer: [Dilla4x Community](https://github.com/Cypaloma/Dilla4x)
* Hardware Supported: ATmega32U4 (Arduino Pro Micro)
* Hardware Availability: [Build Guide](../../wiki/hardware/Assembly-Guide.md)

> **⚠️ TESTING STATUS**: This firmware (v0.1.0) follows 2025 QMK standards (data-driven config). It should compile correctly but has not been tested on hardware yet.

> **⚡ FIRMWARE SIZE**: ATmega32U4 has limited flash (28KB). VIA + MIDI + NKRO uses ~26KB. If you encounter size errors, disable NKRO or mousekeys in VIA keymap.

## Features

- **Dual Purpose**: MIDI controller + programmable macro pad
- **VIA Support**: Real-time remapping (requires external VIA definition - see below)
- **Gaming Ready**: N-Key Rollover, mouse keys, media control
- **MIDI Notes**: Chromatic C2-D#3 (matches Dilla4x-MIDI firmware)

## Make Commands

Compile default keymap:

    make dilla4x:default

Compile VIA keymap:

    make dilla4x:via

Flash to device (enter bootloader first):

    make dilla4x:via:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold top-left key while plugging in
* **Physical reset**: Bridge RST to GND on Pro Micro twice quickly  
* **Keycode in layout**: Not implemented by default

## Default Keymap

Layer 0 - MIDI Notes (Chromatic C2 to D#3):

```
┌─────┬─────┬─────┬─────┐
│ C3  │ C#3 │ D3  │ D#3 │  MIDI 48-51
├─────┼─────┼─────┼─────┤
│ G#2 │ A2  │ A#2 │ B2  │  MIDI 44-47
├─────┼─────┼─────┼─────┤
│ E2  │ F2  │ F#2 │ G2  │  MIDI 40-43
├─────┼─────┼─────┼─────┤
│ C2  │ C#2 │ D2  │ D#2 │  MIDI 36-39
└─────┴─────┴─────┴─────┘
```

## VIA Support

**IMPORTANT**: VIA configuration is NOT stored in QMK firmware. You must:

1. Flash the `via` keymap to your device
2. Submit keyboard definition to [the-via/keyboards](https://github.com/the-via/keyboards)
3. Wait for PR approval

See [VIA_SETUP.md](keymaps/via/VIA_SETUP.md) for detailed instructions.

**Quick test** (before PR approval):
- Visit https://usevia.app/
- Go to "Design" tab
- Upload JSON from VIA_SETUP.md
- Test your layout

## Building from Source

### Prerequisites

Install QMK:

```bash
# macOS
brew install qmk/qmk/qmk

# Linux
python3 -m pip install --user qmk

# Windows - install QMK Toolbox
```

Setup QMK:

```bash
qmk setup
```

### Clone & Link

```bash
# Clone Dilla4x repo
git clone https://github.com/Cypaloma/Dilla4x.git
cd Dilla4x

# Link to QMK keyboards directory
ln -s "$(pwd)/firmware/qmk/dilla4x" ~/qmk_firmware/keyboards/dilla4x
```

### Compile

```bash
qmk compile -kb dilla4x -km via
```

### Flash

```bash
# Put device in bootloader mode, then:
qmk flash -kb dilla4x -km via
```

## Firmware Details

- **MCU**: ATmega32U4
- **Bootloader**: Caterina
- **Layout**: 4x4 ortholinear (16 keys direct pin)
- **MIDI**: Basic mode (Note On/Off, fixed velocity)
- **Debounce**: 30ms (matches Arduino firmware)

## Resources

* [QMK Documentation](https://docs.qmk.fm/)
* [VIA Configurator](https://usevia.app/)
* [Build Guide](../../wiki/hardware/Assembly-Guide.md)
* [Arduino Firmware](../Dilla4x-MIDI/)

## License

Apache 2.0 (same as parent project)
