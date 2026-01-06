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

---

## Uploading

1. Connect the ESP32 to the computer
2. Select the correct `Port` under `Tools > Port`
3. Click the `Upload` arrow.
   > [!Note]: If you see `"Connecting..."`, you may need to hold down the `"BOOT"` button on the ESP32 until the upload starts.
   > [!Tip]: To check the code without "uploading", click on the `"Verify"` button. 

---

## 📕 Resources

- https://www.reddit.com/r/arduino/wiki/guides/breadboards-explained/#wiki_breadboards_explained
- https://protosupplies.com/guide-to-solderless-breadboards/
- https://www.reddit.com/r/arduino/wiki/guides/protecting_pc_from_overloads/#wiki_protecting_your_pc_from_overloads

- https://www.reddit.com/r/arduino/comments/1ojjsyg/just_got_my_arduino_and_am_not_sure_where_to_start/
- https://old.reddit.com/r/PrintedCircuitBoard/wiki/books#wiki_embedded_boards
- https://www.reddit.com/r/arduino/comments/15ywzk8/great_resources_for_learning_and_teaching/

- 🌟 [New Arduino Tutorials - YouTube Paul McWhorter](https://www.youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP)
- [Importance of "Blink without Delay" - YouTube Glenn McCall](https://www.youtube.com/watch?v=MRwaiFTkw_k&list=PL3kTorZwZbkBubi2q6TNwJ4UXTaTO9Qhs)

- https://docs.arduino.cc/language-reference/
- https://www.arduinolibraries.info/
