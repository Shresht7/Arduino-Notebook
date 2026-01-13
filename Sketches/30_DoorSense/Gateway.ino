#include <esp_now.h>
#include <WiFi.h>

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
    Serial.println("--- NEW PACKET RECEIVED ---");
    Serial.print("Node ID: ");
    Serial.println(incomingReadings.nodeID);
    Serial.print("Door Status: ");
    Serial.println(incomingReadings.isDoorOpen ? "OPEN" : "CLOSED");
    Serial.print("Vibration/Knock: ");
    Serial.println(incomingReadings.isKnock ? "YES" : "NO");
    Serial.print("Battery: ");
    Serial.print(incomingReadings.vbat);
    Serial.println("V");
    Serial.print("Total Wakeups: ");
    Serial.println(incomingReadings.bootCount);
    Serial.println("---------------------------");
}

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
    Serial.println("Gateway is listening...");
}

void loop() {}
