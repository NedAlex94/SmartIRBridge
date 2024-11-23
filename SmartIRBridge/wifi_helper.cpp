// wifi_helper.cpp

#include "wifi_helper.h"

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
