// wifi_helper.h

#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <WiFi.h>

// Function to perform Wi-Fi scan and print networks
String scanAndPrintWiFiNetworks();

// FreeRTOS task function for Wi-Fi scanning
void wifiScanTask(void *parameter);

// Initiate the Wi-Fi scan task
void startWiFiScanTask();

// Start an access point
void startAccessPoint();

void connectToStoredWiFiOrFallback();


#endif // WIFI_HELPER_H
