# STM32 Security Access Console

A mini embedded project built on an STM32 Nucleo board that simulates a secure command-line authentication system using UART communication.

The project demonstrates embedded software development concepts such as state machines, UART communication, GPIO control, authentication logic, timing, and user interaction.

---

## Features

### Authentication

- Password-based authentication over UART
- Maximum of 3 failed login attempts
- Automatic 30-second system lock after 3 incorrect passwords
- LED alarm indication during lock state
- Two-factor authentication using the onboard user button
- User must press the button 3 times within 10 seconds

---

## Command Console

After successful authentication, the following commands become available:

| Command | Description |
|---------|-------------|
| `help` | Display available commands |
| `status` | Show current device status |
| `led on` | Turn LED on |
| `led off` | Turn LED off |
| `blink` | Start LED blinking |
| `lock` | Logout and return to login screen |

---

## Device Status

The `status` command displays information such as:

- Authentication state
- LED state
- Failed login attempts
- System uptime
- Current operating mode

---

## Hardware

- STM32 Nucleo-F401RE
- UART (Virtual COM Port)
- On-board User LED
- On-board User Button

---

## Software

- STM32CubeIDE
- STM32 HAL Drivers
- Git
- GitHub

---

## Project Structure

```
stm32-security-access-console
│
├── Core/
├── Drivers/
├── docs/
│   └── user_manual.md
├── README.md
├── .gitignore
└── STM32_Security_Access_Console.ioc
```

---

## Authentication Flow

```
Power On
    │
    ▼
Password Prompt
    │
    ├── Wrong Password
    │       │
    │       ▼
    │  Failed Attempts
    │
    │       └── 3 Attempts
    │               │
    │               ▼
    │         System Locked
    │         (30 seconds)
    │
    ▼
Correct Password
    │
    ▼
Press Button 3 Times
(within 10 seconds)
    │
    ├── Success
    │       │
    │       ▼
    │ Command Console
    │
    └── Failure
            │
            ▼
      System Locked
```

---

## Learning Objectives

This project was created to practice:

- UART communication
- GPIO configuration
- State machine implementation
- Embedded software architecture
- Command parser implementation
- Software timers
- User authentication logic
- Version control using Git

---



## Author

Developed by Dora Pečurlić 

![STM32](https://img.shields.io/badge/MCU-STM32-blue)

![Language](https://img.shields.io/badge/C-HAL-success)

![Status](https://img.shields.io/badge/Status-In%20Development-orange)