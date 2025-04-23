# Tap-Sensitive Color-Changing LED System

## 📋 Overview

This embedded systems project uses an LPC21xx microcontroller to detect taps and light different LEDs based on the number of taps within a 1-second window.

## 🎯 Features

- Tap detection within a time window
- LED color mapping:
  - 1 Tap → Red
  - 2 Taps → Green
  - 3 Taps → Yellow
  - 4 Taps → Blue
  - 5 Taps → Purple
- LCD display of current tap count and color
- Efficient refresh using last count tracking

## 🔧 Hardware Used

- LPC2129 Microcontroller
- 16x2 LCD (4-bit mode)
- 5 LEDs (Red, Green, Yellow, Blue, Purple)
- Tap Sensor (Active-High)
- Breadboard and Jumper Wires

## 🛠️ Software

- Keil uVision or GCC ARM toolchain
- proteus 8 professional
- delay_headers.h, LCD_4Bit_header.h

## 🚀 Setup

1. Connect tap sensor to P0.7
2. Connect LEDs to P0.8–P0.12 with resistors
3. Connect LCD in 4-bit mode
4. Flash `main.c` to the LPC21xx
5. Observe LCD and LED behavior upon tapping

## 🎥 Demo

[demo video link](https://youtu.be/PORfqftTYU4)

---

🧑‍💻 Built by Shyam Ganesh for Bilimbe Embedded Interview Task
