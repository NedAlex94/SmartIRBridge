// wps_button.cpp

#include "wps_button.h"

WPSButton::WPSButton(int pin) {
  buttonPin = pin;
  pinMode(buttonPin, INPUT_PULLUP);
  lastButtonState = !isPressed();
}

bool WPSButton::isPressed() {
  return digitalRead(buttonPin) == LOW;
}

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
