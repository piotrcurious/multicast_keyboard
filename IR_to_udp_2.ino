#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// IR receiver and UDP settings
const uint16_t kRecvPin = D5; // GPIO pin for the IR receiver
const uint16_t kUdpPort = 2390; // UDP port to send messages
const char* multicast_ip = "224.0.0.1"; // Multicast IP address

IRrecv irrecv(kRecvPin);
decode_results results;
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  irrecv.enableIRIn(); // Start the receiver
  udp.begin(kUdpPort);
}

void loop() {
  if (irrecv.decode(&results)) {
    // Use this function to get a string representation of the command
    String command = typeToString(results.decode_type, results.command, results.repeat);
    // Send the command via UDP multicast
    udp.beginMulticast(WiFi.localIP(), multicast_ip, kUdpPort);
    udp.write(command.c_str());
    udp.endPacket();
    
    irrecv.resume(); // Receive the next value
  }
}

String typeToString(decode_type_t protocol, uint64_t data, bool repeat) {
  // This function should be modified to match the specific IR remote type and its commands
  // For example, if the remote is NEC type and the button 'Power' is pressed:
  if (protocol == NEC && data == 0x20DF10EF && !repeat) {
    return "Power Button Pressed";
  }
  // Add more cases as needed for other buttons and remote types
  return "Unknown Command";
}
