// SmartIRBridge.ino

// Uses IRremote, an MIT Library for IR signal decoding and handling
// Install it from https://github.com/Arduino-IRremote/Arduino-IRremote
#include <IRremote.hpp>

#include "wps_button.h"    
#include "wifi_helper.h"  
#include "light_control.h" 

// GPIO pin where the IR receiver's Vout is connected
const uint16_t RECV_PIN = 15;

// GPIO pin for the WPS button
const uint16_t WPS_BUTTON_PIN = 16;

// GPIO pin for the light
const uint16_t LIGHT_PIN = 18;

// Create WPSButton obj
WPSButton wpsButton(WPS_BUTTON_PIN);

// Create LightControl obj for GPIO 18
LightControl light(LIGHT_PIN);

// Task handle for Wi-Fi scanning
TaskHandle_t wifiScanTaskHandle = NULL;

// Flag indicates Wi-Fi scanning in progress
volatile bool wifiScanning = false;

void setup() {
  Serial.begin(115200);         // Initialize serial communication
  IrReceiver.begin(RECV_PIN);   // Start the IR receiver on the specified pin
  Serial.println("IR Receiver is initialized. Waiting for signals...");
  Serial.println("WPS Button initialized. Waiting for input...");

  // Light starts off by default
  light.turnOff();
}

void loop() {
  // Handle WPS button
  if (wpsButton.isPressed()) {
    if (!wifiScanning) {
      Serial.println("Button pressed! Starting Wi-Fi scan...");
      wifiScanning = true;

      // Start the Wi-Fi scanning task
      xTaskCreatePinnedToCore(
        wifiScanTask,      // Task function
        "WiFiScanTask",    // Name of the task
        4096,              // Stack size in bytes
        NULL,              // Task input parameter
        1,                 // Priority of the task
        &wifiScanTaskHandle, // Task handle
        0                  // Core to run the task
      );
    }
  }

  // Continue handling other tasks
  handleIR();
}


// Function that handles IR processing
void handleIR() {
  if (IrReceiver.decode()) {
    uint32_t decodedData = IrReceiver.decodedIRData.decodedRawData;

    if (decodedData == 0) {
      Serial.println("Repeat Signal Detected");
    } else {
      Serial.print("Decoded Data: ");
      Serial.println(decodedData, HEX);
    }

    IrReceiver.resume(); // Resume the IR receiver for the next signal
  }
}

// FreeRTOS task for Wi-Fi scanning
void wifiScanTask(void *parameter) {
    Serial.println("Wi-Fi scan started...");

    // Start the LED blinking task
    xTaskCreatePinnedToCore(
        ledBlinkTask,             // Blinking task function
        "LEDBlinkTask",           // Name of the task
        2048,                     // Stack size in bytes
        NULL,                     // Task input parameter
        1,                        // Priority of the task
        NULL,                     // Task handle not needed
        1                         // Core to run the task (can be 0 or 1)
    );

    // Perform the Wi-Fi scan
    scanAndPrintWiFiNetworks();  // Calls Wi-Fi scanning function
    Serial.println("Wi-Fi scan complete.");

    // Stop the blinking
    wifiScanning = false;  // Flag for blinking task to terminate

    // Delete this Wi-Fi scan task
    vTaskDelete(NULL);
}




void ledBlinkTask(void *parameter) {
  while (wifiScanning) {
    light.turnOn();
    vTaskDelay(250 / portTICK_PERIOD_MS);  // LED on for 250ms
    light.turnOff();
    vTaskDelay(250 / portTICK_PERIOD_MS);  // LED off for 250ms
  }
  vTaskDelete(NULL);  // Deletes the task when `wifiScanning` is false
}

