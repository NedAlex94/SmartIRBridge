// web_server.cpp

#include "web_server.h"
#include <WiFi.h>
#include <WebServer.h>

// Initialize the web server on port 80
WebServer server(80);



/**
 * Initialize the web server.
 */
void initWebServer() {
    // Define the root page
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/plain", "Hello, this is your ESP32 writing!");
    });

    // Start the server
    server.begin();
    Serial.println("Web server started at http://192.168.4.1");
}

/**
 * Handle client requests.
 */
void handleWebServer() {
    server.handleClient();
}


