set -e

# Configuration - Detect QMK_HOME dynamically
if [ -n "$QMK_HOME" ]; then
    # Use environment variable if set
    QMK_HOME="$QMK_HOME"
elif command -v qmk &> /dev/null && qmk config user.qmk_home &> /dev/null; then
    # Try to get from QMK config
    QMK_HOME=$(qmk config user.qmk_home 2>/dev/null | cut -d'=' -f2)
else
    # Default fallback
    QMK_HOME="$HOME/qmk_firmware"
fi

echo "Using QMK_HOME: $QMK_HOME"

RELEASE_DIR="release_builds"
PLATFORM_VERSION="v0.3.1"
MIDI_VERSION="v0.3.0"
QMK_VERSION="v0.1.1-alpha"
WEB_VERSION="v0.1.0"

echo "🛠️  Building Dilla4x Platform Release ${PLATFORM_VERSION}"
echo "=============================================="

# Ensure release directory exists
mkdir -p "$RELEASE_DIR"

# 1. Build MIDI Firmware
echo ""
echo "📦 Building Dilla4x-MIDI ${MIDI_VERSION}..."
arduino-cli compile --fqbn arduino:avr:leonardo firmware/Dilla4x-MIDI --output-dir "$RELEASE_DIR"
mv "$RELEASE_DIR/Dilla4x-MIDI.ino.hex" "$RELEASE_DIR/dilla4x-midi-${MIDI_VERSION}.hex"
rm "$RELEASE_DIR/Dilla4x-MIDI.ino.elf"
rm "$RELEASE_DIR/Dilla4x-MIDI.ino.with_bootloader.hex"
echo "✅ MIDI firmware built: dilla4x-midi-${MIDI_VERSION}.hex"

# 2. Build QMK Firmware (Unified)
echo ""
if command -v qmk &> /dev/null; then
    echo "📦 Building Dilla4x-QMK ${QMK_VERSION}..."
    ./debug_qmk_build.sh
    cp "$QMK_HOME/dilla4x_default.hex" "${RELEASE_DIR}/dilla4x-qmk-${QMK_VERSION}.hex"
    echo "✅ QMK firmware built: dilla4x-qmk-${QMK_VERSION}.hex"
else
    echo "⚠️  qmk not found. Skipping QMK build."
fi

# 3. Package Web App
echo ""
echo "📦 Packaging Web-Dilla4x ${WEB_VERSION}..."
cd tools/web-dilla4x
zip -r "../../${RELEASE_DIR}/dilla4x-web-${WEB_VERSION}.zip" . -x "*.DS_Store"
cd ../..
echo "✅ Web app packaged: dilla4x-web-${WEB_VERSION}.zip"

echo ""
echo "🎉 Build complete!"
echo "📁 Firmware files in: ${RELEASE_DIR}/"

echo ""
echo "Next steps:"
echo "1. Test firmware files on hardware"
echo "2. Create GitHub release with these files"
echo "3. Tag release with version numbers"
