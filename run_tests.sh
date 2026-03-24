#!/bin/bash
set -e

MOCK_DIR="mock_arduino/src"
RUNNER="mock_arduino/src/runner.cpp"
ARDUINO_CPP="mock_arduino/src/Arduino.cpp"

compile_and_run() {
    local ino=$1
    local name=$2
    local platform=$3
    echo "----------------------------------------"
    echo "Testing $name on $platform"
    echo "----------------------------------------"
    cat $RUNNER $ino > tmp_test.cpp
    g++ -I$MOCK_DIR -DARDUINO=100 -D$platform=1 -o tmp_test tmp_test.cpp $ARDUINO_CPP
    ./tmp_test
    rm tmp_test tmp_test.cpp
    echo ""
}

echo "Testing Async versions..."
compile_and_run "IR_to_udp_async.ino" "IR to UDP Async" "ESP32"
compile_and_run "keyboard_to_udp_async.ino" "Keyboard to UDP Async" "ESP32"
compile_and_run "telnet_aggregator_async.ino" "Telnet Aggregator Async" "ESP32"

echo "Testing Synchronous versions..."
compile_and_run "IR_to_udp.ino" "IR to UDP" "ESP8266"
compile_and_run "stub1.ino" "Stub1 (PS2Keyboard)" "ESP32"
compile_and_run "udp_keyboard.ino" "UDP Keyboard (PS2KeyAdvanced)" "ESP32"
compile_and_run "telnet_server.ino" "Telnet Server Relay" "ESP32"

echo "All tests passed successfully!"
