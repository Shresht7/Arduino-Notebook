#include <Adafruit_APDS9960.h>
#include <Adafruit_NeoPixel.h>

Adafruit_APDS9960 apds;

#define PIN 16
#define NUMPIXELS 1
Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(115200);

    if (!apds.begin())
    {
        Serial.println("Failed to initialize device!");
    }

    // Enable Color Sensing Mode
    apds.enableColor(true);

    pixel.begin();
    pixel.setBrightness(50);
}

void loop()
{
    uint16_t r, g, b, c;

    // Wait for color data to be ready
    while (!apds.colorDataReady())
    {
        delay(5);
    }

    // Get the raw data
    apds.getColorData(&r, &g, &b, &c);

    pixel.setPixelColor(0, pixel.Color(r, g, b));

    delay(500);
}

// Clear (C) Measure Total Ambient Light. It is useful for knowing how bright the room is overall.
// Normalization: Raw values change based on distance and lighting. To get a "true" color
// you often calculate the ratio: redRatio = R / (R + G + B)
