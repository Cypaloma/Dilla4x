# How to Use Dilla4x-QMK Firmware

The **Dilla4x-QMK** firmware transforms your Dilla4x into a fully programmable input device with real-time customization via VIA. This guide covers everything from flashing to advanced usage.

---

## 📋 Table of Contents

1. [What is the QMK Firmware?](#what-is-the-qmk-firmware)
2. [Flashing the Firmware](#flashing-the-firmware)
3. [Default Keymap](#default-keymap)
4. [Using VIA for Customization](#using-via-for-customization)
5. [Use Cases](#use-cases)
6. [Keyboard Shortcuts Reference](#keyboard-shortcuts-reference)
7. [Troubleshooting](#troubleshooting)
8. [Advanced Customization](#advanced-customization)

---

## What is the QMK Firmware?

**QMK (Quantum Mechanical Keyboard)** is an open-source keyboard firmware used by thousands of custom keyboards worldwide. The Dilla4x-QMK firmware (v0.1.0) brings this powerful ecosystem to your device.

### Key Differences from MIDI Firmware

| Feature | Dilla4x-MIDI (v0.3.0) | Dilla4x-QMK (v0.1.0) |
|---------|----------------------|---------------------|
| **Primary Use** | MIDI controller for music | Programmable macro pad / gaming |
| **Customization** | Fixed layout, octave shifting via chords | Fully reprogrammable via VIA |
| **MIDI Support** | Full MIDI functionality | Optional MIDI mode |
| **N-Key Rollover** | No | Yes (gaming) |
| **Mouse Control** | No | Yes |
| **Media Keys** | No | Yes |
| **Layers** | Single layer | Unlimited (via VIA) |
| **Best For** | Music production, DAWs | Gaming, productivity, accessibility |

### When to Use QMK Firmware

Choose QMK if you want to:
- **Game**: Use as a custom gaming keypad with macros
- **Work**: Create productivity shortcuts (copy/paste, app switching, etc.)
- **Accessibility**: Remap keys for comfort or adaptive needs
- **Mix Modes**: Switch between MIDI, gaming, and macro functions

---

## Flashing the Firmware

### Prerequisites

You'll need:
- **QMK Toolbox** (Windows/Mac) or **QMK CLI** (Linux/Mac)
- **Dilla4x hardware** assembled and connected
- **Firmware file**: Pre-compiled `.hex` or build from source

### Option 1: Using QMK Toolbox (Easiest - Windows/Mac)

1. **Download QMK Toolbox**:
   - Visit: https://github.com/qmk/qmk_toolbox/releases
   - Download the latest release for your OS

2. **Get the Firmware**:
   - **Pre-compiled**: Check [Releases](https://github.com/Cypaloma/Dilla4x/releases) for `dilla4x_via.hex`
   - **Build from source**: See [QMK README](../../firmware/qmk/dilla4x/readme.md)

3. **Flash**:
   - Open QMK Toolbox
   - Click "Open" and select `dilla4x_via.hex`
   - Check "Auto-Flash"
   - **Enter bootloader** on your Dilla4x:
     - **Method 1**: Hold top-left key while plugging in USB (Bootmagic)
     - **Method 2**: Bridge RST to GND twice quickly on Pro Micro
   - Toolbox will detect and flash automatically
   - Wait for "Flash complete" message

### Option 2: Using QMK CLI (Linux/Mac/Advanced)

1. **Install QMK CLI**:
   ```bash
   # macOS
   brew install qmk/qmk/qmk
   
   # Linux
   python3 -m pip install --user qmk
   ```

2. **Setup QMK Environment**:
   ```bash
   qmk setup
   ```

3. **Link Dilla4x to QMK**:
   ```bash
   cd ~/Dilla4x
   ln -s "$(pwd)/firmware/qmk/dilla4x" ~/qmk_firmware/keyboards/dilla4x
   ```

4. **Compile and Flash**:
   ```bash
   # Compile VIA keymap
   qmk compile -kb dilla4x -km via
   
   # Enter bootloader on device, then:
   qmk flash -kb dilla4x -km via
   ```

### Verification

After flashing:
1. Unplug and replug your Dilla4x
2. Open a text editor
3. Press some keys - you should see MIDI note keycodes or letters (depending on keymap)
4. The device is now running QMK firmware!

---

## Default Keymap

The default VIA keymap starts with **MIDI notes** matching the standard Dilla4x-MIDI layout:

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

**This is just the starting point!** With VIA, you can remap these to anything.

---

## Using VIA for Customization

**VIA** is a web-based configurator that lets you remap keys in real-time without reflashing firmware.

### Setting Up VIA

1. **Flash VIA Keymap** (if not already done):
   - Follow the [Flashing section](#flashing-the-firmware) above
   - Make sure you flashed the **`via`** keymap, not `default`

2. **Open VIA Configurator**:
   - Visit: https://usevia.app/
   - Use **Chrome** or **Edge** (required for Web HID)

3. **First Time Setup**:
   - Click "Authorize device" when prompted
   - Select "Dilla4x Controller" from the list
   - **NOTE**: If not detected, see [VIA Setup Guide](../../firmware/qmk/dilla4x/keymaps/via/VIA_SETUP.md)

### Remapping Keys

1. **Select a Key**:
   - Click any key on the visual layout

2. **Choose New Function**:
   - Browse the tabs: Basic, Media, Macro, Layers, Special
   - Click the desired function

3. **Save**:
   - Changes are **instant** and saved to EEPROM
   - No need to reflash!

### Creating Layers

**Layers** let you have multiple layouts on one device (like Shift on a keyboard).

**Example: Gaming + Productivity Layers**

- **Layer 0**: MIDI notes (default)
- **Layer 1**: Gaming macros (WASD, abilities)
- **Layer 2**: Productivity (copy, paste, undo, etc.)

**To add a layer**:
1. In VIA, keys show "0" (Layer 0)
2. VIA allows dynamic layer creation
3. Assign a key to "MO(1)" (momentary Layer 1)
4. While holding that key, Layer 1 activates

### Macro Recording

VIA supports **macros** (key sequences):

1. Go to "Macros" tab in VIA
2. Click "+" to add
3. Type your sequence (e.g., `Ctrl+C {KC_DOWN} Ctrl+V`)
4. Assign macro to a key

---

## Use Cases

### 🎮 Gaming Setup

**Example: Fps Game Pad**

```
┌──────┬──────┬──────┬──────┐
│  Q   │  W   │  E   │  R   │  Abilities
├──────┼──────┼──────┼──────┤
│  A   │  S   │  D   │  F   │  Movement + Use
├──────┼──────┼──────┼──────┤
│ Ctrl │ Shift│ Space│ Tab  │  Crouch/Sprint/Jump/Map
├──────┼──────┼──────┼──────┤
│  1   │  2   │  3   │  4   │  Weapon Select
└──────┴──────┴──────┴──────┘
```

**Setup in VIA**:
- Remap each key to keyboard letters
- Enable NKRO (already enabled by default)
- Test in game

### 💼 Productivity Macros

**Example: Editing Shortcuts**

```
┌──────────┬──────────┬──────────┬──────────┐
│  Undo    │  Redo    │ Save     │ Save As  │
├──────────┼──────────┼──────────┼──────────┤
│  Cut     │  Copy    │ Paste    │ Find     │
├──────────┼──────────┼──────────┼──────────┤
│  Bold    │  Italic  │ Underline│ Link     │
├──────────┼──────────┼──────────┼──────────┤
│  Layer 0 │  Layer 1 │ Vol Down │ Vol Up   │
└──────────┴──────────┴──────────┴──────────┘
```

**Common Macros**:
- `Ctrl+Z` (Undo)
- `Ctrl+Shift+Z` (Redo)
- `Ctrl+S` (Save)
- `Ctrl+F` (Find)

### ♿ Accessibility Configuration

**One-Handed Layout Example**:

```
┌──────┬──────┬──────┬──────┐
│ Enter│ Space│ Bksp │ Esc  │  Common actions
├──────┼──────┼──────┼──────┤
│  Tab │  Up  │ Home │ End  │  Navigation
├──────┼──────┼──────┼──────┤
│ Left │ Down │ Right│ PgDn │  Arrow cluster
├──────┼──────┼──────┼──────┤
│ Copy │ Paste│ Undo │ Redo │  Edit actions
└──────┴──────┴──────┴──────┘
```

**Benefits**:
- All common functions on one hand
- Customizable to individual needs
- Mouse control available via VIA

### 🎵 MIDI Controller (Hybrid Mode)

Keep MIDI notes for music while adding shortcuts:

```
┌─────┬─────┬─────┬─────┐
│ C3  │ C#3 │ D3  │ D#3 │  Layer 0: MIDI Notes
├─────┼─────┼─────┼─────┤
│ G#2 │ A2  │ A#2 │ B2  │
├─────┼─────┼─────┼─────┤
│ E2  │ F2  │ F#2 │ G2  │
├─────┼─────┼─────┼─────┤
│ C2  │ C#2 │ D#2 │[L1] │  Hold [L1] for Layer 1
└─────┴─────┴─────┴─────┘

Hold [L1]:
┌──────┬──────┬──────┬──────┐
│ Play │ Stop │ Rec  │ Metro│  Layer 1: DAW Controls
├──────┼──────┼──────┼──────┤
│ Undo │ Redo │ Save │ Snap │
├──────┼──────┼──────┼──────┤
│ Mute │ Solo │ Arm  │ Mon  │
├──────┼──────┼──────┼──────┤
│ Vol- │ Vol+ │ Pan← │ ---- │
└──────┴──────┴──────┴──────┘
```

---

## Keyboard Shortcuts Reference

### QMK Special Keycodes

| Code | Function |
|------|----------|
| `KC_TRNS` | Transparent (passes through to layer below) |
| `MO(n)` | Momentary layer n (hold to activate) |
| `TG(n)` | Toggle layer n on/off |
| `LT(n, kc)` | Tap for keycode, hold for layer n |
| `KC_MPLY` | Media play/pause |
| `KC_VOLU` | Volume up |
| `KC_VOLD` | Volume down |
| `KC_MUTE` | Mute |

### MIDI Note Codes

All QMK MIDI notes follow this pattern:
- `MI_C_2` = C in octave 2 (MIDI 36)
- `MI_Cs_2` = C# in octave 2 (MIDI 37)
- `MI_C_3` = C in octave 3 (MIDI 48)

Full reference: [QMK MIDI Keycodes](https://docs.qmk.fm/#/feature_midi)

### Mouse Control

| Code | Function |
|------|----------|
| `KC_MS_U` | Mouse up |
| `KC_MS_D` | Mouse down |
| `KC_MS_L` | Mouse left |
| `KC_MS_R` | Mouse right |
| `KC_BTN1` | Mouse left click |
| `KC_BTN2` | Mouse right click |
| `KC_WH_U` | Scroll wheel up |
| `KC_WH_D` | Scroll wheel down |

---

## Troubleshooting

### Device Not Detected in VIA

**Problem**: VIA doesn't see your Dilla4x

**Solutions**:
1. **Check Firmware**: Ensure you flashed the **`via`** keymap, not `default`
2. **Browser**: Use Chrome or Edge (VIA requires Web HID)
3. **Permissions**: Allow browser to access USB devices
4. **Cable**: Try a different USB cable/port
5. **Manual Load**: See [VIA Setup Guide](../../firmware/qmk/dilla4x/keymaps/via/VIA_SETUP.md) for manual definition upload

### MIDI Not Working in DAW

**Problem**: DAW doesn't receive MIDI

**Solutions**:
1. **Check Keymap**: Ensure your active layer has MIDI keycodes (not regular keys)
2. **DAW Settings**: Select "Dilla4x Controller" as MIDI input device
3. **MIDI Channel**: Default is Channel 1 - verify in DAW
4. **USB Mode**: Some DAWs prefer dedicated MIDI firmware - consider Dilla4x-MIDI (v0.3.0)

### Keys Not Responding

**Problem**: Keys don't work or wrong keys trigger

**Solutions**:
1. **Reset EEPROM**: 
   - In VIA, use "Clear EEPROM" option
   - Or reflash firmware with QMK Toolbox
2. **Test in Text Editor**: Verify keys work outside specific software
3. **Check Layers**: You might be on wrong layer - press layer toggle key
4. **Physical Check**: Verify keyswitches are properly seated

### Firmware Too Large

**Problem**: "Firmware size exceeds flash" during compile

**Solutions**:
1. **Disable Features**: Edit `rules.mk`:
   ```makefile
   MOUSEKEY_ENABLE = no  # Disable mouse keys
   NKRO_ENABLE = no      # Disable NKRO
   ```
2. **Use Default Keymap**: Flash `default` instead of `via` (smaller)
3. **LTO Already Enabled**: The firmware already uses Link Time Optimization

### Can't Enter Bootloader

**Problem**: Device won't enter flashing mode

**Solutions**:
1. **Bootmagic**: Hold **top-left key** while plugging in USB
2. **Physical Reset**: 
   - Locate RST and GND pins on Pro Micro
   - Touch them together with tweezers/wire twice quickly
3. **Recovery Mode**: See [Recovery Guide](../../firmware/Dilla4x-MIDI/utils/recovery/README.md)

---

## Advanced Customization

### Building Your Own Keymap

1. **Fork the Repository**: https://github.com/Cypaloma/Dilla4x

2. **Create a Keymap**:
   ```bash
   cd ~/qmk_firmware/keyboards/dilla4x/keymaps
   cp -r via my_custom_keymap
   ```

3. **Edit `keymap.c`**:
   ```c
   const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
       [0] = LAYOUT_ortho_4x4(
           KC_Q, KC_W, KC_E, KC_R,
           KC_A, KC_S, KC_D, KC_F,
           KC_Z, KC_X, KC_C, KC_V,
           KC_1, KC_2, KC_3, MO(1)
       ),
       [1] = LAYOUT_ortho_4x4(
           KC_ESC, KC_UP, KC_HOME, KC_END,
           KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
           KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
       )
   };
   ```

4. **Compile and Flash**:
   ```bash
   qmk compile -kb dilla4x -km my_custom_keymap
   qmk flash -kb dilla4x -km my_custom_keymap
   ```

### Enabling Additional Features

Edit `~/qmk_firmware/keyboards/dilla4x/rules.mk`:

```makefile
# Add RGB underglow (if hardware supports)
RGBLIGHT_ENABLE = yes

# Add audio (if hardware supports)
AUDIO_ENABLE = yes

# Add tap dance
TAP_DANCE_ENABLE = yes
```

Then recompile.

### Using Community Layouts

Dilla4x is compatible with the `ortho_4x4` community layout:

```bash
# Use any ortho_4x4 keymap from community
qmk compile -kb dilla4x -km <community_keymap_name>
```

Browse community layouts: https://github.com/qmk/qmk_firmware/tree/master/layouts/community/ortho_4x4

---

## Additional Resources

- **QMK Documentation**: https://docs.qmk.fm/
- **VIA Configurator**: https://usevia.app/
- **QMK Discord**: https://discord.gg/qmk (community support)
- **Dilla4x Repository**: https://github.com/Cypaloma/Dilla4x
- **QMK Firmware Source**: [firmware/qmk/dilla4x](../../firmware/qmk/dilla4x/)

---

## Quick Start Checklist

- [ ] Flash the VIA keymap using QMK Toolbox or QMK CLI
- [ ] Verify device works (test keys in text editor)
- [ ] Open VIA configurator at https://usevia.app/
- [ ] Authorize device in browser
- [ ] Remap keys to your preference
- [ ] Test your layout
- [ ] Create additional layers as needed
- [ ] Save your configuration (automatic in VIA)

**You're now ready to use your Dilla4x as a fully programmable input device!**

---

*For MIDI-focused usage, see the [Dilla4x-MIDI Firmware Guide](How-to-Use-Dilla4x-MIDI.md).*
