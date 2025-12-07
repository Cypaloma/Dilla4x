# 🎛️ Dilla4x - Open Source MIDI Platform

**A minimalist, accessible 4x4 ortholinear MIDI controller inspired by classic MPC layouts.**

> *"Get ready for the up-and-coming, whatever it is." - J Dilla*

![License](https://img.shields.io/badge/license-Apache%202.0-blue.svg) ![Hardware](https://img.shields.io/badge/hardware-Open%20Source-green.svg) ![Firmware](https://img.shields.io/badge/firmware-v0.3-orange.svg)

---

## 🎵 What is Dilla4x?

The **Dilla4x** is a fully open-source hardware and software project designed to be the most accessible and hackable MIDI grid controller available. Built around the **Arduino Pro Micro**, it serves as both a serious musical instrument and a learning platform for hardware development.

### ✨ Key Features

| Feature | Description |
| :--- | :--- |
| **🎹 16 Mechanical Keys** | Uses standard **Cherry MX-compatible** keyswitches for a responsive, premium feel. |
| **♿ Accessible Design** | Unique **"chord trigger" octave shifting** allows full creative control for users with limited hand mobility or fine dexterity. |
| **🔌 Plug-and-Play** | **Class-compliant USB MIDI**. Works instantly with Ableton, Logic, FL Studio, web synths, and more. No drivers needed. |
| **🛠️ Hackable Core** | Powered by **Arduino**. Simple, robust, low-latency firmware (v0.3). Easy to modify and extend. |
| **🔓 Open Hardware** | Simple PCB and 3D-printed enclosure designs that are easy to print, assemble, and modify. |

---

## 🚀 Quick Start

Everything you need to get started is in our comprehensive **[Wiki](wiki/Home.md)**.

1.  **🛠️ Build It**
    *   Follow the **[Step-by-Step Assembly Guide](wiki/hardware/Assembly-Guide.md)** to put your hardware together.
2.  **⚡ Flash It**
    *   Upload the code using our **[Firmware Guide](wiki/development/Dilla4x_Firmware.md)**.
    *   *Current Version: Standard MIDI Firmware (v0.3)*
3.  **🎧 Play It**
    *   Learn the layout and techniques in **[How to Use Your Dilla4x](wiki/sound/How-to-Use-Dilla4x-MIDI.md)**.

---

## 🧠 Firmware & Development

The project currently runs on **Standard MIDI Firmware (v0.3)**, a stateless, low-latency engine designed for performance.

*   **💻 View Source**: [`firmware/Dilla4x-MIDI/`](firmware/Dilla4x-MIDI/)
*   **🔧 Modify**: [Arduino Development Guide](wiki/development/Arduino-Development.md) or [PlatformIO Guide](wiki/development/VSCodium-PlatformIO-MIDI-Guide.md)

### 🔮 The Road Ahead

We are actively expanding the Dilla4x ecosystem. Check [ROADMAP.md](ROADMAP.md) for full details.

- [ ] **QMK Port**: Bringing advanced keymapping (Layers, Tap Dance) to the Dilla4x.
- [ ] **Visual Arts**: Workflows for TouchDesigner, Resolume, and p5.js.
- [ ] **Ergonomics**: Low-profile enclosure designs.

---

## 📂 Repository Structure

```text
├── 3d-prints/         # STL files for the enclosure
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

This project is open source under the **Apache 2.0 License**. Contributions to hardware, firmware, and documentation are welcome!

1.  Fork the repository
2.  Create your feature branch
3.  Submit a Pull Request

---

*Dedicated to the legacy of James Dewitt Yancey.*
