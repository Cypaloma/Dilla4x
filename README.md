# 🎛️ Dilla4x - Open Source Device Platform

**A minimalist, accessible 4x4 ortholinear input device inspired by classic MPC layouts.**

> *"Get ready for the up-and-coming, whatever it is." - J Dilla*

![License](https://img.shields.io/badge/license-Apache%202.0-blue.svg) ![Hardware](https://img.shields.io/badge/hardware-Open%20Source-green.svg) ![Firmware](https://img.shields.io/badge/firmware-Dual%20Mode-orange.svg)

---

## 🎵 What is Dilla4x?

The **Dilla4x** is a fully open-source hardware and software platform. Built around the **Arduino Pro Micro (ATmega32U4)**, it serves as both a serious creative tool and a learning platform for hardware development.

### ✨ Key Features

| Feature | Description |
| :--- | :--- |
| **🎹 16 Mechanical Keys** | Uses standard **Cherry MX-compatible** keyswitches for a responsive, premium feel. |
| **♿ Accessible Design** | Unique **"chord trigger" octave shifting** (MIDI firmware) or custom layouts via VIA allow full creative control for users with diverse needs. |
| **🔌 Plug-and-Play** | **USB HID/MIDI compatible**. Works instantly with DAWs, browsers, games, and creative software. No drivers needed. |
| **🛠️ Hackable Core** | Powered by **ATmega32U4**. Choose between MIDI or QMK firmware, or create your own. |
| **🔓 Open Hardware** | Simple PCB and 3D-printed enclosure designs that are easy to print, assemble, and modify. |

---

## 🚀 Quick Start

Everything you need to get started is in our comprehensive **[Wiki](wiki/Home.md)**.

1.  **🛠️ Build It**
    *   Follow the **[Step-by-Step Assembly Guide](wiki/hardware/Assembly-Guide.md)** to put your hardware together.
2.  **⚡ Flash Firmware**
    *   **Choose your firmware:**
        *   **[Dilla4x-MIDI](firmware/Dilla4x-MIDI/)** - Dedicated MIDI controller with chord-based octave shifting (v0.3.0)
        *   **[Dilla4x-QMK](firmware/qmk/dilla4x/)** - Programmable macro pad with VIA support (v0.1.0)
3.  **🎧 Use It**
    *   **MIDI Mode**: Learn the layout in **[How to Use Dilla4x-MIDI](wiki/software/How-to-Use-Dilla4x-MIDI.md)**
    *   **QMK Mode**: Remap keys with VIA - see **[QMK README](firmware/qmk/dilla4x/readme.md)**
    *   **Web App**: Try the **[Web Dilla4x Manual](wiki/software/Web-Dilla4x-Manual.md)** for browser-based synthesis

---

## 🎹 Web Dilla4x Companion App

**No software to install.** The Dilla4x comes with a powerful browser-based companion app that turns your controller into a basic **Sampler and Synthesizer** instantly.

*   **Launch it**: Open [`tools/web-dilla4x/index.html`](tools/web-dilla4x/index.html) in Chrome/Edge
*   **Features**:
    *   **Sampler**: Drag & drop WAV/MP3s, per-pad pitch/envelope controls.
    *   **Synth**: Full subtractive synth engine with A/D envelope and low-pass filter.
    *   **Visualizer**: Real-time oscilloscope and VU meter.
*   **Manual**: [Read the Web Dilla4x Guide](wiki/software/Web-Dilla4x-Manual.md)

---

## 🧠 Firmware Options

The Dilla4x supports **two firmware modes** - choose based on your use case:

### 🎵 Dilla4x-MIDI Firmware (v0.3.0)

A stateless, low-latency MIDI engine designed for musical performance.

*   **💻 Source**: [`firmware/Dilla4x-MIDI/`](firmware/Dilla4x-MIDI/)
*   **✨ Features**:
    *   Chromatic MIDI notes (C2-D#3)
    *   Chord-based octave shifting (accessibility feature)
    *   Class-compliant USB MIDI
    *   Recovery mode for failed uploads
*   **📖 Guide**: [Firmware Documentation](wiki/development/Dilla4x_Firmware.md) | [Usage Manual](wiki/software/How-to-Use-Dilla4x-MIDI.md)
*   **🔧 Modify**: [Arduino IDE Guide](wiki/development/Arduino-Development.md) | [PlatformIO Guide](wiki/development/VSCodium-PlatformIO-MIDI-Guide.md)

### ⌨️ Dilla4x-QMK Firmware (v0.1.0)

A versatile QMK-based firmware for programmable macros, gaming, and accessibility.

*   **� Source**: [`firmware/qmk/dilla4x/`](firmware/qmk/dilla4x/)
*   **✨ Features**:
    *   VIA support for real-time remapping
    *   N-Key Rollover (NKRO)
    *   Mouse keys and media control
    *   MIDI mode support
    *   Community layout compatible (ortho_4x4)
*   **📖 Guide**: [QMK README](firmware/qmk/dilla4x/readme.md) | [VIA Setup](firmware/qmk/dilla4x/keymaps/via/VIA_SETUP.md)
*   **🔧 Modify**: Standard QMK development workflow

---

## 🔮 Roadmap

We are interested in expanding the Dilla4x ecosystem. Check [ROADMAP.md](ROADMAP.md) for full details.

Future directions:
- [ ] **Visual Arts**: Workflows for TouchDesigner, Resolume, and p5.js.
- [ ] **Ergonomics**: Low-profile enclosure designs.
- [ ] **Firmware Variants**: Additional community-contributed firmware options.

---

## 📂 Repository Structure

```text
├── 3d-prints/         # STL files for the enclosure
├── firmware/
│   ├── Dilla4x-MIDI/  # Arduino MIDI firmware (v0.3.0)
│   └── qmk/dilla4x/   # QMK programmable firmware (v0.1.0)
├── tools/
│   └── web-dilla4x/   # Browser-based sampler/synth app
├── wiki/              # Complete documentation (Build, Code, Play)
│   ├── development/   # Coding guides
│   ├── hardware/      # BOM & Assembly
│   ├── software/      # Usage manuals for both firmwares
│   └── sound/         # Music theory & creative guides
├── ROADMAP.md         # Future development plans
└── LICENSE            # Apache 2.0
```

---

## 🤝 Contributing

This project is open source under the **Apache 2.0 License**. Contributions to hardware, firmware, and documentation are welcome!

1.  Fork the repository
2.  Create your feature branch
3.  Submit a Pull Request

Whether you're interested in MIDI, QMK, hardware design, or creative applications - there's room for you to contribute!

---

*Dedicated to the legacy of James Dewitt Yancey.*
