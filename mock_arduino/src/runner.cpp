#include <iostream>
#include "Arduino.h"
#include "AsyncUDP.h"

// Prototypes for the .ino functions
void setup();
void loop();

extern AsyncUDP udp;

int main() {
    std::cout << "Starting Mock Arduino Runner..." << std::endl;
    setup();
    for(int i = 0; i < 10; ++i) {
        if (i == 7) {
            udp.simulatePacket("TEST_MULTICAST");
        }
        loop();
    }
    std::cout << "Mock Arduino Runner finished." << std::endl;
    return 0;
}
