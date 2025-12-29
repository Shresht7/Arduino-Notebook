// Passive Infrared (PIR) Motion Sensor (HC-SR501)
// Just like a button! but triggered by heat/motion.

// Note: HC-SR501 needs 5V to power its internal circuitry.
// The ESP32 operates on a 3.3V logic, but it does have a 5V pin. The data sent by the sensor is 3.3V still.

// The HC-SR501 has two potentiometers:
// - One for Holding Time
// - Another for Sensitivity
// It also has jumper to switch between two modes.

#define LED_PIN 2
#define PIR_PIN 25

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    Serial.print("The sensor needs a couple of minutes to warm up and properly initialize...");
    delay(120 * 1000);
    Serial.println("Done Initializing!");
}

void loop()
{
    int detectedMotion = digitalRead(PIR_PIN);
    digitalWrite(LED_PIN, detectedMotion);
}
