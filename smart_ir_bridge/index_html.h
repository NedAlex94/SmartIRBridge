// index_html.h

#ifndef INDEX_HTML_H
#define INDEX_HTML_H


// Embed the HTML content directly as a string from /templates because I could not be bothered to write it to memory yet.
// You can test this withotu compiling by running the mininum python server instead.
// index_html.h

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Config</title>
</head>
<body>
    <h1>ESP32 Config Server</h1>

    <!-- Tabs for navigation -->
    <div>
        <a href="/">Step 1: Wi-Fi Connection</a> |
        <a href="/mqtt">Step 2: MQTT Server Connection</a>
    </div>

    <!-- Content Placeholder -->
    %CONTENT%

</body>
</html>
)rawliteral";

const char step1_content[] PROGMEM = R"rawliteral(
<h2>Step 1: WiFi Connection</h2>

<form method="POST" action="/scan">
    <button type="submit">Scan Wi-Fi</button>
</form>

<!-- Scan Wi-Fi results section -->
<div id="scan-results-section" style="display: %DISPLAY%;">
    <h2>Scan Results:</h2>
    <form method="POST" action="/connect">
        <div>
            <label for="wifi_networks">Select the Wi-Fi you want the ESP32 to connect to:</label>
        </div>
        <select id="wifi_networks" name="ssid" required>
            %OPTIONS%
        </select>
        <br><br>
        <div>
            <label for="password">Enter Password:</label>
        </div>
        <input type="password" id="password" name="password" required>
        <br><br>
        <button type="submit">Connect</button>
    </form>
</div>
)rawliteral";

const char step2_content[] PROGMEM = R"rawliteral(
<h2>Step 2: MQTT Server Connection</h2>
<!-- MQTT configuration form -->
<form method="POST" action="/mqtt-save">
    <label for="mqtt_broker">Broker Address:</label>
    <input type="text" id="mqtt_broker" name="mqtt_broker" required>
    <br><br>
    <label for="mqtt_port">Port:</label>
    <input type="number" id="mqtt_port" name="mqtt_port" value="1883" required>
    <br><br>
    <label for="mqtt_username">Username:</label>
    <input type="text" id="mqtt_username" name="mqtt_username">
    <br><br>
    <label for="mqtt_password">Password:</label>
    <input type="password" id="mqtt_password" name="mqtt_password">
    <br><br>
    <button type="submit">Save MQTT Settings</button>
</form>
)rawliteral";

#endif // INDEX_HTML_H

