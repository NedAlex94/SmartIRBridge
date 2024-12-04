// SmartIRBridge.ino

// Uses IRremote, an MIT Library for IR signal decoding and handling
// Install it from https://github.com/Arduino-IRremote/Arduino-IRremote
#include "ir_handler.h"    

#include "wps_button.h"    
#include "wifi_helper.h"  
#include "light_control.h" 
#include "globals.h" 
#include "web_server.h"

// Create objects
LightControl light;  
WPSButton wpsButton;


// Flag to indicate Wi-Fi scanning in progress
volatile bool wifiScanning = false; // Definition of wifiScanning

void setup() {
    Serial.begin(115200);  
    Serial.println("Debug: Setup started.");
       
    initIR(); // Initialize IR receiver

    // Handle Wi-Fi connection, if stored, or fallback
    connectToStoredWiFiOrFallback();


    // Initialize the web server
    initWebServer();


    Serial.println("WPS Button initialized. Waiting for input...");

    // Light starts off by default
    light.turnOff();

    Serial.println("Debug: Setup ended.");

}

void loop() {

    handleWebServer();

    // Handle WPS button
    if (wpsButton.isPressed()) {
        if (!wifiScanning) {
            Serial.println("Button pressed! Starting Wi-Fi scan...");
            // Initiate the Wi-Fi scan task via wifi_helper
            startWiFiScanTask();
        }
    }

    // Continue handling other tasks
    handleIR();
}
