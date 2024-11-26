// wps_button.h

#ifndef WPS_BUTTON_H
#define WPS_BUTTON_H

#include <Arduino.h>

class WPSButton {
  public:
    WPSButton();            // Default constructor
    bool isPressed();       // Check if the button is pressed
    void checkAndPrint();   // Print "Yes" or "No" based on button state
  private:
    bool lastButtonState;   // Stores the last button state
};

#endif
