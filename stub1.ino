#include <PS2Keyboard.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const int dataPin = 5;
const int irqPin = 4;

// Initialize PS2 keyboard
PS2Keyboard keyboard;

// Initialize UDP
WiFiUDP udp;
IPAddress multicastAddress(224, 0, 0, 1);
unsigned int multicastPort = 2390;

void setup() {
  Serial.begin(115200);
  // Setup WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Setup PS2 keyboard
  keyboard.begin(dataPin, irqPin);

  // Begin UDP multicast
  udp.beginMulticast(WiFi.localIP(), multicastAddress, multicastPort);
}

String convertScancodeToVT100(char scancode) {
  // Simple mapping for demonstration
  if (scancode == 0x1C) return "A"; // Example scancode for 'A'
  return String(scancode);
}

void loop() {
  // Check if data is available from the keyboard
  if (keyboard.available()) {
    // Read scancode
    char scancode = keyboard.readScancode();
    
    // Convert scancode to VT100 sequence
    String vt100Sequence = convertScancodeToVT100(scancode);
    
    // Send VT100 sequence over UDP multicast
    udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
    udp.write(vt100Sequence.c_str());
    udp.endPacket();
  }
}
