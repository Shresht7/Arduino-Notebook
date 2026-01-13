#include <esp_now.h>
#include <WiFi.h>

// Address of the gateway!
uint8_t gatewayAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message
{
    uint8_t nodeID;
    bool isDoorOpen;
    bool isKnock;
    float vbat;
    uint32_t bootCount;
} struct_message;

struct_message myData;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
        return;

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, gatewayAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    // Fill with dummy test data
    myData.nodeID = 1;
    myData.isDoorOpen = true;
    myData.isKnock = false;
    myData.vbat = 4.2;
    myData.bootCount = 1;

    esp_now_send(gatewayAddress, (uint8_t *)&myData, sizeof(myData));
    Serial.println("Test Packet Sent!");
}

void loop() {}
