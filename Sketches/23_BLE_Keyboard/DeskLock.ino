// When the sensor no longer detects your presence (goes LOW), it sends the system lock shortcut.

#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Desk Lock");

#define PROXIMITY_SENSOR_PIN 13

const unsigned long LOCK_DELAY = 5000; // 5 seconds of "no motion" before locking
unsigned long lastMotionTime = 0;
bool isLocked = false;

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(115200);
    pinMode(PROXIMITY_SENSOR_PIN, INPUT);
    bleKeyboard.begin();
    Serial.println("Desk Lock Active");
}

void loop()
{
    if (bleKeyboard.isConnected())
    {
        int sensorState = digitalRead(PROXIMITY_SENSOR_PIN);

        if (sensorState == HIGH)
        {
            // Reset the timer as long as motion is detected
            lastMotionTime = millis();
            if (isLocked)
            {
                Serial.println("Welcome back");
                isLocked = false;
            }
        }
        else
        {
            // No motion detected. Check if grace period has expired
            if (!isLocked && (millis() - lastMotionTime > LOCK_DELAY))
            {
                Serial.println("No one detected. Locking workstation...");

                // Windows LOCK: Win + L
                bleKeyboard.press(KEY_LEFT_GUI);
                bleKeyboard.press('l');
                delay(100);
                bleKeyboard.releaseAll();

                isLocked = true;
            }
        }
    }
}
