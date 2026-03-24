#include <WiFi.h>
#include <WiFiUdp.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// IR receiver and UDP settings
const uint16_t kRecvPin = 14; // GPIO pin
const uint16_t kUdpPort = 2390;
const char* multicast_ip = "224.0.0.1";

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
  Serial.println("\nWiFi connected");
  irrecv.enableIRIn();
  Udp.beginMulticast(WiFi.localIP(), IPAddress(224,0,0,1), kUdpPort);
}

void loop() {
  if (irrecv.decode(&results)) {
    String command = typeToString(results.decode_type, results.value, results.repeat);
    Udp.beginPacketMulticast(IPAddress(224,0,0,1), kUdpPort, WiFi.localIP());
    Udp.write(command.c_str());
    Udp.endPacket();
    
    irrecv.resume();
  }
}
