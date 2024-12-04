// wifi_credentials_storer.cpp

#include "wifi_credentials_storer.h"
#include <Preferences.h>

Preferences preferences;

void saveWiFiCredentials(const String& ssid, const String& password) {
    preferences.begin("wifi", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.end();
}

void loadWiFiCredentials(String& ssid, String& password) {
    preferences.begin("wifi", true);
    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");
    preferences.end();
}

bool areWiFiCredentialsStored() {
    preferences.begin("wifi", true); // Read-only mode
    String ssid = preferences.getString("ssid", "");
    String password = preferences.getString("password", "");
    preferences.end();
    return !ssid.isEmpty() && !password.isEmpty();
}
