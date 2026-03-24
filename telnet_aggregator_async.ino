#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncUDP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncUDP.h>
#endif

#include <WiFiClient.h>

// Credentials for STA (to connect to internet/telnet server)
const char* sta_ssid = "YOUR_STA_SSID";
const char* sta_password = "YOUR_STA_PASSWORD";

// Credentials for AP (to receive multicast from other devices)
const char* ap_ssid = "YOUR_AP_SSID";
const char* ap_password = "YOUR_AP_PASSWORD";

const char* telnet_server = "192.168.1.10"; // Example
const uint16_t telnet_port = 23;
const uint16_t udp_port = 2390;

AsyncUDP udp;
WiFiClient telnetClient;

void connectToWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi");
    WiFi.begin(sta_ssid, sta_password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
  }
}

void connectToTelnetServer() {
  if (!telnetClient.connected()) {
    Serial.println("Connecting to telnet server...");
    if (telnetClient.connect(telnet_server, telnet_port)) {
      Serial.println("Connected to telnet server");
    } else {
      Serial.println("Connection failed");
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);
  connectToWiFi();
  WiFi.softAP(ap_ssid, ap_password);

  if(udp.listenMulticast(IPAddress(224,0,0,1), udp_port)) {
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();

      if (telnetClient.connected()) {
        telnetClient.write(packet.data(), packet.length());
        telnetClient.println(); // Add newline for telnet command
      }
    });
  }
}

void loop() {
  connectToWiFi();
  connectToTelnetServer();

  while (telnetClient.available()) {
    String line = telnetClient.readStringUntil('\n');
    Serial.println("From Telnet: " + line);
  }
  delay(100);
}
