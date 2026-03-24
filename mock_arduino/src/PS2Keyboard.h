#ifndef PS2KEYBOARD_H
#define PS2KEYBOARD_H

#include "Arduino.h"

class PS2Keyboard {
public:
    void begin(uint8_t dataPin, uint8_t irqPin) {}
    bool available() { return false; }
    char read() { return 0; }
    char readScancode() { return 0; }
};

#endif
