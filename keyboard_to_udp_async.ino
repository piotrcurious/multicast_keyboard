#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncUDP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncUDP.h>
#endif

#include <PS2KeyAdvanced.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int DataPin = 5;
const int IRQpin = 4;
const uint16_t kUdpPort = 2390;
const char* multicast_ip = "224.0.0.1";

PS2KeyAdvanced keyboard;
AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  keyboard.begin(DataPin, IRQpin);

  if(udp.listenMulticast(IPAddress(224,0,0,1), kUdpPort)) {
    Serial.println("UDP listening on multicast");
  }
}

void loop() {
  if (keyboard.available()) {
    uint16_t c = keyboard.read();
    if (c > 0) {
        String msg = "KEY_" + String(c);
        Serial.print("Sending Key: ");
        Serial.println(msg);
        udp.broadcastTo(msg.c_str(), kUdpPort);
    }
  }
}
