#include <Adafruit_NeoPixel.h>

#define PIN 16
#define NUMPIXELS 1

Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    pixel.begin();
    pixel.setBrightness(50);
}

void loop()
{
    pixel.setPixelColor(0, pixel.Color(255, 0, 0));
    pixel.show();
    delay(1000);

    pixel.setPixelColor(0, pixel.Color(0, 255, 0));
    pixel.show();
    delay(1000);

    pixel.setPixelColor(0, pixel.Color(0, 0, 255));
    pixel.show();
    delay(1000);
}
