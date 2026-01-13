#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress[] = {0x08, 0xB6, 0x1F, 0xC1, 0xB2, 0x8C};

// This same struct needs to be on the receiver
typedef struct struct_message
{
    char a[32];
    int b;
    float c;
} struct_message;

struct_message myData;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the peer (the receiver)
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop()
{
    // Fill the envelope
    strcpy(myData.a, "Hello Receiver!");
    myData.b = random(1, 100);
    myData.c = 1.23;

    // Send it!
    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
    delay(2000);
}
