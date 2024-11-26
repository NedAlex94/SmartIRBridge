// light_control.cpp

#include "light_control.h"
#include "globals.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Define the light pin
const uint16_t LIGHT_PIN = 18;

// Definition of the LightControl constructor and methods
LightControl::LightControl() {
    pinMode(LIGHT_PIN, OUTPUT);       // Set the light pin as an output
    digitalWrite(LIGHT_PIN, LOW);     // Ensure the light is off by default
}

void LightControl::turnOn() {
    digitalWrite(LIGHT_PIN, HIGH);    // Set the pin HIGH to turn the light on
}

void LightControl::turnOff() {
    digitalWrite(LIGHT_PIN, LOW);     // Set the pin LOW to turn the light off
}


/**
 * Blinks the light a specified number of times.
 * Will later be used to show the user that connection is in progress.
 */
void LightControl::blink(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LIGHT_PIN, HIGH); // Turn the light on
        delay(500);                    // Wait for 500ms
        digitalWrite(LIGHT_PIN, LOW);  // Turn the light off
        delay(500);                    // Wait for 500ms
    }
}

// Implementation of the ledBlinkTask
void ledBlinkTask(void *parameter) {
    LightControl *light = static_cast<LightControl *>(parameter);

    while (wifiScanning) {             // Accessing the global variable
        light->turnOn();
        vTaskDelay(250 / portTICK_PERIOD_MS);  // LED on for 250ms
        light->turnOff();
        vTaskDelay(250 / portTICK_PERIOD_MS);  // LED off for 250ms
    }

    light->turnOff();                   // Ensure the light is off after blinking
    vTaskDelete(NULL);                  // Delete the task when done
}
