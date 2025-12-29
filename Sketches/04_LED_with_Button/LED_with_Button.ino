const int LED = 2;

// A IR Proximity Sensor is a binary sensor and thus can behave like a switch!
const int PROX_SENSOR = 4;

void setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);
    pinMode(PROX_SENSOR, INPUT);
}

void loop()
{
    int state = digitalRead(PROX_SENSOR);
    Serial.println(state);

    if (state == LOW)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }

    delay(100);
}
