#!/usr/bin/env bash
# ========================================================================
#  Dilla4x Recovery Auto-Flash for macOS
#  Compiles and uploads recovery.ino to an ATmega32U4 (Pro Micro)
#  
#  This script is designed to be double-clickable in Finder (.command file)
# ========================================================================
set -euo pipefail

# Tunables (override via environment variables)
FQBN="${FQBN:-arduino:avr:micro}"
SKETCH_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${BUILD_DIR:-${SKETCH_DIR}/build}"
PORT_HINT="${PORT_HINT:-}"

echo "[Recovery] Board: ${FQBN}"
echo "[Recovery] Sketch: ${SKETCH_DIR}"
mkdir -p "${BUILD_DIR}"

echo "[Recovery] Compiling sketch..."
if ! arduino-cli compile --fqbn "${FQBN}" --output-dir "${BUILD_DIR}" "${SKETCH_DIR}"; then
  echo "[Recovery] Compilation failed. Make sure arduino-cli is installed."
  read -p "Press Enter to exit..."
  exit 1
fi

HEX="$(ls "${BUILD_DIR}"/*.ino.hex 2>/dev/null | head -n 1 || true)"
if [[ -z "${HEX}" || ! -f "${HEX}" ]]; then
  echo "[Recovery] Hex not found in ${BUILD_DIR}"
  read -p "Press Enter to exit..."
  exit 1
fi
echo "[Recovery] Hex: ${HEX}"

echo "[Recovery] Scanning for ports... Double-tap reset if needed."

declare -A touch_count 2>/dev/null || touch_count=""

while true; do
  # macOS serial ports for Pro Micro (Caterina bootloader)
  for port in /dev/cu.usbmodem* /dev/tty.usbmodem*; do
    [[ -e "${port}" ]] || continue

    # Respect a specific hint if provided.
    if [[ -n "${PORT_HINT}" && "${port}" != "${PORT_HINT}" ]]; then
      continue
    fi

    echo "[Recovery] Trying port ${port}..."

    # Fast attempts on the current port (sketch or bootloader).
    for attempt in {1..3}; do
      if arduino-cli upload --fqbn "${FQBN}" --input-dir "${BUILD_DIR}" -p "${port}" "${SKETCH_DIR}" 2>/dev/null; then
        echo "[Recovery] SUCCESS on ${port}"
        read -p "Press Enter to exit..."
        exit 0
      fi
      sleep 0.1
    done

    # Trigger bootloader via 1200 bps touch
    stty -f "${port}" 1200 cs8 -cstopb -parenb clocal ignpar -ixon 2>/dev/null || true
    sleep 0.5

    # Retry after bootloader trigger
    for attempt in {1..5}; do
      for p2 in /dev/cu.usbmodem* /dev/tty.usbmodem*; do
        [[ -e "${p2}" ]] || continue
        if arduino-cli upload --fqbn "${FQBN}" --input-dir "${BUILD_DIR}" -p "${p2}" "${SKETCH_DIR}" 2>/dev/null; then
          echo "[Recovery] SUCCESS on ${p2}"
          read -p "Press Enter to exit..."
          exit 0
        fi
      done
      sleep 0.1
    done
  done
  sleep 0.5
done
