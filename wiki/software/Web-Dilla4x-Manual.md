# Web Dilla4x Manual

**Web Dilla4x** is the official companion web app for the Dilla4x MIDI controller. It features a dual-mode engine: a versatile **Sampler** for chopping samples and a powerful **Synth** for playing melodies.

## Getting Started
1.  **Open the App**: Open the `index.html` file located in `tools/web-dilla4x/` in a modern browser (Chrome, Edge, or Brave recommended for Web MIDI support).
2.  **Connect MIDI**: Plug in your Dilla4x controller via USB.
    *   **Auto-Detect**: The status bar will show "MIDI Ready". The app automatically attempts to detect if you are using QMK or the custom DillaFW and adjusts the mapping accordingly.
    *   *Manual Override*: If the mapping feels wrong (e.g. pads are scattered), manually select "QMK" or "DillaFW" from the dropdown in the toolbar.
3.  **Start Audio**: Click anywhere on the page or press a pad to initialize the audio engine.

## Interface Overview
*   **Toolbar**: Access global controls like Load/Save, Main Volume, Mode Switching, and Theme toggles.
*   **The Grid**: A 4x4 interactive representation of your controller pads.
*   **Visualizer**: A real-time oscilloscope and VU meter at the bottom of the screen to visualize your sound.
*   **Sidebar**: A sliding settings panel that changes based on your current Mode and selection. Open it by clicking the "⚡ Settings" button or switching modes.

---

## Mode: Sampler
The default mode. Designed for playing one-shot samples, drums, and FX.

### 1. Loading Samples
*   **Drag & Drop**: Simply drag any audio file (`.wav`, `.mp3`, `.ogg`) from your computer onto a specific pad to load it instantly.
*   **Load Pack**: Click the "Load Pack" button to import a `.dilla` or `.zip` file containing up to 16 audio files.
*   **Global Drag**: Drag a `.dilla` or `.zip` pack anywhere onto the page background to load the entire kit at once.

### 2. Per-Pad Settings
Every pad has its own independent settings. To edit a pad, **click it** or **press it** on your controller. The Sidebar will update to show:
*   **Pitch**: Change the playback speed and pitch of the sample (0.1x to 2.0x).
*   **Attack**: Fade-in time. Increase this to soften the start of the sound (e.g. for pads or swells).
*   **Decay**: Controls how long the sample sustains. Lower this to make the sound "tighter" or "shorter".

### 3. Renaming Pads
Organize your kit by renaming pads directly.
1.  **Click** the text label on any pad (e.g., "Empty" or the filename).
2.  **Type** your new name.
3.  **Press Enter** or click away to save.

---

## Mode: Synth
Switch to **Synth Mode** using the dropdown in the toolbar to turn your Dilla4x into a melodic instrument.

### Sound Design Controls
The Sidebar provides a full subtractive synthesis engine:
*   **Waveform**: Choos between **Triangle** (mellow), **Sine** (smooth), **Square** (retro/chiptune), and **Sawtooth** (bright/edgy).
*   **Vibrato**: Adds a pulsating pitch modulation effect (LFO). Great for lead sounds.
*   **Volume**: Master volume for the synth engine.
*   **Envelope (ADSR)**:
    *   *Attack*: How fast the sound reaches full volume.
    *   *Release*: How long the sound fades out after you let go of the key.
*   **Filter**: A Low-Pass Filter to shape the brightness.
    *   *Cutoff*: Frequencies above this point are removed.
    *   *Resonance (Q)*: Emphasizes the cutoff frequency for a "squelchy" sound.

### Keyboard Layouts
You can change the note mappings in the sidebar:
*   **MPC (Up)**: Notes align chromatically starting from the bottom-left (C3) and going up. Best for melodic playing.
*   **Book (Down)**: Notes read left-to-right, top-to-bottom.

---

## Global Features

### Main Volume
A master volume slider is available in the top toolbar to control the overall output level of the app.

### Visualizer & VU Meter
*   **Oscilloscope**: The waveform display shows the shape of your sound in real-time.
*   **VU Meter**: The vertical bar next to the visualizer shows your output levels. Keep it in the green/yellow!

### Theme & Accent
*   **Dark/Light Mode**: Toggle the Sun/Moon icon to switch themes.
*   **Accent Color**: Click the color circle to pick a custom LED/Accent color for the interface. This preference is saved automatically.

### Saving Your Work
*   **Save Pack**: Click this to download your current bank of samples as a `.dilla` file. You can share this file with others or load it back later. *Note: Synth settings are not currently saved in packs.*

## Keyboard Shortcuts
Don't have your MIDI controller? You can play using your computer keyboard:
*   **Row 1**: `1` `2` `3` `4`
*   **Row 2**: `Q` `W` `E` `R`
*   **Row 3**: `A` `S` `D` `F`
*   **Row 4**: `Z` `X` `C` `V`
