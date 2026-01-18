# Arduino with ESP32 Notebook

This repository is a collection of Arduino sketches for the ESP32, serving as a personal notebook and a quick reference for various hardware peripherals and programming concepts.

The ESP32 is a System on a Chip (SoC) microcontroller developed by [Espressif](https://www.espressif.com) that include Wi-Fi and Bluetooth wireless capabilities and a dual-core processor. The ESP32 can connect to a Wi-Fi network to connect to the internet (station mode); or create its own Wi-Fi network (Access Point mode) so that other devices can connect to it. It also supports Bluetooth classic and Bluetooth Low Energy (BLE).

[ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)

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

### Connect ESP32 to your PC

Plug in the ESP32 via USB.
Open `Tools -> Ports` and select the correct COM port for your ESP32.

### Uploading a Sketch

1. Connect the ESP32 to the computer
2. Select the correct `Port` under `Tools > Port`
3. Click the `Upload` arrow.
   > [!Note]: If you see `"Connecting..."`, you may need to hold down the `"BOOT"` button on the ESP32 until the upload starts.
   > [!Tip]: To check the code without "uploading", click on the `"Verify"` button. 

---
## PlatformIO (VS Code)

These sketches can also be used with PlatformIO, a powerful extension for Visual Studio Code.

### 1. Install PlatformIO

1. Download and install [Visual Studio Code](https://code.visualstudio.com/).
2. Open VS Code and go to the **Extensions** view (you can use the shortcut `Ctrl+Shift+X`).
3. Search for `PlatformIO IDE` and click **Install**.
4. Wait for the installation to complete, then reload VS Code if prompted.

### 2. Open a Sketch

The easiest way to run one of the sketches is to import it as a new PlatformIO project.

1. Open VS Code.
2. Click the **PlatformIO icon** (alien head) on the left-hand activity bar to open the PlatformIO Home screen.
3. From the home screen, click **Import Arduino Project**.
4. A wizard will appear:
   - For **Select Arduino Sketch Folder**, choose a sketch from this repository (e.g., `Sketches/00_Blink`).
   - For **Select Board**, search for and select `Espressif ESP32 Dev Module`.
5. Click **Import**.

PlatformIO will create a new project, including a `platformio.ini` configuration file, and copy the sketch into the `src` folder.

### 3. Build and Upload

- **Build**: Click the **Build** button (checkmark icon) in the PlatformIO toolbar at the bottom of the window to compile the code.
- **Upload**: Connect your ESP32, and click the **Upload** button (right arrow icon) in the toolbar. PlatformIO will automatically detect the port.

> [!Note]
> If you see `Connecting...` in the terminal, you may need to hold down the `BOOT` button on your ESP32 until the upload begins.

### 4. Managing Libraries

If a sketch requires external libraries (like the DHT sensor or OLED screen examples), you can add them to the `platformio.ini` file using the `lib_deps` option. PlatformIO will automatically download any required libraries.

Here is an example `platformio.ini` configuration:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    adafruit/DHT sensor library
    adafruit/Adafruit GFX Library
    adafruit/Adafruit SSD1306
```

---

## 📕 Resources

### Videos

- [Importance of "Blink without Delay" - YouTube Glenn McCall](https://www.youtube.com/watch?v=MRwaiFTkw_k&list=PL3kTorZwZbkBubi2q6TNwJ4UXTaTO9Qhs)
- [Pico Course for Beginners - Core Electronics - YouTube](https://www.youtube.com/watch?v=Ic4ExTusoTw)
- 🌟 [New Arduino Tutorials - YouTube Paul McWhorter](https://www.youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP)
- [Arduino Workshop for Beginners - Core Electronics - YouTube](https://www.youtube.com/playlist?list=PLPK2l9Knytg5s2dk8V09thBmNl2g5pRSr)
- [DigiKey Electronics FreeRTOS - YouTube](https://www.youtube.com/playlist?list=PLEBQazB0HUyQ4hAPU1cJED6t3DU0h34bz)

### Text

- https://randomnerdtutorials.com/getting-started-with-esp32/
- https://controllerstech.com/esp32/freertos-tutorials/

### References

- https://docs.arduino.cc/language-reference/
- https://www.arduinolibraries.info/

- https://www.reddit.com/r/arduino/wiki/guides/breadboards-explained/#wiki_breadboards_explained
- https://www.reddit.com/r/arduino/wiki/guides/protecting_pc_from_overloads/#wiki_protecting_your_pc_from_overloads
- https://www.reddit.com/r/arduino/comments/1ojjsyg/just_got_my_arduino_and_am_not_sure_where_to_start/
- https://old.reddit.com/r/PrintedCircuitBoard/wiki/books#wiki_embedded_boards
- https://www.reddit.com/r/arduino/comments/15ywzk8/great_resources_for_learning_and_teaching/
- https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/
- [Pinout](https://randomnerdtutorials.com/esp32-pinout-reference-gpios/)

### Drivers

- https://randomnerdtutorials.com/install-esp32-esp8266-usb-drivers-cp210x-windows/

### Extras

- https://protosupplies.com/guide-to-solderless-breadboards/
