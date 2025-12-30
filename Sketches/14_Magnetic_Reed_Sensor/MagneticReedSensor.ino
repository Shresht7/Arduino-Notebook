// Magnetic Reed Sensor is a Digital Input similar to the buttons before
// but instead of pressing the button a magnetic field triggers it

// Inside the glass tube are two tiny metal reeds. When a magnet comes close, they get pulled
// together and complete the circuit. When the magnet moves away they spring apart.

#define LED_PIN 2
#define REED_PIN 25

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    pinMode(REED_PIN, INPUT);
}

void loop()
{
    // Read the state. (HIGH = Open/No Magnet, LOW = Closed/Magnet)
    int magnetInProximity = digitalRead(REED_PIN);
    Serial.print(magnetInProximity);

    if (magnetInProximity == LOW)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    // Small delay to keep the Serial Monitor Readable
    delay(100);
}

// Like all mechanical switches, reed sensors can "bounce". When the magnet gets near, the metal strops might vibrate and touch each other many
// times in a millisecond before staying closed. If you were building a **security alarm** or **door counter** you would want to add a "Debounce"
// logic to make sure you only count the opening once.

// Why are Magnetic Reed Sensors Awesome?
// Zero Power: It consumes no electricity while waiting for a magnet
// Hidden: Can be hidden inside a door frame or behind plastic or wood.
// Since it's sealed in glass, it doesn't corrode like a standard button
