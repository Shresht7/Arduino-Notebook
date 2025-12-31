// The previous example used polling. It constantly asked the sensor for data.
// Interrupts flip the script. The ESP32 goes about its business (or sleeps), and the APDS-9960
// "taps it on the shoulder" only when a gesture is actually detected.
// The APDS-9960 has an INT pin. When a gesture is sensed, this pin pulls LOW.

#include <Adafruit_APDS9960.h>

Adafruit_APDS9960 apds;

// Interrupt pin
const int INT_PIN = 4;

// "volatile tells the compiler that this changes out the main flow
// Prevents the compiler from optimizing the variable away. It tells the ESP32, that this variable can change at any
// millisecond from an outside trigger.
volatile bool gestureDetected = false;

// This is the Interrupt Service Routine (ISR)
// It must be as short as possible
// IRAM_ATTR tells the ESP32 to store the interrupt function in RAM instead of Flash. It makes the response time much faster.
void IRAM_ATTR ISR_Gesture()
{
    gestureDetected = true
}

void setup()
{
    Serial.begin(115200);
    pinMode(INT_PIN, INPUT_PULLUP);

    if (!apds.begin())
    {
        Serial.println("Failed to initialize device");
    }

    apds.enableGesture(true);

    // Set up the interrupt:
    // Trigger when the INT_PIN goes from HIGH to LOW (FALLING)
    attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_Gesture, FALLING);
}

void loop()
{
    if (gestureDetected)
    {
        handleGesture();
        gestureDetected = false; // Reset the flag
    }

    // The CPU can now do other heavy tasks here without missing a gesture
}

void handleGesture()
{
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
