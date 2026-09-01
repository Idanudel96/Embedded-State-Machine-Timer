# Embedded Digital Lock & Sequential Timer

An embedded C project developed for the **Texas Instruments TMS320F28335 (Delfino Evaluation Board)** as a final project for a Microprocessors and Microcontrollers course.

The system implements a digital lock controlled by a finite state machine (FSM), with keypad-based password input, timer-driven system behavior, LCD output, and hardware interrupt handling.

## System Overview

The system operates primarily between two states:

**LOCKED**  
→ Correct 4-digit passcode entered  
→ **OPEN**  
→ Countdown expires  
→ **LOCKED**

User input is received through a matrix keypad, while system status and countdown information are displayed on a 16x2 LCD.

## Main Features

- Finite State Machine (FSM) for digital-lock control
- 4-digit passcode verification
- Timer-based automatic transition from `OPEN` back to `LOCKED`
- CPU Timer 0 for periodic interrupt-driven operations
- External interrupts for keypad input
- 4x4 matrix keypad interface
- 16x2 LCD interface
- Countdown display in `HH:MM:SS` format
- GPIO-based output control
- Modular organization of keypad, LCD, and state-machine functionality

## Embedded Architecture

The project combines several embedded-system components:

**TMS320F28335**
- System initialization
- Interrupt Service Routines (ISRs)
- CPU Timer
- GPIO control

↓

**Input**
- 4x4 Matrix Keypad
- External GPIO interrupts

↓

**Control**
- Finite State Machine
- Passcode validation
- Countdown logic

↓

**Output**
- 16x2 LCD
- System status
- Countdown display

## Interrupt Handling

The project uses interrupt-driven execution for time-sensitive and asynchronous operations.

### CPU Timer

CPU Timer 0 is used for periodic system operations, including countdown timing and display-related updates.

### External Interrupts

External interrupts connected to GPIO inputs are used to process keypad events without relying solely on continuous polling.

## Finite State Machine

The digital lock behavior is controlled through a software-based FSM.

### LOCKED State

- The system waits for keypad input.
- Entered digits are processed as a passcode.
- A valid passcode causes a transition to the `OPEN` state.

### OPEN State

- The system starts a countdown.
- Remaining time is displayed on the LCD.
- When the countdown reaches zero, the system automatically returns to the `LOCKED` state.

## Project Structure

- `Flax_DelfinoEvbGpioToggle.c` – Main application file containing system initialization, execution logic, and interrupt service routines
- `StateMachine.h` – State-machine definitions and related declarations
- `keyboardmat.c` – Matrix-keypad handling and input processing
- `keyboardmat.h` – Keypad interface declarations
- `LCD2x16Display.c` – LCD control and display functionality
- `LCD2x16Display.h` – LCD interface declarations
- `README.md` – Project documentation

## Technologies & Concepts

- C
- Texas Instruments TMS320F28335
- Embedded Systems
- Finite State Machines
- Interrupt Service Routines
- Hardware Timers
- GPIO
- Matrix Keypad Interfacing
- LCD Interfacing

## Engineering Topics

This project provided hands-on experience with:

- Embedded C programming
- Interrupt-driven system design
- Finite State Machine implementation
- Hardware timer configuration
- GPIO-based peripheral interfacing
- Matrix keypad input handling
- LCD control
- Modular embedded-software organization
- Hardware/software integration
- Debugging embedded-system behavior

## Acknowledgments

Foundational hardware-interfacing templates and base code for the Delfino evaluation board were provided by **Prof. Elazar Flaxer** as part of the Microprocessors and Microcontrollers course.

The project-specific system logic, state-machine behavior, keypad interaction, timing functionality, and application implementation were developed as part of the course project.
