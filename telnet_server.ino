#include <WiFi.h>
#include <WiFiUdp.h>

// Replace with your network credentials for the STA interface
const char* sta_ssid = "YOUR_STA_SSID";
const char* sta_password = "YOUR_STA_PASSWORD";

// AP mode credentials
const char* ap_ssid = "YOUR_AP_SSID";
const char* ap_password = "YOUR_AP_PASSWORD";

// Telnet server details
const char* telnet_server = "server_address";
const uint16_t telnet_port = 23; // Standard telnet port

// UDP multicast details
const uint16_t udp_port = 2390; // UDP port to listen on
const char* multicast_ip = "224.0.0.1"; // Multicast IP address

WiFiServer telnetServer(telnet_port);
WiFiUDP Udp;
WiFiClient telnetClient;

void setup() {
  Serial.begin(115200);

  // Connect to the WiFi network in STA mode
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(sta_ssid, sta_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to STA WiFi network.");

  // Set up the AP network
  WiFi.softAP(ap_ssid, ap_password);

  // Start the telnet server
  telnetServer.begin();
  telnetServer.setNoDelay(true);

  // Join the multicast group on the AP interface
  Udp.beginMulticast(WiFi.softAPIP(), multicast_ip, udp_port);
}

void loop() {
  // Check for new telnet clients
  if (telnetServer.hasClient()) {
    if (!telnetClient || !telnetClient.connected()) {
      if (telnetClient) telnetClient.stop();
      telnetClient = telnetServer.available();
      Serial.println("Telnet client connected");
    }
  }

  // Listen for UDP multicast packets on the AP interface
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    // Relay the received UDP multicast message to the telnet session
    if (telnetClient && telnetClient.connected()) {
      telnetClient.println(incomingPacket);
    }
  }
}
