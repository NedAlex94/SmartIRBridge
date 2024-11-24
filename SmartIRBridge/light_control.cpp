// light_control.cpp

#include "light_control.h"
#include "globals.h"    // Include the globals header
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Definition of the LightControl constructor and methods
LightControl::LightControl(int pin) {
  lightPin = pin;
  pinMode(lightPin, OUTPUT);      // Set the light pin as an output
  digitalWrite(lightPin, LOW);    // Ensure the light is off by default
}

void LightControl::turnOn() {
  digitalWrite(lightPin, HIGH);   // Set the pin HIGH to turn the light on
}

void LightControl::turnOff() {
  digitalWrite(lightPin, LOW);    // Set the pin LOW to turn the light off
}

void LightControl::blink(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(lightPin, HIGH);  // Turn the light on
    delay(500);                    // Wait for 500ms
    digitalWrite(lightPin, LOW);   // Turn the light off
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
