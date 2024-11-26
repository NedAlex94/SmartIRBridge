// web_server.cpp

#include "web_server.h"
#include <WiFi.h>
#include <WebServer.h>

// Initialize the web server on port 80
WebServer server(80);


// Embed the HTML content directly as a string from /templates because I could not be bothered to write it to memory yet.
// You can test this withotu compiling by running the mininum python server instead.
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Config</title>
</head>
<body>
    <h1>ESP32 Config Server</h1>
    <form method="POST" action="/scan">
        <button type="submit">Scan Wi-Fi</button>
    </form>
    <h2>Scan Results:</h2>
    <form method="POST" action="/connect">
        <div>
            <label for="wifi_networks">Select the Wi-Fi you want the ESP32 to connect to:</label>
        </div>
        <select id="wifi_networks" name="ssid" required>
            %SCAN_RESULTS%
        </select>
        <br><br>
        <div>
            <label for="password">Enter Password:</label>
        </div>
        <input type="password" id="password" name="password" required>
        <br><br>
        <button type="submit">Connect</button>
    </form>
</body>
</html>
)rawliteral";

/**
 * Initialize the web server.
 */
void initWebServer() {
    // Define the root page
    server.on("/", HTTP_GET, []() {
        String html = index_html; 
        html.replace("%SCAN_RESULTS%", "<option>Click 'Scan Wi-Fi' to search</option>");
        server.send(200, "text/html", html);
    });

    // Define the scan page. This will be improved in the future becasue it can be clunky.
    server.on("/scan", HTTP_POST, []() {
        String scanResults = scanAndPrintWiFiNetworks(); // Call the helper function in wifi_helper.cpp
        String html = index_html; 
        html.replace("%SCAN_RESULTS%", scanResults);
        server.send(200, "text/html", html);
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


