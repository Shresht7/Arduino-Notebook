// Magnetic Reed Sensor is a Digital Input similar to the buttons before
// but instead of pressing the button a magnetic field triggers it

// Inside the glass tube are two tiny metal reeds. When a magnet comes close, they get pulled
// together and complete the circuit. When the magnet moves away they spring apart.

#define LED_PIN 2
#define REED_PIN 25

#define BAUD_RATE 115200

// STATE
// -----

int reedState;                      // Current reading
int lastSteadyState = HIGH;         // The "confirmed" state
int lastFlickerState = HIGH;        // The last raw reading
unsigned long lastDebounceTime = 0; // The last time the pin flickered
unsigned long debounceDelay = 50;   // 50ms is the "sweet spot" for switches

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    pinMode(REED_PIN, INPUT);
}

void loop()
{
    // Read the raw value of the switch
    int currentReading = digitalRead(REED_PIN);

    // If the switch changed (due to noise or movement)
    if (currentReading != lastFlickerState)
    {
        lastDebounceTime = millis(); // Reset the timer
    }

    // If the reading has been stable for longer than the delay...
    if ((millis() - lastDebounceTime) > debounceDelay)
    {

        // ... and if it's actually a new state
        if (currentReading != lastSteadyState)
        {
            lastSteadyState = currentReading;

            // Now we act on the confirmed changes
            if (lastSteadyState == LOW)
            {
                digitalWrite(LED_PIN, HIGH);
            }
            else
            {
                digitalWrite(LED_PIN, LOW);
            }
        }
    }

    // Save the reading for next time
    lastFlickerState = currentReading;
}

// Like all mechanical switches, reed sensors can "bounce". When the magnet gets near, the metal strops might vibrate and touch each other many
// times in a millisecond before staying closed. If you were building a **security alarm** or **door counter** you would want to add a "Debounce"
// logic to make sure you only count the opening once.

// Why are Magnetic Reed Sensors Awesome?
// Zero Power: It consumes no electricity while waiting for a magnet
// Hidden: Can be hidden inside a door frame or behind plastic or wood.
// Since it's sealed in glass, it doesn't corrode like a standard button
