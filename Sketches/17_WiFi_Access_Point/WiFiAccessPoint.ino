#include <WiFi.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "password123"; // Password for the WiFi AP. Must be at least 8 characters.

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    Serial.println("Creating WiFi Access Point...");

    // Start WiFi Access Point
    WiFi.softAP(ssid, password);

    // Retrieve the IP Address
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP Address: ");
    Serial.println(IP); // Usually 192.168.4.1
}

void loop()
{
    // We can see how many "stations" (devices like phones/laptops) are connected
    Serial.printf("Station Connected: %d\n", WiFi.softAPgetStationNum());
    delay(2000);
}
