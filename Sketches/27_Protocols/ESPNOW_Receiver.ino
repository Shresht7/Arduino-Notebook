#include <esp_now.h>
#include <WiFi.h>

// This MUST match the Sender's struct exactly
typedef struct struct_message
{
    char a[32];
    int b;
    float c;
} struct_message;

struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&myData, incomingData, sizeof(myData));

    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Message: ");
    Serial.println(myData.a);
    Serial.print("Int: ");
    Serial.println(myData.b);
    Serial.print("Float: ");
    Serial.println(myData.c);
    Serial.println();
}

void setup()
{
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the callback function
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void loop()
{
    // The Receiver doesn't need to do anything in the loop!
    // It just waits for the Callback to trigger.
}
