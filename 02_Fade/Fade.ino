// The pin number of the builtin LED
const int LED = 2;

// Brightness Level
int brightness = 0;
int fadeStep = 5;
int fadeDelay = 30;

// The setup function runs once when the board powers up
void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    Serial.println("Starting Fade Effect...");
}

// The loop functions runs over and over indefinitely
void loop()
{
    // Set the brightness level of the LED
    analogWrite(LED, brightness);

    // Print a "graph" to the Serial Plotter
    Serial.println(brightness);

    // Update the brightness level
    brightness += fadeStep;

    // Check if we've reached the bounds and reverse the fadeStep direction
    if (brightness <= 0 || brightness >= 255)
    {
        fadeStep *= -1;
        Serial.println("--- Direction Reversed ---")
    }

    delay(fadeDelay); // Wait for some duration before the next iteration of the loop
}

// In an ESP32, this is achieved using Pulse Width Modulation (PWM).
// The ESP32 can't actually output "2.5 volts". It can only do 0V or 3.3V. To get a "fade", it switches the pin on and off incredibly fast.
// 0% Duty Cycle: The pin is always off (0V)
// 50% Duty Cycle: The pin is on half the time (looks like half brightness)
// 100% Duty Cycle: The pin is always on (3.3V)

// Serial Plotter
// The standard Serial Monitor just shows a list of numbers.
// Go to `Tools > Serial Plotter`
// Ensure the speed is 115200 baud
// You will see a triangle wave representing the LED brightness.

// Caution: If the LED just stays on or off and doesn't fade. Check the Pins, some ESP32 pins are "Input Only" (GPIO 34, 35, 36, and 39).
