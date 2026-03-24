#include <PS2KeyAdvanced.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// Initialize PS2 keyboard
PS2KeyAdvanced keyboard;
const int DataPin = 5;
const int IRQpin = 4;

// Network settings
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
IPAddress multicast_ip(224, 0, 0, 1);
const int udp_port = 2390;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Begin listening for UDP multicast packets
  udp.beginMulticast(WiFi.localIP(), multicast_ip, udp_port);

  // Initialize PS2 keyboard
  keyboard.begin(DataPin, IRQpin);
}

void loop() {
  // Check if key pressed
  if (keyboard.available()) {
    // Read the ASCII value of the key
    uint16_t c = keyboard.read();
    
    // Convert the key to a string for UDP transmission
    String message = "KEY_" + String(c);

    // Send the key over UDP multicast
    udp.beginPacket(multicast_ip, udp_port);
    udp.print(message);
    udp.endPacket();
  }
}
