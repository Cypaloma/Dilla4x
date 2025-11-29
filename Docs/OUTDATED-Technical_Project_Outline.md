# Dilla4x Technical Project Outline

This project creates an ecosystem of accessibility-focused open source devices to de-mystify and personalize the digital instrument, making the increasingly dominant digital music space more inclusive and interesting.

The course provides participants with resources to build their own instrument, learning from experiences to create an online repository with detailed instructions. At its extreme, it supports fully standalone digital instruments producing sound. Provided designs start simply while encouraging expansion for custom ergonomics or advanced features unavailable in mass-produced instruments.

## MIDI Controller vs. Digital Instrument

A **MIDI controller** manipulates external sound sources (e.g., synthesizer, DAW). Alone, it produces no sound.

A **digital instrument** relies on digital processing without analog components at some stage.

Example: A MIDI controller into a player piano (robotic acoustic piano using MIDI) technically makes a digital instrument.

Modern digital instruments split into:
- **Control surface**: Physical interface (keys, pads).
- **Sound generator**: Processes input to sound.

Digital shifts separated these; combined devices can control externals.

The **control surface** abstracts to any sensor/interface generating control signals: light, moisture, color, etc.—infinite possibilities for music.

## Budget Controllers & Accessibility

Popular budget MIDI: piano keybeds, percussion pads.

Alternatives often costly or software-restricted.

Good MIDI controller: Plug-and-play, no proprietary drivers/software/registration/internet.

## Default Instrument: Dilla4x

Dilla4x is a minimalist 4x4 ortholinear keypad inspired by the MPC (Music Production Center), favored for percussion by producers/controllerists.

- **Ultra-tiny footprint**, familiar layout, instantly useful.
- 16 Cherry MX keyswitches: binary state (on/off), no velocity.
- Pins: 12 digital (D2-D13), 4 analog-as-digital (A0-A3); 1 analog free.
- **Solderless**: Keyswitches pre-soldered to Dupont cables.
- **3D printed shell**: Top/bottom with plate, brass inserts, screws.
- **Firmware**: USB MIDI via Control_Surface library.

Designed for:
- Easy 3D printing.
- Roomy for beginner builds/additions.
- Solderless workflow.

Assembly: Electronics bottom, switches top, flip/connect Duponts to pins, glue MCU, screw halves, add keycaps, flash, plug.

## Provided Materials
- Arduino Pro Micro (USB-C, headers pre-soldered).
- 16 Cherry MX keyswitches on Dupont cables (hot glue strain relief).
- Keycaps.
- 3D printed Dilla4x shell with brass inserts.
- Matching screws.
- Small USB-C cable.
- Screwdriver.

**Connection**: Keyswitch pin1 → MCU pin, pin2 → GND.

## Keyswitches: Cherry MX Standard

Ubiquitous in keyboards/POS/labs. Gaming/work demand created vibrant market.

Types (digital only here):
- **Clicky**: Audible/tactile click.
- **Tactile**: Bump feedback.
- **Linear**: Smooth, bottom-out.

Recommended: Light tactile (e.g., Keychron Pro Banana), no LEDs.

**Specs**:
- 14x14mm hole (±0.05mm), corners r<0.3mm.
- Plate 1.5mm thick for clips.
- 19.05mm (0.75") center spacing.

3D plate thicker for rigidity; cutouts for clips.

Alternatives: Arcade buttons (24/30mm, screw/snap-in; larger/$$).

## Microcontroller: Arduino Pro Micro

Native USB MIDI (ATmega32U4). 12 digital GPIO, 5 analog (use as digital).

Recommend USB-C version (durable).

## Firmware Implementation

Uses **Control_Surface** library: MIDI abstraction, minimal code.

Install: Arduino IDE Library Manager.

**Include**:
```cpp
#include <Control_Surface.h>
```

**MIDI Interface**:
```cpp
USBMIDI_Interface midi;
```

**NoteButton** example:
```cpp
NoteButton key1 {2, {36, CHANNEL_1}};  // Pin 2 → C1 ch1
```

`setup()`: `pinMode(pin, INPUT_PULLUP);`

`loop()`: Library handles.

[Dilla4x-MIDI.ino](firmware/Dilla4x-MIDI/Dilla4x-MIDI.ino) ready-to-flash:
- 16 keys: Bottom-left C1(36) → right/up higher to C3(51).
- Octave shift: All top 8 (rows1-2) simultaneous → +1; bottom 8 → -1 (-2/+2 max, EEPROM).
- LED feedback, serial debug.

Flash: Board=Arduino Leonardo.

## Advanced: Customization

Define buttons by name:
```cpp
const uint8_t KEY1_PIN = 2;
NoteButton KEY1 {KEY1_PIN, {36, CHANNEL_1}};
```

## Software Integration

Pair with DAWs/synths (Ableton, Bitwig, VCV Rack). Open source support: presets/docs.

## Out of Scope (v1)
- Velocity/MPE/analog keys.
- Encoders/displays/audio out/sensors.
- Knobs/rotary controls.

Future: transport combos, expansion.

## Arcade Buttons Note
Larger (24/30mm), screw-in for thick plates. Same wiring/function.

---

**Version**: v1.0 Dilla4x Focus  
**Repo**: [Dilla4x GitHub](.)  
Print 3D files: TBA