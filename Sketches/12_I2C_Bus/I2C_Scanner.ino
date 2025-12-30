// Unlike the DHT22 or the PIR sensor, which each need their own dedicated pin,
// I2C is a "party line". It can connect up to 127 different sensors to the same two wires,
// and the ESP32 can talk to them individually using their "address"

// Every I2C device uses these two pins:
// - SDA (Serial Data): The line where the actual data travels
// - SCL (Serial Clock): The "metronome" that keeps the devices in sync
// On an ESP32 the default pins are:
// - SDA: GPIO21
// - SCL: GPIO22

// The ADDR pin on sensors like the BHT1750 is used when you want to use two of these sensors as once.

#include <Wire.h>

// These are the defaults, but let's define them explicitly anyway
#define I2C_SDA 21
#define I2C_SCL 22

#define BAUD_RATE 115200

void setup()
{
    Wire.begin(I2C_SDA, I2C_SCL);
    Serial.begin(BAUD_RATE);
    Serial.println("I2C Scanner");
}

void loop()
{
    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
                Serial.print("0");
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++;
        }
    }

    if (nDevices == 0)
        Serial.println("No I2C devices found!!!");
    else
        Serial.println("DONE!!!");

    delay(5000);
}
