// # Buttons
//
// ## Pull Up
//
// In electronics, an input pin can't just be "left floating". If a pin isn't connected to anything, it will pick up electrical noise from the air and flip randomly between `HIGH` and `LOW`.
//
// To fix this, we use a **Pull-up Resistor**. The ESP32 actually has these built-in!
//
// ## Connection
//
// To connect a "momentary switch" button:
// - Connect one side of the button to a GPIO pin like `GPIO4`
// - Connect the other side of the button to `GND`

// The pin number for the button
const int BUTTON = 4;

void setup()
{
    Serial.begin(115200);
    pinMode(BUTTON, INPUT);
}

void loop()
{
    int state = digitalRead(BUTTON);
    Serial.println(state);
    delay(100);
}
