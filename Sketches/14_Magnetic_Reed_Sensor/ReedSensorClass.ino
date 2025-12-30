// Magnetic Reed Sensor is a Digital Input similar to the buttons before
// but instead of pressing the button a magnetic field triggers it

// Inside the glass tube are two tiny metal reeds. When a magnet comes close, they get pulled
// together and complete the circuit. When the magnet moves away they spring apart.

#define LED_PIN 2
#define REED_PIN 25

#define BAUD_RATE 115200

class ReedSensor
{
private:
    int _pin;
    int _lastSteadyState;
    int _lastFlickerState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    bool _isClosed;

public:
    // Constructor: Sets the pin and the delay (defaults to 50ms)
    ReedSensor(int pin, unsigned long delayTime = 50)
    {
        _pin = pin;
        _debounceDelay = delayTime;
        _lastSteadyState = HIGH;
        _lastFlickerState = HIGH;
        _lastDebounceTime = 0;
        _isClosed = false;
    }

    // Call this in setup()
    void init()
    {
        pinMode(_pin, INPUT);
    }

    // Call this every loop() to process the logic
    void update()
    {
        // Read the raw value of the switch
        int currentReading = digitalRead(_pin);

        // If the switch changed (due to noise or movement)
        if (currentReading != _lastFlickerState)
        {
            _lastDebounceTime = millis(); // Reset the timer
        }

        // If the reading has been stable for longer than the delay...
        if ((millis() - _lastDebounceTime) > _debounceDelay)
        {

            // ... and if it's actually a new state
            if (currentReading != _lastSteadyState)
            {
                _lastSteadyState = currentReading;
                _isClosed = (_lastSteadyState == LOW);
            }
        }

        // Save the reading for next time
        _lastFlickerState = currentReading;
    }

    // Getter to check the status in your main code
    bool isClosed()
    {
        return _isClosed;
    }
};

ReedSensor sensor(25);

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    sensor.init();
}

void loop()
{
    // Update internal state of the sensor
    sensor.update();

    // use the data
    if (sensor.isClosed())
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}

// Like all mechanical switches, reed sensors can "bounce". When the magnet gets near, the metal strops might vibrate and touch each other many
// times in a millisecond before staying closed. If you were building a **security alarm** or **door counter** you would want to add a "Debounce"
// logic to make sure you only count the opening once.

// Why are Magnetic Reed Sensors Awesome?
// Zero Power: It consumes no electricity while waiting for a magnet
// Hidden: Can be hidden inside a door frame or behind plastic or wood.
// Since it's sealed in glass, it doesn't corrode like a standard button
