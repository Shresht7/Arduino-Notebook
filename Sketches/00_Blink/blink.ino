// The Pin Number of the builtin LED
const int LED = 2;

// The setup function runs once when the board powers up
void setup()
{
    // Initialize the LED pin as OUTPUT
    pinMode(LED, OUTPUT);
}

// The loop functions runs indefinitely
void loop
{
    digitalWrite(LED, HIGH); // Turn LED ON (HIGH voltage level)
    delay(1000);             // Wait for 1 second (1000ms)
    digitalWrite(LED, LOW);  // Turn LED OFF (LOW voltage level)
    delay(1000);             // Wait for 1 second (1000ms)
}
