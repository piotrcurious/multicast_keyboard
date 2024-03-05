#include <WiFi.h>
#include <AsyncUDP.h>

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

AsyncUDP udp;

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(sta_ssid, sta_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void connectToTelnetServer() {
  if (!telnetClient.connect(telnet_server, telnet_port)) {
    Serial.println("Connection to telnet server failed!");
  } else {
    Serial.println("Connected to telnet server");
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to the WiFi network in STA mode
  WiFi.mode(WIFI_AP_STA);
  connectToWiFi();

  // Set up the AP network
  WiFi.softAP(ap_ssid, ap_password);

  // Connect to the telnet server
  connectToTelnetServer();

  // Join the multicast group on the AP interface
  if(udp.listenMulticast(IPAddress(224, 0, 0, 1), udp_port)) {
    udp.onPacket( {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();

      // Relay the received UDP multicast message to the telnet session
      if (telnetClient.connected()) {
        telnetClient.write(packet.data(), packet.length());
      }
    });
  }
}

void loop() {
  // Reconnect to WiFi if necessary
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  // Reconnect to the telnet server if necessary
  if (!telnetClient.connected()) {
    connectToTelnetServer();
  }

  // Handle telnet client
  if (telnetClient.connected()) {
    while (telnetClient.available()) {
      // Read data from the telnet server and print it
      String line = telnetClient.readStringUntil('\n');
      Serial.println(line);
    }
  }
}
