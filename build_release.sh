#!/bin/bash
# Build script for creating firmware releases
# Builds both MIDI and QMK firmware for distribution

set -e

RELEASE_DIR="release_builds"
PLATFORM_VERSION="v0.3.1"
MIDI_VERSION="v0.3.0"
QMK_VERSION="v0.1.0"
WEB_VERSION="v0.1.0"

echo "🛠️  Building Dilla4x Platform Release ${PLATFORM_VERSION}"
echo "=============================================="
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
    
    # Compile unified firmware
    echo "   Building Unified QMK Firmware..."
    qmk compile -kb dilla4x -km default
    cp "$HOME/qmk_firmware/.build/dilla4x_default.hex" "$RELEASE_DIR/dilla4x-qmk-${QMK_VERSION}.hex"
    
    echo "✅ QMK firmware built: dilla4x-qmk-${QMK_VERSION}.hex"
else
    echo "⚠️  qmk not found. Please build manually:"
    echo "   qmk compile -kb dilla4x -km default"
fi

# Build Web App
echo ""
echo "📦 Packaging Web-Dilla4x ${WEB_VERSION}..."
if command -v zip &> /dev/null; then
    cd tools/web-dilla4x
    
    # Add a helpful README for the zip user
    echo "Dilla4x Web Companion (v${WEB_VERSION})" > README.txt
    echo "-----------------------------------" >> README.txt
    echo "1. Extract this zip file." >> README.txt
    echo "2. Double-click 'index.html' to launch the app." >> README.txt
    echo "3. Connect your Dilla4x via USB." >> README.txt
    
    zip -r ../../$RELEASE_DIR/dilla4x-web-${WEB_VERSION}.zip . -x "*.DS_Store"
    
    rm README.txt # Cleanup
    cd ../..
    echo "✅ Web app packaged: dilla4x-web-${WEB_VERSION}.zip"
else
    echo "⚠️  zip not found. Skipping web app packaging."
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
