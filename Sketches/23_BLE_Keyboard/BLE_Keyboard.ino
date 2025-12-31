#include <BleKeyboard.h>

// Initialize the Bluetooth Keyboard with a name and manufacturer
BleKeyboard bleKeyboard("ESP32 Keyboard", "S7 Tech");

#define PROXIMITY_SENSOR_PIN 13 // Pin connected to proximity sensor
int lastSensorState = LOW;

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(PROXIMITY_SENSOR_PIN, INPUT);

    Serial.println("Starting BLE Keyboard");

    // Initialize the Bluetooth Keyboard
    bleKeyboard.begin();
}

void loop()
{
    if (bleKeyboard.isConnected())
    {
        int currentSensorState = digitalRead(PROXIMITY_SENSOR_PIN);

        // Trigger once when the state changes from LOW to HIGH
        if (currentSensorState == HIGH && lastSensorState == LOW)
        {
            Serial.println("Proximity detected! Sending Key...");
            bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

            // Small delay to prevent multiple triggers from one movement
            delay(500);
        }

        lastSensorState = currentSensorState;
    }
}
