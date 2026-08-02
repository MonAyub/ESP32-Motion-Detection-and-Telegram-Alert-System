# ESP32 Motion Detection Security System with Telegram Alerts

## Overview
This project is an ESP32-based smart security system that detects motion using a PIR sensor.
When motion is detected, the ESP32 sends a real-time alert message to a Telegram account.
It also sends a notification when motion stops. The system synchronizes time using an NTP server so every alert contains the current time.

## Features
- Motion detection using PIR sensor
- Real-time Telegram notifications
- LED indication for motion detection
- NTP time synchronization
- Wi-Fi connectivity
- Automatic system online notification

## Components Required
- ESP32 Development Board
- PIR Motion Sensor (HC-SR501)
- LED
- 220Ω Resistor
- Breadboard
- Jumper Wires
- Wi-Fi Connection

## Libraries Used
- WiFi
- WiFiClientSecure
- UniversalTelegramBot
- ArduinoJson
- time.h

## Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| PIR Sensor | GPIO 13 |
| LED | GPIO 14 |

## How It Works

1. ESP32 connects to Wi-Fi.
2. Synchronizes time using an NTP server.
3. Waits for the PIR sensor to stabilize.
4. Sends a "System Online" message to Telegram.
5. Continuously monitors the PIR sensor.
6. If motion is detected:
   - Turns ON the LED.
   - Sends a Telegram alert with the current time.
7. If motion stops:
   - Turns OFF the LED.
   - Sends a "No More Motion" message with the current time.

## Installation

1. Clone this repository.
2. Open the project using Arduino IDE.
3. Install the required libraries.
4. Update the following information in the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"
```

5. Select the ESP32 board.
6. Upload the code.
7. Open the Serial Monitor.

## Project Structure

```
ESP32-Telegram-Security-System/
│
├── ESP32_Telegram_Security_System.ino
├── README.md
├── circuit_diagram.png
├── flowchart.png
├── algorithm.pdf
└── images/
    ├── setup.jpg
    └── telegram_alert.png
```

## Future Improvements

- Buzzer Alarm
- Camera Integration
- Email Notifications
- Cloud Data Logging
- Mobile Dashboard

## Author

Monirojjaman Ayoive

Department of ICT

Mawlana Bhashani Science and Technology University (MBSTU)

## License

This project is for educational purposes.
