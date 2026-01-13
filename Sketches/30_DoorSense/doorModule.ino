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
RTC_DATA_ATTR int bootCount = 0; // This variable survives deep sleep

void setup()
{
    Serial.begin(115200);
    bootCount++;

    // Identify Wakeup Reason
    esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();

    // Read Sensors
    pinMode(32, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);

    myData.nodeID = 1;
    myData.isDoorOpen = (digitalRead(32) == HIGH); // High -> Magnet Away (Open)
    myData.isKnock = (wakeup_reason == ESP_SLEEP_WAKEUP_EXT1 && digitalRead(33) == LOW);
    myData.bootCount = bootCount;

    // Read Battery
    int raw = analogRead(34);
    myData.vbat = (raw / 4095.0) * 3.3 * 2.0; // *2 for 1:1 voltage divider.

    // Send data via ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() == ESP_OK)
    {
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, gatewayAddress, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        esp_now_add_peer(&peerInfo);
        esp_now_send(gatewayAddress, (uint8_t *)&myData, sizeof(myData));
        delay(100); // Give the radio 100ms to finish
    }

    // Configure Wakeup Sources
    // We want either pin 32 or 33
    uint64_t pin_mask = (1ULL << 32) | (1ULL << 33);

    // Wakeup if any of these pins go low (vibration) or high (door open)
    esp_sleep_enable_ext1_wakeup(pin_mask, ESP_EXT1_WAKEUP_ANY_HIGH);

    Serial.println("Entering deep sleep...");
    esp_deep_sleep_start();
}

void loop() {}
