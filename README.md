# Arduino-based Insulin Pump

A microcontroller-based insulin delivery system designed to provide precise dosing through a user-friendly interface.

## Overview

This project implements a programmable insulin pump using an ESP32 microcontroller, a stepper motor for precise insulin delivery, and an OLED display for user interaction. The system allows users to select insulin doses (5, 10, or 15 units) and perform actions like injection or reservoir refilling through an intuitive menu system.

![Insulin Pump](images/insulin%20pump.jpg)
![Insulin Pump 2](images/insulin%20pump%202.jpg)

## Hardware Components

- **ESP32 Microcontroller**: Main processing unit
- **OLED Display (SSD1306)**: User interface (128x64 pixels)
- **Stepper Motor & Driver**: Precise insulin delivery mechanism
- **Push Buttons (3)**: User input controls (Up, Down, Select)
- **Power Supply**: Powering the system

## Circuit Diagram

![Circuit Diagram](images/circuit%20diagram.jpg)

## Software Features

- **Menu-driven Interface**: Easy navigation through dose options and functions
- **Precise Dosing Control**: Calibrated stepper motor movements
- **Dual Operation Modes**: Injection and refill capabilities
- **Debounce Protection**: Prevents accidental button triggers

## How It Works

### Display and Menu System

The OLED display shows a navigable menu with two levels:
1. **Main Menu**: Select insulin dose amount (5, 10, or 15 units)
2. **Sub-Menu**: Choose action to perform (Inject, Refill, Back)

### Button Controls

- **UP Button (GPIO 14)**: Navigate up through menu options
- **DOWN Button (GPIO 12)**: Navigate down through menu options
- **SELECT Button (GPIO 13)**: Confirm selection or enter sub-menu

### Stepper Motor Control

The stepper motor provides precise control for insulin delivery:
- Steps are calculated based on selected dose (dose * 200 steps)
- Direction control allows for both injection and refill operations
- Motor is enabled only during operation to conserve power

### Code Structure

```
setup():
- Initialize buttons, display, and stepper motor
- Set initial display state

loop():
- Process button inputs with debounce protection
- Update menu navigation based on button presses
- Execute stepper motor actions based on selected options
```

### Key Functions

- `drawMenu()`: Renders the current menu state to the OLED display
- `moveStepper(steps)`: Controls the stepper motor for precise insulin delivery
- Button handling logic in the main loop manages user interaction

## Implementation Challenges

1. **Motor Calibration**: Calibrating the stepper motor for accurate insulin doses required careful testing and adjustment of steps-per-unit ratios.

2. **User Interface Design**: Creating an intuitive interface on a small OLED display while maintaining readability and ease of use.

3. **Button Debouncing**: Implementing reliable button debouncing to prevent accidental double-presses during menu navigation.

4. **Power Management**: Ensuring the stepper motor is only powered during operation to extend battery life.

5. **ESP32 Pin Selection**: Finding non-conflicting GPIO pins that work with both the display (I²C) and the stepper driver.

## Future Improvements

- Battery level monitoring
- Dose history logging
- Bluetooth connectivity for mobile app control
- Custom dose programming
- Temperature monitoring for insulin stability

## Installation and Setup

1. Connect the hardware according to the circuit diagram
2. Upload the code to your ESP32 using the Arduino IDE
3. Ensure all libraries are installed:
   - Wire.h
   - Adafruit_GFX.h
   - Adafruit_SSD1306.h
   - AccelStepper.h

## Required Libraries

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [AccelStepper](https://www.airspayce.com/mikem/arduino/AccelStepper/)

## License

MIT License

Copyright (c) 2025

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
