# STM32 Two-Player Mini Games (STM32L152C-Discovery)

Small embedded project for the STM32L152C-Discovery board (STM32CubeIDE / CubeMX).

It implements **two simple 2-player games** using the on-board **glass LCD**, LEDs, timers and a potentiometer input:

- **Game 1 (reaction time):** waits a random time, turns on an LED, and the first player to react wins. The LCD shows the winner and timing.
- **Game 2 (timing challenge):** a short countdown / blank-screen moment happens with randomness and the players try to press at the right time. A potentiometer (ADC) is used to scale the difficulty/time window.

Timers are used for timing/measurement and PWM is used to generate simple tones.

## Hardware / Platform
- Board: **STM32L152C-Discovery (STM32L152RBTx)**
- Tools: **STM32CubeIDE + STM32CubeMX**
- Language: **C (HAL + direct register access in parts)**

## Repo contents
This repo includes only source code + CubeMX config (`.ioc`). Build artifacts are intentionally excluded.
