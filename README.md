# ATTiny85 Guitar Footswitch Toggle

This project provides firmware for an ATtiny85 microcontroller to control two guitar pedal circuits (A and B) using two footswitches and two relays. It allows for quick switching between circuits and toggling each circuit on and off individually, making it ideal for guitar pedal loopers, true bypass switchers, or A/B/Y boxes.

## Features

- **Two Footswitch Inputs:**
  - Connects to two standard guitar pedal footswitches (momentary, normally open).
  - Footswitch A controls Circuit A (Relay 1), Footswitch B controls Circuit B (Relay 2).

- **Relay Outputs:**
  - Two output pins control two relays, which can switch audio circuits or other loads.

- **Toggle Logic:**
  - Pressing Footswitch A:
    - If both circuits are off, Circuit A turns on (Relay 1 ON, Relay 2 OFF).
    - If Circuit A is already on, pressing again turns both circuits off.
    - If Circuit B is on, pressing A switches instantly to Circuit A (Relay 1 ON, Relay 2 OFF).
  - Pressing Footswitch B:
    - If both circuits are off, Circuit B turns on (Relay 2 ON, Relay 1 OFF).
    - If Circuit B is already on, pressing again turns both circuits off.
    - If Circuit A is on, pressing B switches instantly to Circuit B (Relay 2 ON, Relay 1 OFF).

- **Debouncing:**
  - Robust counter-based debouncing ensures reliable operation with mechanical footswitches.

## Hardware Setup

- **Microcontroller:** ATtiny85
- **Inputs:**
  - Footswitch A: Connect to pin 3 (physical pin 2)
  - Footswitch B: Connect to pin 4 (physical pin 3)
  - Both switches should connect between the input pin and GND (internal pull-ups are enabled in code).
- **Outputs:**
  - Relay 1 (Circuit A): pin 1 (physical pin 6)
  - Relay 2 (Circuit B): pin 2 (physical pin 7)
- **Relays:**
  - Use relays suitable for your audio or switching needs. Drive relays via transistors if required.

## How It Works

- The firmware continuously monitors the state of both footswitches.
- When a footswitch is pressed (LOW pulse detected and debounced), the code toggles the corresponding relay:
  - If the relay was off, it turns on and the other relay turns off.
  - If the relay was already on, it turns off (both relays off).
- This allows for quick switching between circuits and toggling each on/off independently.

## Usage

1. Flash the `pedal_toggle.ino` firmware to your ATtiny85.
2. Connect your footswitches and relays as described above.
3. Power the circuit and use the footswitches to toggle and switch between your pedal circuits.

---

**Note:**
- The code is optimized for momentary (not latching) footswitches.
- Adjust the debounce count in the code if you experience missed or double triggers.

---

Enjoy seamless switching between your guitar pedal circuits! 