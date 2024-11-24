// ir_handler.cpp
#include "ir_handler.h"
#include <IRremote.hpp>

// Define the IR receiver pin
const uint16_t RECV_PIN = 15;

// Initialize the IR receiver
void initIR() {
    // Configure the IR receiver with the RECV_PIN
    IrReceiver.begin(RECV_PIN);
    Serial.println("IR Receiver is initialized. Waiting for signals...");
}

// Handle incoming IR signals
void handleIR() {
    if (IrReceiver.decode()) {
        uint32_t decodedData = IrReceiver.decodedIRData.decodedRawData;

        if (decodedData == 0) {
            Serial.println("Repeat Signal Detected");
        } else {
            Serial.print("Decoded Data: ");
            Serial.println(decodedData, HEX);
        }

        IrReceiver.resume(); // Prepares for the next signal
    }
}
