// TFT_eSPI by Bodmer is highly optimzed for ESP32.
// Note: After installing the library, you usually need to edit the User_Setup.h file in the library folder
//       to define your pins and display driver.

// #define ST7735_DRIVER

// #define TFT_WIDTH 128
// #define TFT_HEIGHT 160

// #define TFT_MISO 19
// #define TFT_MOSI 23
// #define TFT_SCLK 18
// #define TFT_CS 5
// #define TFT_DC 2
// #define TFT_RST 4

#include <TFT_eSPI.h>
#include <SPI.h>

// Invoke Library
TFT_eSPI tft = TFT_eSPI();

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(115200);

    // Initialize the TFT display
    tft.init();
    tft.setRotation(1); // 1 = Landscape (pins on the right)

    // Clear screen with a nice background
    tft.fillScreen(TFT_BLACK);

    // Set "cursor" to top left
    tft.setCursor(0, 0, 2); // Text at 0,0 using Font 2
    tft.setTextColor(TFT_WHITE);
    tft.println("Hello World!");

    tft.drawRect(0, 0, 160, 128, TFT_WHITE); // Draw a border around the edge
}

void loop()
{
    // We can make the text "blink" or change colors here
    tft.setCursor(90, 110, 2);
    tft.setTextColor(TFT_MAGENTA, TFT_BLACK); // Text Color, Background Color
    tft.print(millis() / 1000);
    tft.print("s");
    delay(1000);
}
