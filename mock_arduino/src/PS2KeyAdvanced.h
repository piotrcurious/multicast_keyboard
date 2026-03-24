#ifndef PS2KEYADVANCED_H
#define PS2KEYADVANCED_H

#include "Arduino.h"

class PS2KeyAdvanced {
public:
    void begin(uint8_t dataPin, uint8_t irqPin) {}
    bool available() {
        static int count = 0;
        return (count++ == 5);
    }
    uint16_t read() { return 65; } // 'A'
};

#endif
