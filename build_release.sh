#!/bin/bash
# Build script for creating firmware releases
# Builds both MIDI and QMK firmware for distribution

set -e

RELEASE_DIR="release_builds"
MIDI_VERSION="v0.3.0"
QMK_VERSION="v0.1.0"

echo "🛠️  Building Dilla4x Firmware Releases"
echo "======================================"
echo ""

# Create release directory
mkdir -p "$RELEASE_DIR"

# Build MIDI Firmware
echo "📦 Building Dilla4x-MIDI ${MIDI_VERSION}..."
cd firmware/Dilla4x-MIDI

# Compile using Arduino CLI (requires arduino-cli installed)
if command -v arduino-cli &> /dev/null; then
    arduino-cli compile --fqbn arduino:avr:leonardo Dilla4x-MIDI.ino --output-dir ../../$RELEASE_DIR/midi_build
    cp ../../$RELEASE_DIR/midi_build/Dilla4x-MIDI.ino.hex ../../$RELEASE_DIR/dilla4x-midi-${MIDI_VERSION}.hex
    echo "✅ MIDI firmware built: dilla4x-midi-${MIDI_VERSION}.hex"
else
    echo "⚠️  arduino-cli not found. Please build manually in Arduino IDE"
    echo "   Save as: $RELEASE_DIR/dilla4x-midi-${MIDI_VERSION}.hex"
fi

cd ../..

# Build QMK Firmware
echo ""
echo "📦 Building Dilla4x-QMK ${QMK_VERSION}..."

if command -v qmk &> /dev/null; then
    # Link keyboard if not already linked
    if [ ! -d "$HOME/qmk_firmware/keyboards/dilla4x" ]; then
        echo "   Linking keyboard to QMK directory..."
        ln -s "$(pwd)/firmware/qmk/dilla4x" "$HOME/qmk_firmware/keyboards/dilla4x"
    fi
    
    # Compile default keymap
    echo "   Building default keymap..."
    qmk compile -kb dilla4x -km default
    cp "$HOME/qmk_firmware/.build/dilla4x_default.hex" "$RELEASE_DIR/dilla4x-qmk-default-${QMK_VERSION}.hex"
    
    # Compile VIA keymap
    echo "   Building VIA keymap..."
    qmk compile -kb dilla4x -km via
    cp "$HOME/qmk_firmware/.build/dilla4x_via.hex" "$RELEASE_DIR/dilla4x-qmk-via-${QMK_VERSION}.hex"
    
    echo "✅ QMK firmware built:"
    echo "   - dilla4x-qmk-default-${QMK_VERSION}.hex"
    echo "   - dilla4x-qmk-via-${QMK_VERSION}.hex"
else
    echo "⚠️  qmk not found. Please build manually:"
    echo "   qmk compile -kb dilla4x -km default"
    echo "   qmk compile -kb dilla4x -km via"
fi

# Clean up temporary build directories
rm -rf "$RELEASE_DIR/midi_build"

echo ""
echo "🎉 Build complete!"
echo "📁 Firmware files in: $RELEASE_DIR/"
echo ""
echo "Next steps:"
echo "1. Test firmware files on hardware"
echo "2. Create GitHub release with these files"
echo "3. Tag release with version numbers"
