// Potentiometer or Rotary Encoder. Or anything really that is an analog sensor
const int POT_PIN = 34;

void setup()
{
    Serial.begin(115200);
    pinMode(POT_PIN, INPUT);
}

void loop()
{
    // Read the raw value (0 to 4095)
    int val = analogRead(POT_PIN);

    // Print it to the Serial Monitor
    Serial.print("Raw Value: ");
    Serial.print(val);

    delay(100); // Wait a bit so the text doesn't fly too fast
}

// Almost every analog sensor works the same way. e.g. Light Sensor (LDR), Moisture Sensor, Temperature Sensor etc. In all
// three cases, the exact same code will get the data.
