// If Interrupts allow your microcontroller to "react" instantly to the world, Deep Sleep allows it to "ignore" it to save power.
// When you combine them, you get a device that can sleep 99% of the time to conserve power and only wake when something of note happens.
// This can extends the battery life of the device into years!

// Deep Sleep shuts down the CPU, WiFi and Bluetooth. Only a tiny timer and a few "RTC" (Real Time Clock) pins stay alive.
// When the ESP32 is in deep-sleep, the `loop()` stops. When it wakes up, it starts the code all the way from the beginning from `setup()`.
// It's like the board just pressed its own reset button.

#define uS_TO_S_FACTOR 1000000 // Conversion factor for microseconds to seconds
#define TIME_TO_SLEEP 10       // Time ESP32 will go to sleep (in seconds)

void setup()
{
    Serial.begin(115200);
    Serial.println("I am awake! Doing work....");

    // This is where you would read sensors and/or send ESP-NOW data

    // Configure the timer wakeup
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

    Serial.println("Going to sleep now. Good night.");
    esp_deep_sleep_start();
}

void loop()
{
    // This will never run as the device sleeps before the setup even ends!
}
