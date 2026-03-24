#ifndef ASYNCUDP_H
#define ASYNCUDP_H

#include "Arduino.h"
#include "IPAddress.h"
#include <functional>
#include <memory>

class AsyncUDPPacket {
    std::shared_ptr<uint8_t[]> _data;
    size_t _len;
public:
    AsyncUDPPacket(const uint8_t* data = nullptr, size_t len = 0) : _len(len) {
        if (data && len) {
            _data.reset(new uint8_t[len]);
            memcpy(_data.get(), data, len);
        }
    }
    IPAddress remoteIP() { return IPAddress(192,168,1,101); }
    uint16_t remotePort() { return 1234; }
    IPAddress localIP() { return IPAddress(192,168,1,100); }
    uint16_t localPort() { return 2390; }
    size_t length() { return _len; }
    uint8_t * data() { return _data.get(); }
    bool isBroadcast() { return false; }
    bool isMulticast() { return true; }
};

class AsyncUDP {
    std::function<void(AsyncUDPPacket& packet)> _handler;
public:
    bool listen(uint16_t port) { return true; }
    bool listenMulticast(IPAddress group, uint16_t port, uint8_t ttl=1) { return true; }
    void onPacket(std::function<void(AsyncUDPPacket& packet)> handler) { _handler = handler; }
    size_t write(const uint8_t *data, size_t len) { return len; }
    size_t print(const char *s) { return strlen(s); }
    size_t print(String s) { return s.length(); }
    size_t broadcastTo(const char* s, uint16_t port) {
        std::cout << "[MOCK BROADCAST TO PORT " << port << "]: " << s << std::endl;
        return strlen(s);
    }
    size_t writeTo(const uint8_t *data, size_t len, IPAddress ip, uint16_t port) { return len; }

    // For simulation
    void simulatePacket(const char* data) {
        if (_handler) {
            AsyncUDPPacket p((const uint8_t*)data, strlen(data));
            _handler(p);
        }
    }
};

#endif
