#ifndef WIFI_H
#define WIFI_H

#include "Arduino.h"
#include "IPAddress.h"
#include "WiFiClient.h"

enum wl_status_t {
    WL_IDLE_STATUS,
    WL_NO_SSID_AVAIL,
    WL_SCAN_COMPLETED,
    WL_CONNECTED,
    WL_CONNECT_FAILED,
    WL_CONNECTION_LOST,
    WL_DISCONNECTED
};

enum WiFiMode { WIFI_OFF, WIFI_STA, WIFI_AP, WIFI_AP_STA };

class WiFiClass {
public:
    wl_status_t status() { return WL_CONNECTED; }
    void begin(const char* ssid, const char* password) {}
    void mode(WiFiMode m) {}
    bool softAP(const char* ssid, const char* password) { return true; }
    IPAddress localIP() { return IPAddress(192, 168, 1, 100); }
    IPAddress softAPIP() { return IPAddress(192, 168, 4, 1); }
};

extern WiFiClass WiFi;

#endif
