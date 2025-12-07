# How to Use Your Dilla4x (MIDI Firmware)

A simple, accessible guide to playing and controlling your Dilla4x using the **standard MIDI Firmware (v0.3)**.

> [!NOTE]
> This guide applies to the default Dilla4x MIDI firmware. Alternative firmwares (like QMK) may have different controls.

## What the Dilla4x Does (In Plain English)

The Dilla4x is a **16-button MIDI controller** that sends musical notes to your computer. Think of it like a tiny piano keyboard, but arranged in a 4x4 grid instead of the traditional piano layout.

**What makes it special**:
- Each button plays a different musical note
- You can shift all notes up or down (octave shifting)
- It's designed to be playable with limited hand mobility
- Works instantly with any music software that accepts MIDI

---

## Button Layout & Notes

### The Grid

Your Dilla4x has 16 buttons arranged like this:

```
[K1 ] [K2 ] [K3 ] [K4 ]    ← Row 1 (Top)
[K5 ] [K6 ] [K7 ] [K8 ]    ← Row 2
[K9 ] [K10] [K11] [K12]    ← Row 3
[K13] [K14] [K15] [K16]    ← Row 4 (Bottom)
```

### What Notes They Play

**Starting notes** (before any octave shifting):

```
Row 1:  C3   C#3  D3   D#3     (Highest notes)
Row 2:  G#2  A2   A#2  B2
Row 3:  E2   F2   F#2  G2
Row 4:  C2   C#2  D2   D#2     (Lowest notes)
```

**Musical pattern**: The notes are arranged chromatically (every half-step) going from bottom-left to top-right, like climbing a musical ladder.

---

## How to Play

### Basic Playing (Individual Notes)

**Press any button** = That note plays (MIDI "Note On")  
**Release the button** = Note stops (MIDI "Note Off")

**For playing individual notes**, use precise fingertip presses - just like piano keys.

### Playing Techniques

#### **For Individual Notes**:
- Use **fingertips** to press buttons precisely
- One finger per button for single notes
- Multiple fingers for chords (pressing several buttons intentionally)
- This is standard playing - requires some finger dexterity

#### **For Octave Shifting** (Accessible):
This is where the accessibility design shines - octave shifting can be done with minimal dexterity:

1. **Flat Finger Method**:
   - Lay 1-2 fingers **flat** across one side (left or right half)
   - Press down to activate multiple buttons at once
   - Good for limited finger dexterity

2. **Palm/Hand Side Method**:
   - Use the **side of your hand** or **palm edge**
   - Press down on one entire half of the grid
   - Excellent for users with limited fine motor control
   - Most accessible option - requires zero finger precision

> [!IMPORTANT]
> **The flat finger and palm methods are for OCTAVE SHIFTING, not normal playing.** You can't hit individual keys accurately with your palm - these techniques are specifically designed for the "chord trigger" that shifts octaves.

**Summary**:
- **Normal playing** = Fingertips on individual buttons
- **Octave shifting** = Flat fingers or palm on entire left/right half

---

## Octave Shifting: Making Notes Higher or Lower

This is where the Dilla4x gets powerful. You can shift **all** the notes up or down by octaves.

### What's an Octave?

An octave is the distance from one note to the same note at a higher/lower pitch. For example:
- C2 → C3 = +1 octave (higher)
- C3 → C2 = -1 octave (lower)

When you shift octaves, all 16 buttons play notes that are higher or lower, but keep the same pattern.

### How to Shift Octaves

#### **Shift UP** (Make Notes Higher)

**Press the RIGHT HALF** of your Dilla4x (all 8 right-side buttons at once):

```
        [✓] [✓]    ← These 8 buttons
        [✓] [✓]
        [✓] [✓]
        [✓] [✓]
```

**How to do it**:
1. Place your hand flat on the **right side** of the grid
2. Press down with your **palm or multiple fingers**
3. Press **at least 6 of the 8 right buttons** at the same time
4. The LED will blink once to confirm
5. All notes are now **one octave higher**

#### **Shift DOWN** (Make Notes Lower)

**Press the LEFT HALF** of your Dilla4x (all 8 left-side buttons at once):

```
[✓] [✓]        ← These 8 buttons
[✓] [✓]
[✓] [✓]
[✓] [✓]
```

**How to do it**:
1. Place your hand flat on the **left side** of the grid
2. Press down with your **palm or multiple fingers**  
3. Press **at least 6 of the 8 left buttons** at the same time
4. The LED will blink once to confirm
5. All notes are now **one octave lower**

### Octave Range

- You can shift **3 octaves up** (maximum)
- You can shift **3 octaves down** (minimum)
- That gives you a total range of **7 octaves** to work with!

**Example**: If you start at C2 and shift up 3 times, you'll be at C5. That's a huge musical range from a tiny controller!

### Octave Reset

**What if you forget what octave you're in?**

1. Unplug the Dilla4x
2. Plug it back in
3. It **always starts at octave 0** (middle range)

This "reset to zero" design means you never get "lost" - just power cycle to get back to the default.

---

## Understanding the LED Feedback

The Dilla4x has a built-in LED that tells you what's happening:

| LED Behavior | What It Means |
|--------------|---------------|
| **Solid ON** | You're pressing a button (note playing) |
| **OFF** | No buttons pressed (idle) |
| **Quick blink** | Octave shift confirmed |
| **Fast continuous blinking** | Recovery mode (troubleshooting only) |

The LED gives you visual confirmation that your octave shifts worked, which is helpful when you're performing live.

---

## Common Usage Patterns

### For Beat Making (Drums)
- Keep at octave 0 or shift down 1-2 octaves for deep bass hits
- Use palm strikes for powerful drum sounds
- Quick taps with fingers for hi-hats and percussion

### For Melodies
- Shift up 1-2 octaves for lead lines
- Use fingertips for precise note control
- Experiment with different octave ranges for variety

### For Basslines
- Shift down 2-3 octaves for sub-bass
- Use flat fingers or palm for thick, chorded bass
- Lower notes have more power and weight

### For Accessibility
- Use whatever playing technique works for you
- Palm/hand side method requires **zero fine motor control**
- Octave shifting lets you access the full musical range without repositioning your hand

---

## Troubleshooting

### "My octave shifts aren't working"

**Requirement**: You need to press **at least 6 out of 8 buttons** on one side.

**Try this**:
- Press with your **whole palm** flat on one side
- Make sure you're covering the full half of the grid
- You should feel/see at least 6 buttons actually clicking down

### "I don't know what octave I'm in"

**Solution**: Unplug and replug the Dilla4x - it always resets to octave 0.

### "Some notes sound wrong"

The Dilla4x uses **chromatic tuning** (all half-steps). Not every series of buttons will sound "musical" - that's intentional! You're working with raw musical intervals.

For traditional scales (major, minor, etc.), you'll skip some buttons. That's normal.

---

## Tips for New Users

1. **Start simple**: Just press buttons and hear what they sound like before worrying about octaves

2. **Experiment with technique**: Try fingers, flat hand, and palm - find what feels best

3. **Use your DAW's piano roll**: See which notes you're playing and learn the layout

4. **Practice octave shifts**: Get comfortable with the palm-press motion - it becomes second nature

5. **Don't overthink it**: The Dilla4x is designed to be intuitive. If it makes sound when you press it, you're doing it right!

---

## Advanced: Why These Design Choices?

### Chromatic Layout
The Dilla4x uses **all 12 notes** (chromatic scale) rather than just white keys like a piano. This gives you:
- Complete musical freedom (any scale, any key)
- Ability to play notes between major scale steps
- Maximum flexibility for non-Western musical traditions

### Accessibility First
The octave shift via "chord trigger" (pressing multiple buttons) was designed so that:
- Users with limited fingers can shift octaves with their palm
- No need for extra buttons or complex menus
- Physical motion is the same as playing (press buttons)
- Visual/tactile feedback (LED blink) confirms the action

### Stateless Design
The device **resets to zero** on power-up intentionally:
- You always know where you're starting from
- No confusion about saved states
- Simple mental model: plug in = octave 0

---

## Getting Started Checklist

1. ✅ Plug Dilla4x into computer via USB
2. ✅ Open your music software (DAW, synthesizer, etc.)
3. ✅ Select "Dilla4x" or "Arduino Pro Micro" as MIDI input
4. ✅ Press a button - hear a sound!
5. ✅ Practice octave shifts (palm press left/right halves)
6. ✅ Make music! 🎵

---

**Remember**: The Dilla4x is a tool for making music **your way**. There's no right or wrong technique - use what works for your hands and your music.

👉 Next: [Connecting to Your DAW](Music-Making-Overview.md)  
🎵 Also See: [Beginner Music Making Tips](Beginner-Guide.md)
