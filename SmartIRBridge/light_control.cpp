// light_control.h

#include "light_control.h"

LightControl::LightControl(int pin) {
  lightPin = pin;
  pinMode(lightPin, OUTPUT);  // Set the light pin as an output
  digitalWrite(lightPin, LOW);  // Ensure the light is off by default

}

void LightControl::turnOn() {
  digitalWrite(lightPin, HIGH);  // Set the pin HIGH to turn the light on
}

void LightControl::turnOff() {
  digitalWrite(lightPin, LOW);   // Set the pin LOW to turn the light off
}

void LightControl::blink(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(lightPin, HIGH);  // Turn the light on
    delay(500);                    // Wait for 500ms
    digitalWrite(lightPin, LOW);   // Turn the light off
    delay(500);                    // Wait for 500ms
  }
}
