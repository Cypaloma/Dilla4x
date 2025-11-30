#!/usr/bin/env bash
set -euo pipefail

# Aggressive auto-flash helper for Pro Micro (ATmega32U4/Caterina).
# - Pre-compiles the sketch to hex.
# - Watches for the bootloader port (after a double-tap reset).
# - Performs a 1200-bps touch to hold the bootloader open longer.
# - Retries uploads rapidly while the bootloader is present.
#
# Tunables:
#   FQBN       : defaults to arduino:avr:micro (Pro Micro compatible)
#   PORT_HINT  : set to a specific port (e.g., /dev/ttyACM0) to focus on that name
#   BUILD_DIR  : override build dir if desired

FQBN="${FQBN:-arduino:avr:micro}"
SKETCH_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${BUILD_DIR:-${SKETCH_DIR}/build}"
PORT_HINT="${PORT_HINT:-}"

echo "Using board: ${FQBN}"
echo "Sketch dir: ${SKETCH_DIR}"
mkdir -p "${BUILD_DIR}"

echo "Compiling sketch..."
arduino-cli compile --fqbn "${FQBN}" --output-dir "${BUILD_DIR}" "${SKETCH_DIR}"
HEX="$(ls "${BUILD_DIR}"/*.ino.hex 2>/dev/null | head -n 1 || true)"
if [[ -z "${HEX}" || ! -f "${HEX}" ]]; then
  echo "Hex not found in ${BUILD_DIR}"
  exit 1
fi
echo "Hex: ${HEX}"

echo "Watching for ports... double-tap reset if needed."

declare -A touch_count

while true; do
  for port in /dev/ttyACM* /dev/ttyUSB* /dev/cu.usbmodem* /dev/cu.usbserial*; do
    [[ -e "${port}" ]] || continue

    # Respect a specific hint if provided.
    if [[ -n "${PORT_HINT}" && "${port}" != "${PORT_HINT}" ]]; then
      continue
    fi

    # Fast attempts on the current port (sketch or bootloader).
    for attempt in {1..3}; do
      if arduino-cli upload --fqbn "${FQBN}" --input-dir "${BUILD_DIR}" -p "${port}" "${SKETCH_DIR}"; then
        echo "Upload OK on ${port}"
        exit 0
      fi
      sleep 0.02
    done

    # Periodically poke bootloader and try again.
    touch_count["${port}"]=$(( ${touch_count["${port}"]:-0} + 1 ))
    if (( touch_count["${port}"] % 5 == 0 )); then
      # 1200 bps touch to trigger bootloader.
      stty -F "${port}" 1200 cs8 -cstopb -parenb clocal ignpar -ixon || true

      # Briefly look for a new port or reuse of same name (tight window, minimal delay).
      found=""
      for i in {1..15}; do  # ~150ms at 10ms
        for p2 in /dev/ttyACM* /dev/ttyUSB* /dev/cu.usbmodem* /dev/cu.usbserial*; do
          [[ -e "${p2}" ]] || continue
          if [[ -z "${PORT_HINT}" || "${p2}" == "${PORT_HINT}" ]]; then
            found="${p2}"
            break 2
          fi
        done
        sleep 0.01
      done

      target="${found:-$port}"
      # Rapid retries once more after touch.
      for attempt in {1..5}; do
        if arduino-cli upload --fqbn "${FQBN}" --input-dir "${BUILD_DIR}" -p "${target}" "${SKETCH_DIR}"; then
          echo "Upload OK on ${target}"
          exit 0
        fi
        sleep 0.02
      done
    fi
  done
  sleep 0.01
done
