// A single button to cycle through three "Modes"
// Mode 0: LED Off
// Mode 1: LED Constant On
// Mode 2: LED Blinking

#define LED_PIN 2

#define TOUCH_PIN 4
#define TOUCH_THRESHOLD 750

#define BAUD_RATE 115200

// State to track the current mode (0, 1 or 2) like an enum
int mode = 0;

bool lastButtonState = HIGH;

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    bool currentButtonState = buttonTouched();
    if (currentButtonState)
    {
        mode++; // Increment the current mode
        if (mode > 2)
            mode = 0; // Bound the mode between 0 and 2

        Serial.print("Mode changed to: ");
        Serial.println(mode);
        delay(50); // Simple debounce
    }
    lastButtonState = currentButtonState;

    // Execute the logic for the current mode
    switch (mode)
    {
    case 0: // OFF
        digitalWrite(LED_PIN, LOW);
        break;

    case 1: // ON
        digitalWrite(LED_PIN, HIGH);
        break;

    case 2: // BLINK
        if ((millis() / 500) % 2 == 0)
        {
            digitalWrite(LED_PIN, HIGH);
        }
        else
        {
            digitalWrite(LED_PIN, LOW);
        }
        break;
    }
}

bool buttonTouched()
{
    int touchValue = touchRead(TOUCH_PIN);
    return touchValue < TOUCH_THRESHOLD;
}
