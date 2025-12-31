#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

void setup()
{
    Serial.begin(115200);

    if (!apds.begin())
    {
        Serial.println("Failed to initialize device!");
    }

    // Enable Color Sensing Mode
    apds.enableColor(true);
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

    Serial.print(" C: ");
    Serial.print(c);
    Serial.print(" R: ");
    Serial.print(r);
    Serial.print(" G: ");
    Serial.print(g);
    Serial.print(" B: ");
    Serial.print(b);
    Serial.println("");

    if (r > g && r > b)
    {
        Serial.println("Detected RED");
    }
    else if (g > r && g > b)
    {
        Serial.println("Detected GREEN");
    }
    else if (b > r && b > g)
    {
        Serial.println("Detected BLUE");
    }

    delay(500);
}

// Clear (C) Measure Total Ambient Light. It is useful for knowing how bright the room is overall.
// Normalization: Raw values change based on distance and lighting. To get a "true" color
// you often calculate the ratio: redRatio = R / (R + G + B)
