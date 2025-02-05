# ESP32 Raw IR Transmitter

## Overview
This project is a **library-less** IR scheduled transmission arduino code designed for the **ESP32**. It allows users to transmit infrared signals based on a preconfigured schedule. The code utilizes **38kHz infrared signals** and supports **custom scheduling**.

## Features
- **Fully compatible with ESP32**
- **Library-less** implementation for efficient execution
- Uses **38kHz IR transmission** with an **8-bit resolution**
- Supports **custom schedules** for automation
- **Real-Time Clock (RTC)** integration for precise scheduling

## Hardware Requirements
- **ESP32**
- **IR LED** (connected to GPIO4 by default)
- **DS3231 RTC Module** (optional for persistent timekeeping)

## Infrared Signal Parameters
- **Carrier Frequency:** 38kHz
- **Duty Cycle:** ~33%
- **PWM Resolution:** 8-bit
- **GPIO Pin:** Default **GPIO4** (modifiable)

## Example Schedule Format
The system schedules actions based on a **24-hour format**:
```cpp
Schedule schedules[] = {
  {6, 00, 0},   // Perform action at 6:00 AM
  {14, 30, 1},  // Perform action at 2:30 PM
  {22, 15, 2},  // Perform action at 10:15 PM
};
```

## Example IR Signal Data
The IR transmission uses raw **pulse durations**, stored in `PROGMEM`. Example:
```cpp
const uint16_t IR_SAMPLE_1[] PROGMEM = {4132, 135, 200, 450, 315};
const uint16_t IR_SAMPLE_2[] PROGMEM = {5120, 250, 180, 370, 420};
```

## Usage
1. **Connect the IR LED and RTC module** to the ESP32.
2. **Upload the code** to your ESP32.
3. **Modify the schedule** to match your desired timing.
4. The system will automatically send IR signals based on the predefined schedule.

## Creator
Developed by **Anjum9694**

---
For modifications or contributions, feel free to submit a pull request!

