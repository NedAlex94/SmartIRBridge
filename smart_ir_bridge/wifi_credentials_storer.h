// wifi_credentials_storer.h

#ifndef WIFI_CREDENTIALS_STORER_H
#define WIFI_CREDENTIALS_STORER_H

#include <Arduino.h>

void saveWiFiCredentials(const String& ssid, const String& password);
void loadWiFiCredentials(String& ssid, String& password);
bool areWiFiCredentialsStored(); 

#endif // WIFI_CREDENTIALS_STORER_H
