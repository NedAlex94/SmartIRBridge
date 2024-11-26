// wifi_helper.cpp

#include "wifi_helper.h"
#include "light_control.h"
#include "globals.h"

extern LightControl light;          // Reference to the LightControl object
extern volatile bool wifiScanning;  // Reference to the wifiScanning flag


/**
 * FreeRTOS task for scanning Wi-Fi networks.
 * Initiates an LED blink task while it performs a network scan.
 */
void wifiScanTask(void *parameter) {
    Serial.println("Wi-Fi scan started...");

    // Start the LED blinking task
    xTaskCreatePinnedToCore(
        ledBlinkTask,             // Blinking task function
        "LEDBlinkTask",           // Name of the task
        2048,                     // Stack size in bytes
        &light,                   // Task input parameter (pointer to LightControl)
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

void startWiFiScanTask() {
    // Create the Wi-Fi scanning task only if not already scanning
    if (!wifiScanning) {
        wifiScanning = true;
        xTaskCreatePinnedToCore(
            wifiScanTask,           // Task function
            "WiFiScanTask",         // Name of the task
            4096,                   // Stack size in bytes
            NULL,                   // Task input parameter
            1,                      // Priority of the task
            NULL,                   // Task handle not needed
            0                       // Core to run the task
        );
    }
}


/**
 * Scans and prints details of available Wi-Fi networks.
 */
void scanAndPrintWiFiNetworks() {
    WiFi.mode(WIFI_STA); // Ensure the ESP32 is in "station" mode
    Serial.println("Scanning for WiFi networks...");

    // Perform WiFi network scan
    int networkCount = WiFi.scanNetworks();

    // Print the number of networks found
    Serial.print("Number of networks found: ");
    Serial.println(networkCount);

    // Loop through the networks and print their details
    for (int i = 0; i < networkCount; i++) {
        Serial.print("Network ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));         // SSID of the network
        Serial.print(" (Signal strength: ");
        Serial.print(WiFi.RSSI(i));         // Signal strength in dBm
        Serial.println(" dBm)");
    }

    // Clear the scan results
    WiFi.scanDelete();
}


void startAccessPoint() {
    const char* apSSID = "ESP32_Config";       // Access Point SSID
    const char* apPassword = "12345678";       // Access Point temporary password

    Serial.println("Starting Access Point...");
    if (WiFi.softAP(apSSID, apPassword)) {
        Serial.println("Access Point started successfully!");
    } else {
        Serial.println("Failed to start Access Point.");
        return; // Exit if AP fail to start
    }

    Serial.print("SSID: ");
    Serial.println(apSSID);
    Serial.print("Password: ");
    Serial.println(apPassword);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}
