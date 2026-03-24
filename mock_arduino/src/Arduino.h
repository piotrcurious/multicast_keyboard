#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <chrono>
#include <thread>
#include <cstdarg>
#include <cstring>
#include <sstream>

class String : public std::string {
public:
    String() : std::string("") {}
    String(const char* s) : std::string(s) {}
    String(const std::string& s) : std::string(s) {}
    String(int v) : std::string(std::to_string(v)) {}
    String(unsigned int v) : std::string(std::to_string(v)) {}
    String(long v) : std::string(std::to_string(v)) {}
    String(unsigned long v) : std::string(std::to_string(v)) {}

    String operator+(const String& other) const { return String((std::string)*this + (std::string)other); }
    String operator+(const char* other) const { return String((std::string)*this + std::string(other)); }
};

inline String operator+(const char* a, const String& b) { return String(std::string(a) + (std::string)b); }

typedef uint8_t byte;

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define D5 5

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);
void analogWrite(uint8_t pin, int val);

void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);
uint32_t millis();
uint32_t micros();

class Serial_ {
public:
    void begin(unsigned long baud) {}
    void print(const char* s) { std::cout << s; }
    void print(String s) { std::cout << (std::string)s; }
    void print(int i) { std::cout << i; }
    void println(const char* s = "") { std::cout << s << std::endl; }
    void println(String s) { std::cout << (std::string)s << std::endl; }
    void println(int i) { std::cout << i << std::endl; }
    void write(const uint8_t* buf, size_t size) { std::cout.write((const char*)buf, size); }
    void write(uint8_t b) { std::cout.write((const char*)&b, 1); }
    void printf(const char* format, ...) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
};

extern Serial_ Serial;

#endif
