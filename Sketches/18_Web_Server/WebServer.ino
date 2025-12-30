#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "password123";

// Initialize the Web Server on port 80 (default for http)
WebServer server(80);

#define LED_PIN 2 // Builtin LED

void handleRoot()
{
    String html = "<html><head>";
    html += "<title>ESP32 Access Point</title>";
    html += "</head><body>";

    html += "<h1>ESP32 LED Control</h1>";
    html += "<a href='/on'>Turn LED ON</a><br/>";
    html += "<a href='/off'>Turn LED OFF</a><br/>";

    html += "</body></html>";

    server.send(200, "text/html", html);
}

void handleLEDON()
{
    digitalWrite(LED_PIN, HIGH);
    server.sendHeader("Location", "/"); // Redirect to the main page automatically
    server.send(303);                   // HTTP Status Code
}

void handleLEDOFF()
{
    digitalWrite(LED_PIN, LOW);
    server.sendHeader("Location", "/"); // Redirect to the main page automatically
    server.send(303);                   // HTTP Status Code
}

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);

    WiFi.softAP(ssid, password);

    server.on("/", handleRoot);
    server.on("/on", handleLEDON);
    server.on("/off", handleLEDOFF);

    server.begin();
    // Retrieve the IP Address
    IPAddress IP = WiFi.softAPIP();
    Serial.printf("Web Server Started. Connect to %s\n", IP);
}

void loop()
{
    server.handleClient();
}
