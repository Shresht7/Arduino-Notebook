#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";
const char *mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

#define BAUD_RATE 115200

void setup()
{
    Serial.begin(BAUD_RATE);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
}

void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("s7mqtttest/test/status", "Hello from ESP32");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }

    client.loop();

    // Send a message every 5 seconds
    static unsigned long lastMsg = 0;
    if (millis() - lastMsg > 5000)
    {
        lastMsg = millis();
        client.publish("s7mqtttest/test/uptime", String(millis()).c_str());
        Serial.println("Sent uptime to broker");
    }
}
