#include <iostream>
#include "Arduino.h"
#include "AsyncUDP.h"

// Prototypes for the .ino functions
void setup();
void loop();

int main() {
    std::cout << "Starting Mock Arduino Runner..." << std::endl;
    setup();
    for(int i = 0; i < 10; ++i) {
        loop();
    }
    std::cout << "Mock Arduino Runner finished." << std::endl;
    return 0;
}
