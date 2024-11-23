// wps_button.h

#ifndef WPS_BUTTON_H
#define WPS_BUTTON_H

#include <Arduino.h>

class WPSButton {
  public:
    WPSButton(int pin);       // Constructor to initialize the button pin
    bool isPressed();         // Function to check if the button is pressed
    void checkAndPrint();     // Function to print "Yes" or "No"
  private:
    int buttonPin;            // Pin connected to the button
    bool lastButtonState;     // Stores the last state of the button
};

#endif
