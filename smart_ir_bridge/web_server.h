//web_server.h

#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>

// Function to perform Wi-Fi scan and return results as an HTML string
String scanAndPrintWiFiNetworks();

// Initialize the web server
void initWebServer();

// Handle incoming web server requests
void handleWebServer();

#endif // WEB_SERVER_H
