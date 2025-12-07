# Dilla4x - Open Source MIDI Platform

**A minimalist, accessible 4x4 ortholinear MIDI controller inspired by classic MPC layouts.**

> *"Get ready for the up-and-coming, whatever it is." - J Dilla*

---

## 🎵 What is Dilla4x?

The **Dilla4x** is a fully open-source hardware and software project designed to be the most accessible and hackable MIDI grid controller available. Built around the Arduino Pro Micro, it serves as both a serious musical instrument and a learning platform for hardware development.

### Key Features

*   **16 Mechanical Keys**: Uses standard Cherry MX-compatible keyswitches for a premium feel.
*   **Accessible Design**: Unique "chord trigger" octave shifting allows full creative control for users with limited hand mobility or fine dexterity.
*   **Plug-and-Play**: Class-compliant USB MIDI. Works instantly with Ableton, Logic, FL Studio, web synths, and more. No drivers needed.
*   **Hackable Core**:
    *   **Standard MIDI Firmware**: Simple, robust, low-latency C++ firmware (v0.3).
    *   **Future Scope**: Support for QMK and detailed guides for visual art integration strictly planned.
*   **Open Hardware**: Simple PCB and 3D-printed enclosure designs that are easy to modify.

---

## 🚀 Quick Start

Everything you need is in our comprehensive **[Wiki](wiki/Home.md)**.

1.  **Build It**: [Step-by-Step Assembly Guide](wiki/hardware/Assembly-Guide.md)
2.  **Flash It**: [Firmware Guide](wiki/development/Dilla4x_Firmware.md)
3.  **Play It**: [How to Use Your Dilla4x](wiki/sound/How-to-Use-Dilla4x-MIDI.md)

---

## 🧠 Firmware & Development

The project currently supports the **Standard MIDI Firmware (v0.3)**, a stateless, low-latency engine designed for performance.

*   **View Source**: [`firmware/Dilla4x-MIDI/`](firmware/Dilla4x-MIDI/)
*   **Modify**: [Arduino Development Guide](wiki/development/Arduino-Development.md) or [PlatformIO Guide](wiki/development/VSCodium-PlatformIO-MIDI-Guide.md)

### Road Ahead
We are actively working on:
*   **QMK Port**: Bringing advanced keymapping (Layers, Tap Dance) to the Dilla4x.
*   **Visual Arts**: Workflows for using Dilla4x with TouchDesigner, Resolume, and p5.js.
*   **Ergonomics**: Low-profile enclosure designs.

*See the full [ROADMAP.md](ROADMAP.md) for details.*

---

## 📂 Repository Structure

```text
├── firmware/          # Arduino firmware source (Standard MIDI v0.3)
├── wiki/              # Complete documentation (Build, Code, Play)
│   ├── development/   # Coding guides
│   ├── hardware/      # BOM & Assembly
│   └── sound/         # Music theory & usage guides
├── ROADMAP.md         # Future development plans
└── LICENSE            # Apache 2.0
```

---

## 🤝 Contributing

This project is open source under the **Apache 2.0 License**.
Contributions to hardware, firmware, and documentation are welcome!

1.  Fork the repository
2.  Create your feature branch
3.  Submit a Pull Request

---

*Dedicated to the legacy of James Dewitt Yancey.*
