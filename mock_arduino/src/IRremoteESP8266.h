#ifndef IRREMOTE_H
#define IRREMOTE_H

#include "Arduino.h"

enum decode_type_t {
    UNKNOWN = -1,
    UNUSED = 0,
    NEC = 1,
};

class decode_results {
public:
    decode_type_t decode_type;
    uint64_t value;
    uint32_t address;
    uint16_t command;
    bool repeat;
};

class IRrecv {
public:
    IRrecv(uint16_t recvpin) {}
    void enableIRIn() {}
    bool decode(decode_results *results) {
        static int count = 0;
        if (count++ == 5) {
            results->value = 0xFFA25D;
            results->decode_type = NEC;
            return true;
        }
        return false;
    }
    void resume() {}
};

#endif
