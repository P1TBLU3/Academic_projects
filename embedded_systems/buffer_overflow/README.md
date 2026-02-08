# Embedded Buffer Overflow Attacks and Mitigations on ARM Microcontrollers

This project explores **buffer overflow vulnerabilities in embedded systems**, focusing on ARM-based microcontrollers (Infineon XMC4500 / XMC4000).  
It was developed as part of an Embedded Systems / Security laboratory and demonstrates both **practical exploitation techniques** and **defensive countermeasures**.

## Overview

The project is structured into several parts that progressively cover:

- Vulnerable firmware design
- Remote exploitation via USB virtual serial interfaces
- Debugging and reverse engineering using GDB and J-Link
- Implementation of software and hardware-level protections

The target platform is a bare-metal ARM Cortex-M microcontroller communicating with a host machine over USB CDC.


## Key Topics Covered

- Stack-based buffer overflow in embedded C
- Exploit development for constrained devices
- USB CDC (Virtual Serial) communication
- ARM Cortex-M memory layout and calling conventions
- GDB/J-Link debugging and memory inspection
- Embedded security countermeasures:
  - Memory Protection Unit (MPU)
  - Stack canaries / stack protector
  - Cryptographic primitives for secure communication

## Toolchain and Technologies

- C (bare-metal embedded)
- Python (exploit scripts)
- ARM GCC toolchain
- GDB + J-Link
- Makefiles
- USB CDC (Virtual Serial)
- libsodium (ARM precompiled)

## Disclaimer

This project is for **educational and research purposes only**.  
The techniques demonstrated here are intended to improve understanding of embedded system security and should **not** be used for malicious purposes.

Developed as part of an academic Embedded Systems / Security course.


