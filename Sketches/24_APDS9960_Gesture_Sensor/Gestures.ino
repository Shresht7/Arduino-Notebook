// APDS9960 is a impressive 4-in-1 sensor. Proximity, Ambient Light, Color (RGBC) and Gestures.
// VCC: 3.3V
// GND: GND
// SDA: GPIO21 (Default ESP32)
// SCL: GPIO22 (Default ESP32)
// INT (Interrupt): GPIO 4 or 19 (Important for low-latency gesture detection)

#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

void setup()
{
    Serial.begin(115200);

    if (!apds.begin())
    {
        Serial.println("Failed to initialize device! Check your wiring.");
    }
    else
    {
        Serial.println("Device initialized");
    }

    // Enable gesture sensing mode
    apds.enableGesture(true);
}

void loop()
{
    // Read the gesture
    uint8_t gesture = apds.readGesture();

    switch (gesture)
    {
    case UP:
        Serial.println("UP");
        break;
    case DOWN:
        Serial.println("DOWN");
        break;
    case LEFT:
        Serial.println("LEFT");
        break;
    case RIGHT:
        Serial.println("RIGHT");
        break;
    case NEAR:
        Serial.println("NEAR");
        break;
    case FAR:
        Serial.println("FAR");
        break;
    default:
        Serial.printf("OTHER: %d\n", gesture);
        break;
    }
}

// Gesture detection is actually a tiny state machine inside the sensor that tracks infrared reflections moving across four
// photodiodes (Up, Down, Left, Right)
