#include <esp_now.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Network Credentials
const char *ssid = "SSID";
const char *password = "PASSWORD";
const char *mqtt_server = "192.168.1.XXX"; // Home Assistant IP

WiFiClient espClient;
PubSubClient client(espClient);

typedef struct struct_message
{
    uint8_t nodeID;
    bool isDoorOpen;
    bool isKnock;
    float vbat;
    uint32_t bootCount;
} struct_message;

struct_message incomingReadings;

// Callback function when the data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));

    // Prepare the JSON payload
    char buffer[128];
    snprintf(buffer, sizeof(buffer),
             "{\"door\": %s, \"knock\": %s, \"battery\": %.2f}",
             incomingReadings.isDoorOpen ? "true" : "false",
             incomingReadings.isKnock ? "true" : "false",
             incomingReadings.vbat);

    // Route to the correct topic based on nodeID
    String topic = "home/sensors/";

    switch (incomingReadings.nodeID)
    {
    case 1:
        topic += "front_door";
        break;
    case 2:
        topic += "back_door";
        break;
    case 3:
        topic += "garage_window";
        break;
    default:
        topic += "unknown_node";
        break;
    }

    // 3. Publish
    client.publish(topic.c_str(), buffer);
    Serial.print("Data from Node ");
    Serial.print(incomingReadings.nodeID);
    Serial.print(" sent to topic: ");
    Serial.println(topic);
}

// MQTT Reconnect function
void reconnect()
{
    while (!client.connected())
    {
        if (client.connect("ESP32_Gateway"))
        {
            client.subscribe("home/sensors/command");
        }
        else
        {
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    // Setup MQTT
    client.setServer(mqtt_server, 1883);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
        return;
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}
