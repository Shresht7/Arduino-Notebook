// A more useful way to combine interrupts and deep-sleep is to stay asleep until a pin changes.

// We can use a PIR sensor to wake up the ESP32 using the Ext0 Wakeup. This allows the ESP32 to drop its power consumption from ~70mA (active)
// to about ~10uA (deep sleep)

// The PIR sensor needs to be connected to a GPIO pin that is "RTC capable". (On ESP32 these are: 33, 32, 27, 26, 25, 15, 14, 13, 12, 4, 2, 0)

#include <esp_now.h>
#include <WiFi.h>

// Replace with receiver's MAC address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct struct_message
{
    char msg[32];
    int status;
} struct_message;

struct_message myData;

void setup()
{
    Serial.begin(115200);

    // Initialize WiFi and ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register Peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    // Send the alert
    strcpy(myData.msg, "MOTION DETECTED!");
    myData.status = 1;
    esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

    Serial.println("Alert Sent!");

    // Configure Wakeup: Wake up when Pin 33 goes HIGH (PIR detects motion)
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1);

    // Go to sleep
    Serial.println("Entering Deep Sleep...");
    esp_deep_sleep_start();
}

void loop()
{
    // Never reached!
}

// Important Note: PIR sensors usually need 30-60 seconds to "calibrate" to the room's infrared signature when they first get power.
// If the power is cut to the PIR sensor during sleep, it will falsely trigger everytime it wakes up. The  PIR sensor must be powered while the ESP32 sleeps.
// PIR sensors are surprisingly efficient. Even if they are constantly on, they consume very little power.

// On each wakeup, the setup runs from start. If you want to keep track of how many times motion was detected, you need to use a special variable prefix:
// RTC_DATA_ATTR int boolCount = 0;
// Variables with this prefix are stored in RTC memory and survive deep sleep
