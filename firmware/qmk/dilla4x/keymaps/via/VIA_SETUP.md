# VIA Configuration for Dilla4x

> **IMPORTANT**: VIA configuration files are NOT stored locally in QMK firmware. They must be submitted to the VIA keyboards repository.

## How VIA Works

VIA reads keyboard definitions from its own repository at [github.com/the-via/keyboards](https://github.com/the-via/keyboards), NOT from your QMK firmware directory.

## To Enable VIA Support

1. **Fork the VIA keyboards repository**:
   ```bash
   https://github.com/the-via/keyboards
   ```

2. **Create keyboard definition** at `src/dilla4x/dilla4x.json`:
   ```json
   {
     "name": "Dilla4x Controller",
     "vendorProductId": 4276281412,
     "matrix": {
       "rows": 4,
       "cols": 4
     },
     "layouts": {
       "keymap": [
         ["0,0", "0,1", "0,2", "0,3"],
         ["1,0", "1,1", "1,2", "1,3"],
         ["2,0", "2,1", "2,2", "2,3"],
         ["3,0", "3,1", "3,2", "3,3"]
       ]
     }
   }
   ```

3. **Calculate vendorProductId**:
   ```
   VID = 0xFEED = 65261
   PID = 0x4444 = 17476
   vendorProductId = (VID << 16) | PID = 4276281412
   ```

4. **Submit Pull Request** to the-via/keyboards repository

5. **Wait for approval** - Once merged, VIA will detect your keyboard

## Testing VIA Locally (Optional)

You can test VIA locally using the design tab:
1. Go to https://usevia.app/
2. Click "Design" tab
3. Upload your JSON definition
4. Test configuration

## Verifying VIA Firmware

Ensure your `via` keymap is flashed:
```bash
make dilla4x:via:flash
```

Your keyboard should appear in VIA after the definition is approved.
