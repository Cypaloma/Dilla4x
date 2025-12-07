# Dilla4x Development Roadmap

Future improvements and planned development for the Dilla4x MIDI controller.

---

## Priority 1: Hardware Improvements

### Reset Button Access Hole
**Status**: 🔴 Not Started  
**Priority**: High  
**Effort**: Low (hardware only)

**Problem**:
Currently, accessing the reset pin to short it and load another sketch to the Arduino requires full disassembly. To enter bootloader mode or trigger recovery, users must:
1. Remove screws
2. Separate top and bottom sections
3. Jump reset pin to ground with screwdriver
4. Reassemble

This is cumbersome for development and production QA.

**Proposed Solution**:
Add a small hole in the bottom plate of the enclosure for a tac switch:
- **Location**: Aligned with Arduino Pro Micro reset button
- **Switch**: Small tac switch glued to bottom plate interior
- **Access**: Accessible with same screwdriver used for assembly screws
- **Benefit**: Reset without disassembly

**Implementation Steps**:
1. Measure Arduino Pro Micro reset button position
2. Add hole to bottom plate 3D model (CAD)
3. Test fit with tac switch
4. Update assembly documentation
5. Validate in production units

**Impact**:
- ✅ Easier bootloader access
- ✅ Faster recovery mode entry
- ✅ Simplified development workflow
- ✅ Better production QA process

---

## Priority 2: Testing Infrastructure

### Unit Tests for Debounce Logic
**Status**: 🔴 Not Started  
**Priority**: Medium  
**Effort**: Medium

**Goal**: Automated unit tests for debounce state machine

**Approach**:
- Mock `millis()` and `digitalRead()`
- Test state transitions with controlled timing
- Validate edge cases (simultaneous presses, rapid bounces, etc.)
- Framework: ArduinoUnit or custom test harness

**Benefits**:
- Catch regressions before deployment
- Document expected behavior
- Enable confident refactoring

---

### Integration Tests for MIDI Output
**Status**: 🔴 Not Started  
**Priority**: Medium  
**Effort**: Medium

**Goal**: Validate MIDI output matches expected note events

**Approach**:
- Capture USB MIDI traffic programmatically
- Simulate button presses (GPIO manipulation or hardware fixture)
- Assert correct MIDI messages sent
- Test octave shifting, note-on/off, velocity

**Tools Required**:
- MIDI monitor library (e.g., `mido` in Python)
- GPIO control (mock or real hardware)
- Test fixture for repeatable button actuation|

---

### QMK Firmware Support
**Status**: 🔴 Not Started
**Priority**: Medium
**Effort**: High

**Goal**: Port QMK (Quantum Mechanical Keyboard) firmware to Dilla4x.

**Benefits**:
- Advanced keymapping (layers, tap-dance, macros)
- VIA/Vial support for real-time configuration
- Standard keyboard functionality (typing mode)

---

### Visual Art Integration
**Status**: 🔴 Not Started
**Priority**: Medium
**Effort**: Medium

**Goal**: workflows and guides for using Dilla4x with visual arts software.

**Use Cases**:
- Triggering video clips (VJing) in Resolume/VDMX
- Controlling generative graphics (TouchDesigner, Processing, p5.js)
- Interactive installation control

---

### Hardware Ergonomics: Height Reduction
**Status**: 🔴 Not Started
**Priority**: Low
**Effort**: High (Redesign)

**Problem**: The current enclosure is relatively tall, which can affect wrist comfort during long sessions.

**Goal**: Redesign the enclosure/PCB mounting to reduce overall height.
- Lower profile switches?

---

## Priority 3: Features & Enhancements

### Feature Requests
**Status**: 🟡 Collecting Ideas  
**Priority**: TBD

**Potential Features** (subject to user feedback):
- Velocity sensitivity (requires hardware change - FSR or pressure sensors)
- Configurable MIDI channel (stored in EEPROM - conflicts with stateless design)
- Alternate chord modes (different octave shift patterns)
- LED feedback customization/optimization
- USB MIDI + DIN MIDI dual output

**Evaluation Criteria**:
- Maintains design philosophy (simplicity, statelessness, robustness)
- No significant complexity increase
- User demand
- Backward compatibility

---

## How to Contribute

**Proposing Features**:
1. Open issue in repository
2. Describe use case and rationale
3. Consider impact on design philosophy
4. Wait for discussion/approval

**Implementing Roadmap Items**:
1. Choose item from roadmap
2. Create branch
3. Implement with tests
4. Update this roadmap
5. Submit pull request

---

## Notes

- **Hardware changes** require coordination with 3D print files
- **Testing infrastructure** builds on existing `testing/` directory
- All changes must maintain **zero EEPROM usage** (stateless design)
- See [`FIRMWARE_SPEC.md`](firmware/Dilla4x-MIDI/FIRMWARE_SPEC.md) for design constraints

---

**Last Updated**: 2025-12-07
