// web_server.cpp

#include "web_server.h"
#include <WiFi.h>
#include <WebServer.h>
#include "wifi_credentials_storer.h"
#include "index_html.h"

// Initialize the web server on port 80
WebServer server(80);

/**
 * Initialize the web server.
 */
void initWebServer() {
    // Define the root page
    server.on("/", HTTP_GET, []() {
        String html = index_html;
        String content = step1_content;
        
        // Determine Wi-Fi connection status and display message
        String connectionStatus;
        if (WiFi.isConnected()) {
            connectionStatus = "Connected to: " + WiFi.SSID() + "<br>IP Address: " + WiFi.localIP().toString();
        } else {
            connectionStatus = "Not connected to any Wi-Fi network.";
        }

        content.replace("%CONNECTION_STATUS%", connectionStatus);
        content.replace("%DISPLAY%", "none"); // No scan results available yet
        content.replace("%OPTIONS%", "");     // Empty options initially
        html.replace("%CONTENT%", content);
        server.send(200, "text/html", html);
    });

    // Define the scan page. This will be improved in the future because it can be clunky.
    server.on("/scan", HTTP_POST, []() {
        String scanResults = scanAndPrintWiFiNetworks(); // Call the helper function in wifi_helper.cpp
        String html = index_html; 
        String content = step1_content;

        // Determine Wi-Fi connection status and display message
        String connectionStatus;
        if (WiFi.isConnected()) {
            connectionStatus = "Connected to: " + WiFi.SSID() + "<br>IP Address: " + WiFi.localIP().toString();
        } else {
            connectionStatus = "Not connected to any Wi-Fi network.";
        }

        content.replace("%CONNECTION_STATUS%", connectionStatus);
        content.replace("%DISPLAY%", "block"); // Show scan results section
        content.replace("%OPTIONS%", scanResults);
        html.replace("%CONTENT%", content);
        server.send(200, "text/html", html);
    });

    // Define the connect page
    server.on("/connect", HTTP_POST, []() {
        String ssid = server.arg("ssid");
        String password = server.arg("password");

        WiFi.begin(ssid.c_str(), password.c_str());

        int timeout = 20;
        while (WiFi.status() != WL_CONNECTED && timeout > 0) {
            delay(500);
            Serial.print(".");
            timeout--;
        }

        if (WiFi.status() == WL_CONNECTED) {
            saveWiFiCredentials(ssid, password); // Save credentials
            Serial.println("\nWi-Fi connected successfully!");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());

            // Disable the Access Point and switch to station mode to improve UX and
            // avoid confusing users (even though the user here is just me.) After all
            // if connection successful, no need for the AP anymore. Though we should
            // include a reset option or a fallback if the stored WiFi is not found in X time
            WiFi.softAPdisconnect(true); // Turn off the Access Point
            WiFi.mode(WIFI_STA);         // Switch to station mode only

            String html = index_html;
            String content = step1_content;

            // Update connection status
            String connectionStatus = "Connected to: " + WiFi.SSID() + "<br>IP Address: " + WiFi.localIP().toString();
            content.replace("%CONNECTION_STATUS%", connectionStatus);
            content.replace("%DISPLAY%", "none");
            content.replace("%OPTIONS%", "");
            html.replace("%CONTENT%", content);
            server.send(200, "text/html", html);

        } else {
            Serial.println("\nFailed to connect to Wi-Fi.");
            server.send(500, "text/plain", "Failed to connect to Wi-Fi. Please try again.");
        }
    });

    // Define the MQTT configuration page
    server.on("/mqtt", HTTP_GET, []() {
        String html = index_html;
        // Insert the content for Step 2 (MQTT configuration)
        html.replace("%CONTENT%", step2_content);
        server.send(200, "text/html", html);
    });

    // Start the server
    server.begin();
    Serial.println("Web server initialized");
}

/**
 * Handle client requests.
 */
void handleWebServer() {
    server.handleClient();
}
