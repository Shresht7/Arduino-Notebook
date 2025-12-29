// Up until now, we used `delay()`. When the ESP32 hits `delay(1000)`, it stops everything and freezes.
// It cannot check a button, it cannot process a WiFi signal, and it cannot read a sensor.

// To do these tasks in a non-blocking way, we use `millis()`. Instead of saying "Wait 1 second", we say "Check the time. Is it 1 second later?"

const int LED1 = 2; // Builtin LED
const int LED2 = 5; // External LED

// State variables to keep track of time since last blink for each LED
unsigned long lastTime1 = 0;
unsigned long lastTime2 = 0;

// State variables to keep track of the LEDs
bool state1 = LOW;
bool state2 = LOW;

void setup()
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
}

void loop()
{
    unsigned int currentTime = millis(); // Get the current time

    // Blink LED1 every 500ms
    if (currentTime - lastTime1 >= 500)
    {
        // 500ms has elapsed since lastTime1
        state1 = !state1; // Toggle state
        digitalWrite(LED1, state1);
        lastTime1 = currentTime; // Update lastTime1
    }

    // Blink LED2 every 1200ms
    if (currentTime - lastTime2 >= 1200)
    {
        // 1200ms has elapsed since lastTime2
        state2 = !state2; // Toggle state
        digitalWrite(LED2, state2);
        lastTime2 = currentTime; // Update lastTime2
    }
}

// This is especially
