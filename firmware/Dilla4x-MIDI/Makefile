FQBN := arduino:avr:leonardo
SKETCH := Dilla4x.ino
LIBS := "Control Surface"
PORT ?= /dev/ttyACM0
BUILD_DIR := build

.PHONY: all compile upload install-deps clean

all: compile

install-deps:
	arduino-cli core update-index
	arduino-cli core install arduino:avr
	arduino-cli lib install $(LIBS)

compile:
	mkdir -p $(BUILD_DIR)
	arduino-cli compile --fqbn $(FQBN) --warnings all --output-dir $(BUILD_DIR) ./

upload:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) --input-dir $(BUILD_DIR) ./

clean:
	rm -rf $(BUILD_DIR)
