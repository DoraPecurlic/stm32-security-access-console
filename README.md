# STM32 Security Access Console

![STM32](https://img.shields.io/badge/MCU-STM32F401RE-blue)
![Language](https://img.shields.io/badge/Language-C-success)
![Framework](https://img.shields.io/badge/Framework-STM32%20HAL-blueviolet)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

A mini embedded security system developed on the STM32 Nucleo-F401RE board.

The system provides password authentication through a UART command-line interface, button-based two-factor authentication, system lockout protection, virtual door control, and alarm control using onboard and external LEDs.

---

## Features

### Authentication

- Password-based authentication through UART
- Password characters are hidden during input
- Maximum of three failed login attempts
- Automatic 30-second lockout after three incorrect passwords
- Visual LED indication while the system is locked
- Two-factor authentication using the onboard user button
- The user must press the button three times within 10 seconds
- Automatic return to password authentication if verification fails

### Command Console

After successful authentication, the user gains access to an interactive command console.

The console is divided into multiple screens:

- Main menu
- Help screen
- Status screen
- Door control screen
- Alarm control screen

### Door Control

The system simulates a controllable security door.

- Open and close the virtual door through UART commands
- Display the current door state
- Use the onboard green LED to represent whether the door is open

### Alarm Control

- Enable or disable the alarm through UART commands
- Display the current alarm state
- Use an external red LED as the alarm indicator
- Blink the alarm LED without blocking the rest of the program

---

## Hardware

### Components

- STM32 Nucleo-F401RE development board
- External red LED
- Current-limiting resistor (330 Ohm)
- Breadboard
- Jumper wires
- USB cable
- Computer running a serial terminal

### Pin Configuration

| Component | STM32 pin | Function |
|---|---|---|
| Onboard green LED LD2 | PA5 | Virtual door state |
| External red LED | PB5 | Alarm indication |
| Onboard user button B1 | PC13 | Two-factor authentication |
| USART2 TX | PA2 | UART transmission |
| USART2 RX | PA3 | UART reception |

The external LED must be connected in series with a current-limiting resistor.

---

## Hardware Setup



---

## Software

- STM32CubeIDE
- STM32CubeMX
- STM32 HAL drivers
- PuTTY 

### UART Configuration

| Setting | Value |
|---|---|
| UART peripheral | USART2 |
| Baud rate | 115200 |
| Data bits | 8 |
| Stop bits | 1 |
| Parity | None |
| Flow control | None |

---

## Software Architecture

The application is divided into separate modules to keep hardware control, interface logic, and system behavior organized.

| Module | Responsibility |
|---|---|
| `main.c` | Hardware initialization and main application loop |
| `security_system.c` | Authentication and main security state machine |
| `command_handler.c` | UART command processing and console navigation |
| `ui_screens.c` | Terminal screen and message output |
| `uart_console.c` | UART helper functions |

The system uses state machines to manage authentication and command-console behavior.

---

## Project Structure

```text
stm32-security-access-console/
├── firmware/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── command_handler.h
│   │   │   ├── security_system.h
│   │   │   ├── uart_console.h
│   │   │   ├── ui_screens.h
│   │   │   └── main.h
│   │   └── Src/
│   │       ├── command_handler.c
│   │       ├── security_system.c
│   │       ├── uart_console.c
│   │       ├── ui_screens.c
│   │       └── main.c
│   ├── Drivers/
├── .gitignore
└── README.md
```

---

## Running the Project

1. Clone the repository.
2. Open the project in STM32CubeIDE.
3. Connect the STM32 Nucleo-F401RE board through USB.
4. Build and flash the project.
5. Open PuTTY.
6. Select the board's virtual COM port.
7. Configure the serial connection to `115200 8N1`.
8. Follow the instructions displayed in the terminal.

---

## Console Preview


---

## Learning Outcomes

This project was created to practice:

- UART communication
- GPIO input and output
- External interrupt handling
- State machine implementation
- Embedded software architecture
- Command parsing
- Authentication logic
- Modular C programming
- Connecting external components to an STM32 board

---

## Author

Developed by Dora Pečurlić.
