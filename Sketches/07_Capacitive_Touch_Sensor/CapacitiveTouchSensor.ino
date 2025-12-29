// Most pins on ESP32 can act as Capacitive Touch Sensors. This means the pin can detect the tiny change in electrical capacitance
// when your finger gets near it (just like a smartphone screen). You don't even need any components, just bare wires!

const int TOUCH_PIN = 4;         // This is actually "Touch 0" on the ESP32
const int LED_PIN = 2;           // Builtin LED
const int TOUCH_THRESHOLD = 600; // Anything below this counts as a touch

void setup()
{
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    // Read the touch value
    int touchValue = touchRead(TOUCH_PIN);

    // Print it so you can see your specific "touch signature"
    Serial.print("Touch Value: ");
    Serial.println(touchValue);

    // If the value drops below our threshold, turn on the LED
    if (touchValue < TOUCH_THRESHOLD)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    delay(100);
}

// You can tape that wire to the inside of a plastic box, and it will detect your touch through the plastic!
// You can turn any metal object (like a lamp or a piece of foil) into a button!
