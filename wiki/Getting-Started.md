# Getting Started with Dilla4x

Welcome to your Dilla4x MIDI controller build! This guide will walk you through assembling your very own MIDI controller, enabling you to create and control music using computers, smartphones, tablets, or other electronic instruments.

## 📦 What's in Your Kit

Before you start, ensure you have all the parts listed below.

### Structural Parts
- **3D Printed Shell**:
  - Top Plate: Holds the keys
  - Bottom Plate: Holds the electronics
  - Heated Inserts: Metal pieces inside the plates for screws (already included in the 3D printed parts)

- **Keys and Controls**:
  - Cherry MX Keyswitches: The buttons you press
    - Dilla4x (4x4) Configuration: 16 keys
  - Key Caps: Covers for the keys to press on with your finger

### Electronic Parts
- Arduino Pro Micro: The brain of your MIDI controller
- Dupont Connectors: Small connectors for making easy, solderless connections between parts
- Multiplexer: For advanced expansion possibilities
- Breadboard: For exploration and prototyping
- USB Cable: Small USB-C cable for power and data

### Tools Provided
- Screwdriver: For assembling the enclosure

### Tools You'll Need
- Computer: To run the Arduino software
- Hot Glue Gun or Double-Sided Tape (Optional): For securing components

### Optional Tools
- Cable Ties or Velcro Straps: For organizing wires inside the housing
- Multimeter: For troubleshooting electrical connections

## 🔧 Assembly Instructions

### Step 1: Assembling the 3D Printed Shell

The shell is the case that holds your instrument together.

#### Check the Parts
1. **Inspect All Pieces**:
   - Examine the top and bottom plates
   - Ensure all heated inserts (metal pieces inside the plates) are present and properly placed

2. **Clean the Parts**:
   - Remove any leftover material from printing, such as small blobs or strings, to ensure a smooth assembly

#### Assemble the Plates
1. **Position the Plates**:
   - Place the top plate on top of the bottom plate, aligning them correctly

2. **Secure with Screws**:
   - Use M3 screws to hold the plates together through the heated inserts
   - Tighten them firmly but avoid over-tightening to prevent damaging the plates

#### Final Checks
- **Stability**: Ensure the plates are securely attached and do not wobble
- **Accessibility**: Confirm that all ports (like the USB-C) are aligned and easy to reach

### Step 2: Setting Up the Electronic Components

Now, let's set up the electronics inside your controller.

#### Getting to Know Your Components
1. **Arduino Pro Micro**:
   - A small board that controls all the keys and sends MIDI signals to your computer

2. **Cherry MX Keyswitches**:
   - These are the buttons you press. Each one can send a signal when pressed

3. **Dupont Connectors**:
   - Tiny connectors that allow you to link wires without soldering

#### Mounting the Arduino Pro Micro
1. **Place the Arduino**:
   - Insert the Arduino Pro Micro into the designated space on the bottom plate
   - Ensure the USB-C port aligns with the hole in the housing for easy access

2. **Secure the Arduino**:
   - Use hot glue or double-sided tape to keep the Arduino in place
   - Be careful not to cover any important parts or ports

#### Connecting the Dilla4x Keys

The Dilla4x (4x4) setup uses 16 keys arranged without a matrix.

**Pin Assignments**:
- Digital Inputs for Main Keys (16 Keys):
  - K1: Pin 2
  - K2: Pin 3
  - K3: Pin 4
  - K4: Pin 5
  - K5: Pin 6
  - K6: Pin 7
  - K7: Pin 8
  - K8: Pin 9
  - K9: Pin 10
  - K10: Pin 11
  - K11: Pin 12
  - K12: Pin 13
  - K13: A0
  - K14: A1
  - K15: A2
  - K16: A3

**Wiring Steps**:
1. Connect Main Keys (K1 to K12):
   - Attach a Dupont connector to K1 and plug the other end into Pin 2 on the Arduino
   - Repeat this process for K2 to K12, connecting them to Pins 3 to 13 respectively

2. Connect Additional Keys (K13 to K16):
   - Attach a Dupont connector to K13 and plug it into A0
   - Repeat for K14 to A1, K15 to A2, and K16 to A3

3. Secure the Wires:
   - Ensure all connectors are firmly in place
   - Use cable ties or Velcro straps to keep the wires organized inside the housing

### Step 3: Installing and Setting Up the Software

Now, let's set up the software that tells your Arduino how to work.

#### Downloading the Arduino Software
1. Visit the Arduino Website:
   - Go to the Arduino Software Page

2. Download the Software:
   - Choose the version that matches your computer's operating system (Windows, Mac, or Linux)

3. Install the Software:
   - Follow the on-screen instructions to install the Arduino IDE (Integrated Development Environment)

4. Open the Arduino Software:
   - After installation, launch the Arduino IDE

#### Installing Necessary Libraries
Libraries are additional tools that help your Arduino understand more functions.

1. Open the Library Manager:
   - In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries...

2. Install Control_Surface Library:
   - In the search bar, type Control_Surface
   - Find the library and click Install

3. Close the Library Manager:
   - Once the library is installed, close the window

#### Uploading the Firmware to Arduino
Firmware is the program that makes your Arduino work as a MIDI controller.

1. Connect the Arduino:
   - Plug your controller into your computer using the USB-C cable

2. Select the Correct Board:
   - In the Arduino IDE, go to Tools > Board > Arduino Leonardo
   - (Note: The Arduino Pro Micro uses the same processor as the Leonardo.)

3. Select the Correct Port:
   - Navigate to Tools > Port
   - Choose the port that says Arduino Leonardo

4. Open the Firmware Code:
   - You should have a firmware file (a .ino file) provided for your controller
   - Click File > Open and select the firmware file

5. Check the Code:
   - Click the checkmark button (✓) to verify the code
   - If there are errors, double-check that the Control_Surface library is installed correctly

6. Upload the Code:
   - Click the right arrow button to upload the code to the Arduino
   - Wait until you see a message that says "Done uploading."

#### Configuring the Firmware
Set up the firmware to match your controller's layout.

1. Open the Firmware File:
   - If not already open, go to File > Open and select your firmware .ino file

2. Set Up the Device:
   - At the top of the code, find the section where you define the device
   - Add the following definitions for Dilla4x:
     ```cpp
     #define DEVICE_DILLA4X
     #define DILLA_CONFIG_4x4
     ```

3. Save the Changes:
   - After making all the changes, click File > Save

4. Upload the Updated Firmware:
   - Click the right arrow button again to upload the updated firmware to the Arduino

**Note**: Only make changes if you understand them. If unsure, follow the default settings.

### Step 4: Final Assembly

Now, let's assemble everything into the housing.

#### Securing Components Inside the Housing
1. **Mount the Arduino Pro Micro**:
   - Ensure it's securely glued or taped inside the bottom plate
   - Verify that the USB-C port is aligned with the hole in the housing

2. **Organize the Wires**:
   - Arrange the Dupont connectors and wires neatly
   - Use cable ties or Velcro straps to keep them tidy

3. **Install Key Switches**:
   - Place all Cherry MX keyswitches firmly into their slots on the top plate

4. **Attach Key Caps**:
   - Put the key caps onto each Cherry MX keyswitch
   - Press down to ensure they're securely attached

#### Finalizing the Housing
1. **Close the Housing**:
   - Carefully place the top plate over the bottom plate
   - Align the holes for the screws

2. **Secure with Screws**:
   - Use M3 screws to fasten the top and bottom plates together through the heated inserts
   - Tighten them until the housing feels solid

3. **Final Checks**:
   - Press all keys to ensure they move freely
   - Ensure no wires are pinched or stuck

## 🎵 Testing Your MIDI Controller

Before using your controller with music software, perform tests to ensure everything works correctly.

### Initial Power-On Test
1. **Connect to Computer**:
   - Plug your MIDI controller into your computer using the USB-C cable

2. **Open Serial Monitor**:
   - In the Arduino IDE, click on the magnifying glass icon (🔍) to open the Serial Monitor
   - Set the baud rate to 9600 at the bottom of the window

3. **Check Status**:
   - You should see messages indicating the controller has started
   - Look for any error messages

### Functional Testing
1. **Test Main Keys (K1 to K16)**:
   - Press each main key
   - In the Serial Monitor or a MIDI monitoring tool, you should see messages indicating which key was pressed

2. **Test Octave Functionality**:
   - Press all 8 top keys (rows 1-2) simultaneously for about 100ms to test +1 octave shift
   - Press all 8 bottom keys (rows 3-4) simultaneously for about 100ms to test -1 octave shift
   - You should see octave shift messages in the Serial Monitor

## 🎧 Using Your Dilla4x

### With Digital Audio Workstations (DAWs)
Your Dilla4x will appear as a standard MIDI device in any DAW:
- **Ableton Live**: Create MIDI clips and assign instruments
- **FL Studio**: Use with any plugin or instrument
- **Logic Pro**: Assign to software instruments
- **Bitwig Studio**: Perfect for modular MIDI routing

### With Mobile Apps
Many mobile music apps support external MIDI controllers:
- **iOS**: GarageBand, Korg Gadget, Cubasis
- **Android**: Caustic, FL Studio Mobile, Music Studio

### Standalone Use
You can also use your Dilla4x with:
- Hardware synthesizers
- MIDI sound modules
- Digital pianos with MIDI input

## 📚 Next Steps

- **[Firmware Configuration](Firmware.md)** - Customize your controller's behavior
- **[Technical Specifications](Technical-Specifications.md)** - In-depth technical details
- **[Troubleshooting](Troubleshooting.md)** - Fix common issues
- **[FAQ](FAQ.md)** - Answers to common questions

---

**Congratulations!** 🎉 You've successfully built your Dilla4x MIDI controller. Your controller is now ready to help you create and control your music in any way you desire.

Remember: Building electronics takes patience and attention to detail. Don't get discouraged if something doesn't work on the first try. Use the troubleshooting steps to fix issues and keep experimenting to make your controller even better.

**Happy Music Making!** 🎵