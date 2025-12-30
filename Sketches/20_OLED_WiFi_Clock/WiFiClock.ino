#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "time.h"

#include "secrets.h"

// WiFi Configuration
const char *ssid = SECRET_WIFI_SSID;
const char *password = SECRET_WIFI_PASSWORD;

// NTP Server Settings
const char *ntpServer = "pool.ntp.org";
const int gmtOffset_sec = 18000;
const int daylightOffset_sec = 0;

// OLED Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // No reset pin (-1 if sharing Arduino reset)
#define SCREEN_ADDRESS 0x3C // I2C Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    Serial.begin(115200);

    // Initialize OLED Display
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    display.clearDisplay();

    display.setTextSize(1);      // Font size
    display.setTextColor(WHITE); // Font Color
    display.setCursor(0, 0);     // Start Position
    display.dim(true);

    display.println("Connecting to WiFi...");
    display.display();

    // Connect to WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // Initialize NTP Time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Show IP on OLED
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Connected!");
    display.println(WiFi.localIP());
    display.display();
    delay(5000);
}

void loop()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return;
    }

    // Buffers to hold the hour and minute strings
    char hourString[3];
    char minString[3];

    // Format time into strings (Use %I for 12-hour, %H for 24-hour)
    strftime(hourString, 3, "%H", &timeinfo); // %H = 24-hour clock
    strftime(minString, 3, "%M", &timeinfo);  // %M = Minute

    // Draw the Vertical Clock
    display.clearDisplay();
    display.setRotation(1);

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(10, 5);
    display.println("////");

    // Draw Hour (Large Font)
    display.setTextSize(4);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 30);
    display.println(hourString);

    // Draw Minute
    display.setTextSize(4);
    display.setCursor(15, 70);
    display.println(minString);

    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(10, 115);
    display.println("////");

    display.display();

    delay(1000); // Update every second
}
