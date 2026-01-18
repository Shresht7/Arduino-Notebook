const int POT_PIN = 34; // Input from potentiometer knob
const int LED_PIN = 2;  // Built-in LED

void setup()
{
    Serial.begin(115200);
    pinMode(POT_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    // Read the potentiometer knob position
    int potValue = analogRead(POT_PIN);

    // Map the value to a delay (in milliseconds)
    // Higher potValue -> Lower delay (faster blinking)
    // We will use the `map()` function. This is a math helper function that converts one range of numbers into another
    int blinkSpeed = map(potValue, 0, 4095, 1000, 50);

    Serial.print("Potentiometer: ");
    Serial.print(potValue);
    Serial.print(" | Delay: ");
    Serial.print(blinkSpeed);
    Serial.println("ms");

    // Perform the blink
    blink(blinkSpeed);
}

void blink(int blinkSpeed)
{
    digitalWrite(LED_PIN, HIGH);
    delay(blinkSpeed);
    digitalWrite(LED_PIN, LOW);
    delay(blinkSpeed);
}
