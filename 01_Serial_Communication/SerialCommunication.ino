// Alternate way to initialize pins. Essentially a compile time constant
#define LED 2

void setup()
{
    // Start serial communication at 115200 bits per second (usually determined by the board)
    Serial.begin(115200);

    // Set the LED pin as output
    pinMode(LED, OUTPUT);

    Serial.println("System Initialized. Starting Blink...");
}

void loop()
{
    digitalWrite(LED, HIGH);
    Serial.println("LED is ON");
    delay(1000);

    digitalWrite(LED, LOW);
    Serial.println("LED is OFF");
    delay(1000);
}

// To view the Serial Monitor, click on the "Magnifying Glass" in the top-right corner of the Arduino IDE (or press Ctrl+Shift+M)
// Make sure the baud rate (bits per second) is set to the same 115200 bits per second. Otherwise you'll see "garbage" being printed out.

// Serial Monitor is your "window" into the ESP32's brain. When you code gets complex, `Serial.println` can be used to find out where things
// are going wrong.
