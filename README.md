# AccessX

AccessX is a secure door lock system built on the STM32F446RE microcontroller. It combines a 4×4 keypad, an I2C LCD display, and hardware controls like relays, LEDs, and a buzzer to create a reliable and interactive access system. I wanted to create a project that blended embedded hardware control with real-world security logic. Currently, the relay drives a blue demo light, but the system can be directly scaled to control a door lock mechanism.

## Features

### Keypad Input:
- 4×4 matrix keypad with row/column scanning
- Debouncing for reliable key detection
- Supports digits (0–9) and function keys (*, #, A–D)

### LCD Interface:
- I2C-driven display for real-time feedback
- Masked PIN entry (asterisks for security)
- System messages like “Access Granted” or lockout countdown

### Security Layer:
- Configurable 4-digit PIN (default: 1234)
- 3 failed attempts trigger a 30-second lockout
- Master reset function with the A key

### Hardware Control:
  - Relay activation triggers a blue light (3s duration)  
    - Can be scaled to control a door lock mechanism
- Green LED for success
- Red LED flashing on failure
- Buzzer feedback for keypresses & status

## Getting Started

### Hardware Setup
- STM32F446RE (Nucleo board recommended)
- 4×4 Keypad wired to GPIO
- I2C LCD on I2C1 (PB8=SCL, PB9=SDA)
- Relay module, LEDs, and buzzer

### Firmware Setup
  - Configure peripherals in STM32CubeMX:
    - I2C1 enabled
    - GPIO pins mapped to keypad rows/columns
- Add i2c-lcd.c and i2c-lcd.h to your project
- Add keypad.c and keypad.h to your project
- Build & flash via STM32CubeIDE or your preferred toolchain

### Usage
- Enter a 4-digit PIN → press # to submit
- Press * to clear input
- Wrong code? 3 attempts = lockout (with countdown)
- Press A for master reset

## Configurable Parameters

### Inside main.c:
- #define CORRECT_PIN "1234" → change your PIN here
- #define RELAY_ON_TIME 3000 → relay activation duration (ms)
- #define LOCKOUT_TIME 30000 → lockout duration (ms)
- #define MAX_ATTEMPTS 3 → number of retries



