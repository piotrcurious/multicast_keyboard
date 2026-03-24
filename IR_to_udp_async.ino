#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncUDP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncUDP.h>
#endif

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// IR receiver and UDP settings
const uint16_t kRecvPin = 14; // GPIO pin (D5 on ESP8266)
const uint16_t kUdpPort = 2390;
const char* multicast_ip = "224.0.0.1";

IRrecv irrecv(kRecvPin);
decode_results results;
AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  irrecv.enableIRIn();

  if(udp.listenMulticast(IPAddress(224,0,0,1), kUdpPort)) {
    Serial.println("UDP listening on multicast");
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    String command = "IR_CODE_" + String((uint32_t)results.value);

    // Custom mapping for known buttons
    if (results.decode_type == NEC) {
        if (results.value == 0xFFA25D) command = "POWER";
    }

    Serial.print("Sending IR command: ");
    Serial.println(command);

    udp.broadcastTo(command.c_str(), kUdpPort);

    irrecv.resume();
  }
}
