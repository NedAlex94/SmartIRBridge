// light_control.h

#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <Arduino.h>

class LightControl {
public:
    LightControl();   // Constructor to initialize the light pin      
    void turnOn();    // Function to turn the light on
    void turnOff();   // Function to turn the light off
    void blink(int times); // Function to blink the light 'times' times
};

void ledBlinkTask(void *parameter);

#endif // LIGHT_CONTROL_H
