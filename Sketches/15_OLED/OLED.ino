#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// This OLED is basically a grid of 128x64 light bulbs (pixels)
// - Top Left: 0, 0
// - Bottom Right: 127, 63

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define I2C_ADDRESS 0x3C // The I2C Address of the OLED Screen

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The -1 indicates that the display does not have a dedicated RESET pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);

    // Initialize the I2C
    Wire.begin();

    // Initialize the display
    if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS))
    {
        Serial.println(F("SSD1306 Initialization Failed!"));
        for (;;)
            ; // DONT PROCEED. LOOP FOREVER
    }

    Serial.println(F("SSD1306 Initialized!!!"));
    display.display(); // Adafruit logo is stored by default in the buffer. Display it for a few seconds.
    delay(2000);

    // Clear the buffer
    display.clearDisplay();

    // Set text properties
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top left corner

    // Say hello world!
    display.println(F("Hello World!"));

    // Call .display() to actually render the buffer
    display.display();
}

void loop()
{
}
