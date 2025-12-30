#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "secrets.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WebServer server(80);
String currentMessage = "Ready..."; // Default Message

const char *INDEX_HTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: 'Segoe UI', sans-serif;
      text-align: center;
      background: #121212;
      color: white;
      margin: 0;
      padding: 20px;
    }
    .container {
      background: #1e1e1e;
      padding: 30px;
      border-radius: 15px;
      box-shadow: 0 10px 20px rgba(0,0,0,0.5);
    }
    input[type='text'] {
      padding: 12px;
      width: 80%;
      border-radius: 8px;
      border: none;
      font-size: 16px;
      margin-bottom: 20px;
    }
    input[type='submit'] {
      background: #007bff;
      color: white;
      border: none;
      padding: 12px 25px;
      border-radius: 8px;
      font-size: 16px;
      cursor: pointer;
      transition: 0.3s;
    }
    input[type='submit']:hover { background: #0056b3; }
    h1 { color: #00d4ff; }
  }
  </style>
</head>
<body>
  <div class="container">
    <h1>OLED Screen</h1>
    <form action="/setMessage" method="POST">
      <input type="text" name="msg" placeholder="Type message here..." maxLength="50">
      <br>
      <input type="submit" value="Update Screen">
    </form>
  </div>
</body>
</html>
)rawliteral";

void handleRoot()
{
    server.send(200, "text/html", INDEX_HTML);
}

void handleSetMessage()
{
    if (server.hasArg("msg"))
    {
        currentMessage = server.arg("msg");

        display.stopscroll();
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 20);
        display.println(currentMessage);
        display.display();
        display.startscrollright(0x00, 0x0F);
    }
    server.sendHeader("Location", "/"); // Redirect to main page
    server.send(303);
}

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS))
    {
        for (;;)
            ;
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.println("Connecting...");
    display.display();

    WiFi.begin(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Online!");
    display.println(WiFi.localIP());
    display.display();

    server.on("/", handleRoot);
    server.on("/setMessage", HTTP_POST, handleSetMessage);
    server.begin();
}

void loop()
{
    server.handleClient();
}
