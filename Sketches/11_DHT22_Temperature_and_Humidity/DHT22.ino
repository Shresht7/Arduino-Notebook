// For the DHT22 we need to add a library because the sensor communicates using a
// unique "one-wire" pulse-timing protocol that is too complex to write from scratch as a beginner.

// # Installing the Library
// 1. In the Arduino IDE, go to `Sketch > Include Library > Manage Libraries...`
// 2. In the search bar, type "DHT22 Sensor Library"
// 3. There are many libraries to choose from. Pick one and click "Install"
// 4. It might ask to install "Adafruit Unified Sensors" as a dependency. Click "Install All"

// Most DHT22 sensors come on a small PCB with 3 pins (labelled +, - and out)
// - + (VCC): Connects to 3.3V
// - - (GND): Connects to GND
// Out (Data): Connects to GPIO26

// The DHT22 is a bit slow, it can only be read every 2 seconds. If you try to read it faster, it will return an error (NaN: Not a Number)

#include "DHT.h"

#define DHT_PIN 26 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22

#define BAUD_RATE 115200

// Initialize the sensor
DHT dht(DHT_PIN, DHTTYPE);

void setup()
{
    Serial.begin(BAUD_RATE);
    Serial.println("DHT22 Sensor Test");
    dht.begin();
}

void loop()
{
    // Wait a few seconds between measurements
    delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
    float h = dht.readHumidity();
    // Read temperature as Celsius (default)
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again)
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("% | ");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("C");
}

// DHT22 is a digital sensor, but is not binary (HIGH/LOW). Unlike the PIR sensor which is binary,
// this sensor sends a packet of 40 bits of data. The library decodes those pulses into numbers for us.

// DHT22 is much better than its little brother DHT11. It can measure sub-zero temperatures and decimal points for humidity.
