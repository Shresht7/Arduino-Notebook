// `ledcAttach` function sets up a LEDC pin with a given frequency and resolution. The LEDC channel is selected automatically.

// bool ledcAttach(uint8_t pin, uint32_t freq, uint8_t resolution);
// This function returns true if the configuration is successful, and false otherwise.

// If you prefer to setup the LEDC channel manually, you can use
// bool ledcAttachChannel(uint8_t pin, uint32_t freq, uint8_t resolution, uint8_t channel);
// This function also returns true if the configuration is successful and false otherwise.

// You can now use `ledcWrite` function to set the duty cycle of the PWM signal

#define LED_PIN 2

// PWM Properties
const int freq = 5000;
const int resolution = 8;

// As we're using 8-bit resolution, the duty cycle will be controlled using a value from 0 to 255.

void setup()
{
    // Configure LED PWM
    ledcAttach(LED_PIN, freq, resolution);
}

void loop()
{
    // Increase the LED brightness
    for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
    {
        // Changing the LED brightness with PWM
        ledcWrite(LED_PIN, dutyCycle);
        delay(15);
    }

    // Decrease the LED brightness
    for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
    {
        // Changing the LED brightness with PWM
        ledcWrite(LED_PIN, dutyCycle);
        delay(15);
    }
}
