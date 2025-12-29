# Arduino Notebook

## Hardware

- ESP32 DevKit
- USB-C Cable

## Software

Arduino IDE or VS Code with Platform IO

## Arduino IDE

### Install Arduino IDE

1. Download and install the Arduino IDE from https://www.arduino.cc/en/software
2. Open Arduino IDE and go to `File -> Preferences`
3. In the "Additional Board Manager URLs" field, paste this URL:
    ```url
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json    
    ```
4. Click `Ok` and close `Preferences`.

### Install ESP32 Board Support

To tell the Arduino IDE how to talk to the ESP32:

1. Go to `Tools -> Boards -> Board Manager`
2. Search for `ESP32` and install the package by `Espressif Systems`
3. Wait for the installation to complete

### (Optional) Install the USB drivers if needed

If your ESP32 isn't detected. install CP210x or CH340 drivers.

### Connect ESP32 to yur PC

Plug in the ESP32 via USB.
Open `Tools -> Ports` and select the correct COM port for your ESP32.
