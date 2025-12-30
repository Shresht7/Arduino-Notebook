#include <Wire.h>
#include <BH1750.h>

// Connections
// VCC -> 3.3V (or 5V if the module has a regulator)
// GND -> GND
// SDA -> GPIO21 (or your SDA pin)
// SCL -> GPIO22 (or your SCL pin)
// ADDR -> GND (to force address 0x23)

BH1750 lightMeter;
#define ADDRESS 0x5C

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);

    // Initialize I2C. (defaults to SDA 21 and SCL 22)
    Wire.begin();

    delay(250);

    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, ADDRESS))
    {
        Serial.println(F("BH1750 Initialized Successfully!"));
    }
    else
    {
        Serial.println(F("Error initializing BH1750!"));
    }
}

void loop()
{
    // Read the light level in Lux
    float lux = lightMeter.readLightLevel();

    Serial.print("Light Level: ");
    Serial.print(lux);
    Serial.print(" lx");

    // Descriptive Feedback based on Lux Levels
    if (lux < 10)
    {
        Serial.println(" - [Dark]");
    }
    else if (lux < 100)
    {
        Serial.println(" - [Dim/Indoor]");
    }
    else if (lux < 1000)
    {
        Serial.println(" - [Bright Indoor]");
    }
    else
    {
        Serial.println(" - [Very Bright/Outdoor]");
    }

    delay(500);
}

// Unlike a simple analog sensor (which gives you a "raw" number between 0 and 4095), Lux is a calibrated standard.
// - Full Moon: 0.25 lux
// - Living Room: 50 lux
// - Office Lighting: 500 lux
// - Direct Sunlight: 32,000 to 100,000 lux
