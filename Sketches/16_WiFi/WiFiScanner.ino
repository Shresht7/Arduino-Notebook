#include "WiFi.h"

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);

    // Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    // Disconnect WiFi if it was previously connected
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup Done!");
}

void loop()
{
    Serial.println("Scanning for networks....");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Scan finished");

    if (n == 0)
    {
        Serial.println("No networks found!");
    }
    else
    {
        Serial.print(n);
        Serial.println(" networks found!");
        for (int i = 0; i < n; i++)
        {
            // Print SSID and RSSI (signal strength) for each network
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
            delay(10);
        }
    }

    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
