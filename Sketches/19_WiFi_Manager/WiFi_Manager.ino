// In the world of microcontrollers, we don't have access to traditional OS features like "Environment Variables".

// 1. One way to handle this is to create a separate header file with all the secrets and add it to `.gitignore`
// 2. WiFi Manager allows the ESP32 to automatically start in a captive portal mode if it can't find a saved network.
//    You can then type in the WiFi credentials and the ESP32 will save them to its permanent internal memory (Flash)

#include <WiFiManager.h>

#define LED_PIN 2

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);

    // Create an instance of WiFi Manager
    WiFiManager wm;

    // Optional: Reset settings for testing (Uncomment to wipe saved WiFi Creds)
    // wm.resetSettings();

    // This one line does all the work:
    // 1. It tries to connect to the last known WiFi
    // 2. If it fails, it starts an Access Point named "ESP32_Config_AP"
    // 3. It waits for you to connect and enter credentials
    bool res = wm.autoConnect("ESP32_Config_AP", "password123");

    if (!res)
    {
        Serial.println("Failed to connect or hit timeout");
        // ESP.restart();
    }
    else
    {
        // If you get here, you are connected to your WiFi
        Serial.println("Connected! Happy days!");
        digitalWrite(LED_PIN, HIGH);
    }
}

void loop()
{
}
