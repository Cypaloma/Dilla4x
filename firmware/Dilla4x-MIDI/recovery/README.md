# Recovery System for Dilla4x Firmware

## Purpose

This recovery system provides a **guaranteed way to flash firmware** to Arduino Pro Micro (ATmega32U4) devices, even when they are "soft-bricked" by USB MIDI firmware that doesn't expose a CDC serial port.

## The Problem

### Why USB MIDI Devices Are Hard to Flash

The Dilla4x main firmware uses `Control_Surface` library with `USBMIDI_Interface`, which creates a **pure MIDI device**. This has a critical implication:

- **No Serial Port**: USB MIDI devices do not enumerate as `/dev/ttyACM*` (Linux) or similar CDC serial ports.
- **No Bootloader Trigger**: `arduino-cli upload` (and Arduino IDE) typically trigger the Caterina bootloader by:
  1. Opening the CDC serial port at **1200 bps**
  2. Closing it (this signals the bootloader to activate)
  3. Waiting for the bootloader port to appear
  4. Uploading to the bootloader

**When there's no serial port, this process fails completely.**

### The Caterina Bootloader Window

The ATmega32U4's Caterina bootloader:
- Activates for **~8 seconds** after the 1200-bps touch or a double-tap reset
- Re-enumerates the USB device (sometimes with the same port name, sometimes different)
- Has **tens to hundreds of milliseconds** of latency due to USB re-enumeration and udev rules
- **Requires precise timing** to catch it before it times out and returns to the sketch

---

## The Solution

### `recovery.ino` - Minimal Blink Sketch

**Purpose**: A minimal, bootloader-friendly sketch that:
- Blinks **only the TX LED** using the `TXLED0/1` macros (active-low)
- Keeps the **RX LED off** to avoid the ambiguity of `LED_BUILTIN`
- Does **nothing else** - no USB MIDI, no complex logic

**When to Use**:
1. You've successfully entered the bootloader (via double-tap or `auto_flash.sh`)
2. You want to flash a "safe" sketch that won't lock you out again
3. You're testing hardware or need a known-good baseline

**Usage**:
```bash
cd recovery
arduino-cli compile --fqbn arduino:avr:micro .
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro .
```

---

### `auto_flash.sh` - Aggressive Auto-Flash Script

**Purpose**: Automatically catch the bootloader window and flash `recovery.ino` without manual timing.

#### How It Works

1. **Pre-Compile**: Compiles `recovery.ino` to hex once (avoid recompiling during the fast loop)

2. **Port Scanning**: Continuously scans for serial ports (`/dev/ttyACM*`, `/dev/ttyUSB*`, etc.)

3. **Two-Pronged Attack**:
   - **Fast Upload Attempts**: Tries 3 rapid uploads on each detected port (catches already-active bootloader)
   - **1200-bps Touch** (every 5th cycle per port):
     - Opens the port at 1200 bps to trigger bootloader
     - Waits briefly (~150ms) for bootloader re-enumeration
     - Bursts 5 rapid upload attempts to catch the bootloader window

4. **No Port Blacklisting**: Unlike naive scripts, this **keeps retrying the same port** because:
   - The bootloader often reuses the same port name
   - The bootloader window is brief (~8 seconds)
   - Blacklisting makes you miss the window

5. **Success**: Exits immediately once upload succeeds

#### Usage

**Basic (scans all ports)**:
```bash
sudo ./auto_flash.sh
```

**Focused (target specific port)**:
```bash
sudo PORT_HINT=/dev/ttyACM0 ./auto_flash.sh
```

**With Custom Board**:
```bash
sudo FQBN=arduino:avr:leonardo ./auto_flash.sh
```

#### Requirements
- **Root/Permissions**: Must be able to access `/dev/ttyACM*` and manipulate port settings (`stty`)
  - Add your user to the `dialout` group: `sudo usermod -aG dialout $USER` (then log out/in)
  - **OR** run with `sudo`

- **Arduino CLI**: Must have `arduino-cli` installed with the `arduino:avr` core

#### Workflow for Bricked Devices

1. **Run the script**:
   ```bash
   sudo ./auto_flash.sh
   ```

2. **Trigger bootloader** (one of these methods):
   - **Double-tap reset**: Short the `RST` pin to `GND` twice quickly (< 0.5s apart)
   - **Wait for periodic touch**: The script will automatically try the 1200-bps touch every few cycles

3. **Visual Confirmation**:
   - **Bootloader Active**: The onboard LED (usually RX) will "breathe" or pulse in a heartbeat pattern
   - **Upload Success**: Script prints `"Upload OK on /dev/ttyACM*"` and exits
   - **Recovery Sketch Running**: TX LED blinks steadily at ~150ms intervals

4. **Verify**:
   ```bash
   arduino-cli board list
   ```
   You should see a serial port appear (because `recovery.ino` doesn't use USB MIDI).

---

## LED Behavior Guide

| State | TX LED | RX LED | Meaning |
|-------|--------|--------|---------|
| **Bootloader** | Off | Breathing/Pulsing | Caterina bootloader active (~8s window) |
| **Recovery Sketch** | Blinking (150ms) | Off | `recovery.ino` running successfully |
| **Main MIDI Firmware** | Varies | Varies | Application-specific (check main `FIRMWARE_SPEC.md`) |
| **Both Solid** | On | On | Usually means `LED_BUILTIN` misuse or hardware issue |

---

## Troubleshooting

### "No boards found" or "Port not appearing"

**Likely Causes**:
1. **USB cable is charge-only** (no data lines) - try a different cable
2. **Driver issues** - check `dmesg | tail` for USB enumeration messages
3. **Board is genuinely bricked** (bootloader corrupted) - requires ICSP/ISP programmer

### "Programmer not responding"

**Causes**:
- Tried to upload while sketch is running (not in bootloader mode)
- Bootloader window expired (8 seconds passed)

**Solution**:
- Use `auto_flash.sh` - it will retry automatically
- Double-tap reset and try again immediately

### Script keeps running but never succeeds

**Causes**:
1. **No double-tap**: You need to manually trigger the bootloader at least once
2. **Wrong FQBN**: If you're using a Leonardo instead of Pro Micro, set `FQBN=arduino:avr:leonardo`
3. **Port permissions**: Make sure you're running with `sudo` or in the `dialout` group

---

## Technical Notes

### Why Not Just Use Software Recovery Mode?

The main firmware's software "recovery mode" (holding specific buttons at power-on) has limitations:

1. **No CDC Serial Exposure**: My original implementation just blinked LEDs - it didn't create a CDC serial port, so uploads were still impossible
2. **Hardware Dependency**: Requires correctly wired buttons with correct polarity (Active-High vs Active-Low)
3. **LED_BUILTIN Issues**: On Pro Micro, `LED_BUILTIN` behaves unexpectedly, making visual feedback unreliable

**This recovery system bypasses all of these issues** by accessing the **hardware bootloader** directly.

### Caterina Bootloader Behavior

The Caterina bootloader on ATmega32U4:
- **Activation**: Triggered by 1200-bps touch on CDC serial or double-tap reset
- **Duration**: ~8 seconds (can vary by manufacturer)
- **USB Re-enumeration**: May appear as the same port or a new port
- **Timing-Sensitive**: USB enumeration + udev rules add 10-100ms latency
- **No Retries**: If you miss the window, the sketch resumes

This is why aggressive, rapid retry logic (like `auto_flash.sh`) is necessary.

---

## Best Practices

1. **Always Flash Recovery First**: After bricking, flash `recovery.ino` before attempting to flash the main firmware again
2. **Test Hardware with Recovery**: Use the simple blink to verify your Pro Micro works before loading complex code
3. **Keep Recovery Accessible**: Don't delete this folder - you'll need it again
4. **Verify Serial Port Appears**: After flashing `recovery.ino`, verify with `arduino-cli board list` that a serial port exists before moving to the main firmware

---

## Future Improvements

Consider these enhancements to the main firmware to prevent soft-bricking:

1. **Dual-Mode USB**: Use `USBCore` to expose **both** MIDI and CDC Serial simultaneously (requires custom USB descriptors)
2. **Safe Boot Delay**: Add a 3-5 second delay at startup where the device is in CDC Serial mode before switching to MIDI
3. **Better Software Recovery**: Make recovery mode expose CDC Serial instead of just blinking LEDs
4. **Hardware Recovery Button**: Dedicate a pin (checked during `setup()`) that forces CDC Serial mode

For now, this recovery system provides a **guaranteed escape hatch** for any soft-brick scenario.
