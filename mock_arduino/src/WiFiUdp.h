#ifndef WIFIUDP_H
#define WIFIUDP_H

#include "Arduino.h"
#include "IPAddress.h"

class WiFiUDP {
public:
    uint8_t begin(uint16_t port) { return 1; }
    uint8_t beginMulticast(IPAddress interfaceAddr, IPAddress multicastAddr, uint16_t port) { return 1; }
    int beginPacket(IPAddress ip, uint16_t port) { return 1; }
    int beginPacketMulticast(IPAddress multicastAddress, uint16_t port, IPAddress interfaceAddress, int ttl = 1) { return 1; }
    int endPacket() { return 1; }
    size_t write(uint8_t byte) { return 1; }
    size_t write(const uint8_t *buffer, size_t size) { return size; }
    size_t write(const char *str) { return strlen(str); }
    int parsePacket() { return 0; }
    int available() { return 0; }
    int read() { return -1; }
    int read(char* buffer, size_t len) { return 0; }
};

#endif
