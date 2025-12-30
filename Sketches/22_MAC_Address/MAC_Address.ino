// To send a message to another ESP32, you need to know its MAC Address. Every devices has a unique one.

#include <WiFi.h>

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    WiFi.mode(WIFI_STA);
    Serial.print("Device MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {}
