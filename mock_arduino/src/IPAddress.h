#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <string>
#include <cstdint>
#include <cstdio>

class IPAddress {
    uint8_t _octets[4];
public:
    IPAddress() { _octets[0] = _octets[1] = _octets[2] = _octets[3] = 0; }
    IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet) {
        _octets[0] = first_octet;
        _octets[1] = second_octet;
        _octets[2] = third_octet;
        _octets[3] = fourth_octet;
    }
    IPAddress(const char* s) { _octets[0] = _octets[1] = _octets[2] = _octets[3] = 0; }
    std::string toString() const {
        char buf[16];
        sprintf(buf, "%u.%u.%u.%u", _octets[0], _octets[1], _octets[2], _octets[3]);
        return std::string(buf);
    }
};

#endif
