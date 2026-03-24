#ifndef WIFICLIENT_H
#define WIFICLIENT_H

#include "Arduino.h"
#include "IPAddress.h"

class WiFiClient {
public:
    int connect(const char* host, uint16_t port) { return 1; }
    int connect(IPAddress ip, uint16_t port) { return 1; }
    void stop() {}
    uint8_t connected() { return 1; }
    size_t write(uint8_t b) { return 1; }
    size_t write(const uint8_t *buf, size_t size) { return size; }
    int available() { return 0; }
    int read() { return -1; }
    String readStringUntil(char terminator) { return ""; }
    void println(const char* s = "") {}
    void println(String s) {}
    operator bool() const { return true; }
};

class WiFiServer {
public:
    WiFiServer(uint16_t port) {}
    void begin() {}
    void setNoDelay(bool nodelay) {}
    bool hasClient() { return false; }
    WiFiClient available() { return WiFiClient(); }
};

#endif
