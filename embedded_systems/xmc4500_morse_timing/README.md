# XMC4500 Morse + Timing Demo

Small embedded project for the Infineon XMC4500 Relax Kit.

It uses SysTick for millisecond timing and GPIO for LEDs/buttons.

## What it does
This repo has two parts:

### Part A
Continuously blinks a fixed message in Morse code on an LED (dot/dash timing).

### Part B
- **Button 1:** plays the Morse message (e.g., “I CAN MORSE”) on the LED.
- **Button 2:** outputs the time difference (in ticks/ms) between the last two Button 1 presses, sending the digits one by one using Morse patterns.

## Notes
- Targets: XMC4500 (XMC GPIO + SysTick).
- Build artifacts are not tracked in Git.

University coursework / lab project.
