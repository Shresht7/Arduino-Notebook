// Hardware interrupts
// Normally, your code runs in a "polling" loop. If you have a `delay(5000)` , the microcontroller suspends execution and is blind for that period.
// An Interrupt breaks through that. It forces the CPU to stop whatever it's doing, run a tiny function (called an ISR - Interrupt Service Routine)
// and then go back to where it left off.

// The Rule of Interrupts:
// - Keep it short and fast. Don't delay.
// - Volatile Variables: Any mutable variable used in an ISR must be declared as `volatile`.

#define BUTTON_PIN 14
#define LED_PIN 2

volatile bool ledState = false;

// The Interrupt Service Routine (ISR)
void IRAM_ATTR handleButtonPress()
{
    ledState = !ledState; // Toggle led
    digitalWrite(LED_PIN, ledState);
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Trigger when pin goes from HIGH to LOW (falling edge)
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}

void loop()
{
    // Simulate a very "busy" program
    delay(10000);
}
