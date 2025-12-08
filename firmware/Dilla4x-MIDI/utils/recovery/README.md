# Recovery Tool

Minimal firmware for unbricking soft-locked devices.

## Purpose

Provides a **safe idle state** when main firmware crashes or prevents USB upload.

## When to Use

- ❌ Device won't show up in Arduino IDE
- ❌ USB enumeration fails  
- ❌ Main firmware locks up device
- ❌ Normal upload fails with timeout errors

> [!IMPORTANT]
> **Two Different Recovery Mechanisms**:
> 
> 1. **This tool** (`recovery/`): Separate minimal sketch for complete unbrick
> 2. **Firmware recovery mode**: Built into main firmware (hold Keys 0+15 at boot)
> 
> Use **this tool** if firmware recovery mode doesn't work or main firmware won't let you upload.

> [!NOTE]
> **Sometimes recovery firmware must be flashed first** if current firmware utilizes USB interface, preventing normal uploads.

## Tools Included

- **`recovery.ino`**: Minimal blink sketch (TX LED only)
- **`auto_flash.sh`**: Linux automated upload script
- **`auto_flash.bat`**: Windows automated upload script
- **`auto_flash_mac.command`**: macOS automated upload script (double-clickable in Finder)

## Usage

### Linux
```bash
cd firmware/Dilla4x-MIDI/utils/recovery/
./auto_flash.sh
```

### Windows
1. Open Command Prompt or PowerShell
2. Navigate to `firmware\Dilla4x-MIDI\utils\recovery\`
3. Run `auto_flash.bat`
```cmd
cd firmware\Dilla4x-MIDI\utils\recovery
auto_flash.bat
```

### macOS
**Option A (Finder)**: Double-click `auto_flash_mac.command`  
**Option B (Terminal)**:
```bash
cd firmware/Dilla4x-MIDI/utils/recovery/
./auto_flash_mac.command
```

> [!NOTE]
> All scripts require `arduino-cli` to be installed and in your PATH.
> Install from https://arduino.github.io/arduino-cli/

### Method 1: Manual Upload

```bash
cd firmware/Dilla4x-MIDI/utils/recovery/

# Try normal upload first
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./

# If that fails, manually jump reset to ground twice (bootloader mode)
# Then immediately upload
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro ./
```

### Method 2: Automated (Recommended)
```bash
cd firmware/Dilla4x-MIDI/utils/recovery/

# Run auto-flash script (watches for ports, handles bootloader)
./auto_flash.sh

# Optional: Specify specific port
PORT_HINT=/dev/ttyACM0 ./auto_flash.sh
```

## What It Does

1. Compiles `recovery.ino` to hex
2. Watches for USB serial ports
3. Attempts upload with retries
4. Periodically triggers bootloader with 1200bps touch
5. Continues until upload succeeds

## Expected Behavior

### After Successful Upload
- **TX LED blinks** rapidly (150ms on/off)
- **RX LED stays off**
- Device appears as `/dev/ttyACM*` in Arduino IDE
- Normal firmware can now be uploaded

### If Still Failing
1. Check USB cable (must be data cable, not charge-only)
2. Try different USB port on computer
3. Verify Arduino Pro Micro isn't damaged (check for shorts/burns)
4. Try manual bootloader trigger (double-tap reset)

## Auto-Flash Script Details

**Environment variables**:
- `FQBN`: Board type (default: `arduino:avr:micro`)
- `PORT_HINT`: Specific port to target (optional)
- `BUILD_DIR`: Custom build directory (optional)

**How it works**:
- Continuously scans for ports
- Attempts rapid uploads when port detected
- Sends 1200bps reset signal to trigger bootloader
- Retries until successful

## Troubleshooting

### "No ports found"
- Device not connected or completely bricked  
- Check for power LED on Arduino
- Try different computer/USB port

### "Upload fails immediately"
- Bootloader might be corrupted  
- Need ISP programmer to reflash bootloader

### "Device reappears but still can't upload main firmware"
- Recovery is working, but main firmware has USB conflict
- Flash recovery again, then immediately upload main firmware

## Next Steps

After successful recovery:
1. Device should blink TX LED
2. Open Arduino IDE
3. Upload desired firmware
4. Test functionality with [`connection_scout`](../connection_scout/)

---

[← Back to Utils](../README.md)
