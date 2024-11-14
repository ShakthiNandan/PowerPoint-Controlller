# ESP8266 Button Control with Python and PyAutoGUI

![Controllers](https://github.com/user-attachments/assets/a6b46014-35b0-4a1e-85e8-8965a5d5e9cb)

![Controller](https://github.com/user-attachments/assets/8fbff93e-c186-4bae-8ae4-1ac604075769)

This project demonstrates how to control volume (or simulate key presses) on your computer using an ESP8266 microcontroller and Python. The ESP8266 acts as a WiFi access point and hosts an HTTP server, allowing you to monitor button presses and control your computer through simulated key presses (e.g., left and right arrow keys).

## Components Needed:
- **ESP8266** (e.g., NodeMCU or Wemos D1 mini)
- **Push Buttons** (for Left and Right actions)
- **Breadboard and Jumper Wires** (for connecting buttons to ESP8266)
- **Computer with Python** installed
- **PyAutoGUI Library** (for simulating key presses)

## Circuit Setup:
1. Connect the **left button** to GPIO pin D5 (or your preferred pin).
2. Connect the **right button** to GPIO pin D6 (or your preferred pin).
3. Use `GND` and `VCC` to power the ESP8266 and buttons accordingly.

## ESP8266 Code:
The ESP8266 acts as a Wi-Fi access point and serves a simple HTML page that indicates whether the buttons are pressed.

- **Left Button** (GPIO D5) and **Right Button** (GPIO D6) are connected to the ESP8266.
- The ESP8266 serves an HTTP endpoint (`/`) that provides an HTML page with the current state of both buttons.
