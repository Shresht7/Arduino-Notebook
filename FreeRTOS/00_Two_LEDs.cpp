#include "Arduino.h"

#define LED1 2
#define LED2 4

void blink_task_1(void *pvParameters)
{
    // Setup
    pinMode(LED1, OUTPUT);

    // Loop
    while (true)
    {
        digitalWrite(LED1, HIGH);             // Turn on LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait 500ms
        digitalWrite(LED1, LOW);              // Turn off LED
        vTaskDelay(500 / portTICK_PERIOD_MS); // Wait 500ms
    }
}

void blink_task_2(void *pvParameters)
{
    // Setup
    pinMode(LED2, OUTPUT);

    // Loop
    while (true)
    {
        digitalWrite(LED2, HIGH);              // Turn on LED
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait 1000ms
        digitalWrite(LED2, LOW);               // Turn off LED
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait 1000ms
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.println("Creating Tasks....");
    // Create Tasks
    xTaskCreate(blink_task_1, "Blink1", 2048, NULL, 1, NULL);
    xTaskCreate(blink_task_2, "Blink2", 2048, NULL, 1, NULL);
}
