#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// IR receiver and UDP settings
const uint16_t kRecvPin = D5; // GPIO pin to receive IR data
const uint16_t kUdpPort = 2390; // UDP port to send data
const char* multicast_ip = "224.0.0.1"; // Multicast IP address

IRrecv irrecv(kRecvPin);
decode_results results;
WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  irrecv.enableIRIn(); // Start the receiver
  Udp.beginMulticast(WiFi.localIP(), multicast_ip, kUdpPort);
}

void loop() {
  if (irrecv.decode(&results)) {
    // Use a switch/case to decode and react to the buttons pressed
    // For example, assuming NEC encoding:
    switch (results.value) {
      case 0xFFA25D: // Button "power"
        Udp.beginPacketMulticast(multicast_ip, kUdpPort, WiFi.localIP());
        Udp.write("POWER_BUTTON_PRESSED");
        Udp.endPacket();
        break;
      // Add more cases for other buttons
    }
    irrecv.resume(); // Receive the next value
  }
}
