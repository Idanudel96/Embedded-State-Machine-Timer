# Embedded Digital Lock & Sequential Timer 🔒⏱️

## Overview
A bare-metal embedded system project written in C for the Texas Instruments TMS320F28335 DSP (Delfino Evaluation Board). This project was developed as a final assignment for the "Microprocessors and Microcontrollers" course, fulfilling the advanced level requirements (Target Score: 85-90). 

The system implements a secure digital lock controlled by a software-based Finite State Machine (FSM). It requires a specific 4-digit passcode entered via a matrix keypad to transition from the `LOCKED` to the `OPEN` state. Once open, it initiates a hardware-based countdown timer before automatically securing the system again.

## Key Features & Requirements Met
* **Interrupt-Driven State Machine:** Robust transition handling between `LOCKED` and `OPEN` states, driven by CPU Timer interrupts rather than blocking polling loops.
* **Hardware Interrupts:** 
  * Utilizes CPU Timer 0 configured for periodic interrupts to manage the countdown and LCD refresh rate.
  * External interrupts (XINT3-XINT6) mapped to GPIOs for responsive, asynchronous keypad inputs.
* **Peripherals Integration:** 
  * Custom driver for a 16x2 alphanumeric LCD to display system states and live countdowns in `HH:MM:SS` format.
  * 4x4 Matrix Keypad scanning with debouncing logic and a cyclic buffer implementation.
  * GPIO toggling for a buzzer alert system to signal state changes and timeout events.
* **Modular Architecture:** The project is cleanly separated into dedicated source and header files for the FSM, LCD driver, Keypad driver, and main execution loop.

## Project Structure
* `Flax_DelfinoEvbGpioToggle.c` - Main program loop, system initialization, and interrupt service routines (ISRs).
* `StateMachine.c / .h` - Logic and transitions for the lock mechanism.
* `keyboardmat.c / .h` - Keypad scanning, ASCII conversion, and cyclic buffer management via interrupts.
* `LCD2x16Display.c / .h` - Driver for LCD initialization and text rendering.

## Acknowledgments
Special thanks to Prof. Elazar Flaxer for providing the foundational C templates and hardware-interfacing base code used throughout this project.
