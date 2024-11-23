// light_control.h

#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <Arduino.h>

class LightControl {
  public:
    LightControl(int pin);   // Constructor to initialize the light pin
    void turnOn();           // Function to turn the light on
    void turnOff();          // Function to turn the light off
    void blink(int times);   // Function to blink the light 'times' times
  private:
    int lightPin;            // Pin connected to the light
};

#endif
