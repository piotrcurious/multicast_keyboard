#include "WiFi.h"
#include "AsyncUDP.h"

// Implementations for Arduino.h
#include <cstdarg>
#include <cstdio>
#include <chrono>

Serial_ Serial;

void pinMode(uint8_t pin, uint8_t mode) {}
void digitalWrite(uint8_t pin, uint8_t val) {}
int digitalRead(uint8_t pin) { return LOW; }
int analogRead(uint8_t pin) { return 0; }
void analogWrite(uint8_t pin, int val) {}

void delay(uint32_t ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void delayMicroseconds(uint32_t us) {
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}

uint32_t millis() {
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
}

uint32_t micros() {
    static auto start = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();
}

WiFiClass WiFi;
