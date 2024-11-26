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
 * Local function for handling Wi-Fi scan results.
 * @param networkCount Number of networks found.
 * @return String containing HTML options for available networks.
 */
static String formatWiFiScanResults(int networkCount) {
    String results = "";
    for (int i = 0; i < networkCount; i++) {
        results += "<option value=\"" + WiFi.SSID(i) + "\">";
        results += WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)";
        results += "</option>";

        // Print to Serial for debugging
        Serial.print("Network ");
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (Signal strength: ");
        Serial.print(WiFi.RSSI(i));
        Serial.println(" dBm)");
    }
    return results;
}

/**
 * Perform a Wi-Fi scan and return results formatted as HTML <option> elements.
 * @return String of HTML options for available networks.
 */
String scanAndPrintWiFiNetworks() {
    Serial.println("Scanning for Wi-Fi networks...");

    // Changed to handle AP and Wi-Fi scanning at the same time
    // WiFi.scanNetworks(show_hidden, scan_duplicates), so those are set to false
    int networkCount = WiFi.scanNetworks(false, false);
    Serial.print("Number of networks found: ");
    Serial.println(networkCount);

    // Format scan results into HTML options
    String scanResults = formatWiFiScanResults(networkCount);

    WiFi.scanDelete(); // Clear scan results
    return scanResults.isEmpty() ? "<option>No networks found</option>" : scanResults;
}




void startAccessPoint() {
    const char* apSSID = "ESP32_Config";       // Access Point SSID
    const char* apPassword = "12345678";       // Access Point temporary password

    Serial.println("Starting Access Point...");

    // Set Wi-Fi mode to AP+STA (Access Point + Station)
    // otherwise the connection to the AP fails on WiFi scan
    WiFi.mode(WIFI_AP_STA);

    if (WiFi.softAP(apSSID, apPassword)) {
        Serial.println("Access Point started successfully!");
    } else {
        Serial.println("Failed to start Access Point.");
        return;
    }

    Serial.print("SSID: ");
    Serial.println(apSSID);
    Serial.print("Password: ");
    Serial.println(apPassword);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
}
