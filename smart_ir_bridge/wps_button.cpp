// wps_button.cpp

#include "wps_button.h"

const uint16_t WPS_BUTTON_PIN = 16;

WPSButton::WPSButton() {
    pinMode(WPS_BUTTON_PIN, INPUT_PULLUP);
    lastButtonState = !isPressed();
}

bool WPSButton::isPressed() {
    return digitalRead(WPS_BUTTON_PIN) == LOW;
}


/**
 * Checks the button state and prints "Yes" if pressed or "No" if not.
 * This is an intermediate step until the functionality is fully programmed.
 * Ensures the state is printed only when it changes.
 */
void WPSButton::checkAndPrint() {
    bool currentButtonState = isPressed();
    if (currentButtonState != lastButtonState) {
        if (currentButtonState) {
            Serial.println("Yes");
        } else {
            Serial.println("No");
        }
        lastButtonState = currentButtonState;
    }
}
