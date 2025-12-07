# Dilla4x Testing Infrastructure

Automated testing tools and test harnesses for firmware validation.

## Purpose

This directory contains tools for testing firmware logic, validating changes, and debugging issues in a controlled environment.

## Tools

### `firmware_test/`

Configurable test harness based on main firmware debounce/MIDI logic.

**Test Modes** (configure in source):
- `TEST_WATCHDOG`: Enable/disable watchdog timer
- `TEST_MIDIUSB`: Enable/disable MIDIUSB library (isolate pin conflicts)
- `TEST_VERBOSE`: Detailed trace logging vs minimal output

**Use cases**:
- Debugging debounce logic
- Testing if MIDIUSB causes pin read issues
- Validating firmware changes before deployment
- Reproducing production bugs in controlled environment

**See**: [firmware_test/README.md](firmware_test/README.md) for detailed usage

---

## Testing Strategy

### Current State

**Manual Testing**:
1. Hardware utilities ([`utils/`](../utils/)) validate physical connections
2. `firmware_test` validates firmware logic with serial tracing
3. Main firmware deployment tested manually on device

### Future Roadmap

See [ROADMAP.md](file:///home/morp/Documents/coding/projects/Dilla4x/ROADMAP.md) for planned testing infrastructure:

**Priority 2 - Testing**:
- Unit tests for debounce logic
- Integration tests for MIDI output validation
- Hardware-in-the-loop (HIL) test framework
- Automated test suite with CI/CD
- Regression test coverage

---

## Adding New Tests

When creating new test utilities:

1. **Create subdirectory**: `testing/your_test_name/`
2. **Add sketch**: `your_test_name.ino`
3. **Document**: Create `README.md` explaining:
   - What it tests
   - How to configure
   - Expected output
   - When to use
4. **Update this file**: Add entry to "Tools" section above

---

## Related

- **Hardware diagnostics**: See [`utils/README.md`](../utils/README.md)
- **Main firmware**: See [`FIRMWARE_SPEC.md`](../FIRMWARE_SPEC.md)
- **Future improvements**: See [ROADMAP.md](file:///home/morp/Documents/coding/projects/Dilla4x/ROADMAP.md)
