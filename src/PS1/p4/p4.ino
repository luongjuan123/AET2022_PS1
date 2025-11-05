#include <WiFi.h>

const char* ssid = "CH-P310";
const char* password = "Comehome02";
const char* host = "192.168.1.104";  /
const int port = 80;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  WiFiClient client;
  if (client.connect(host, port)) {
    Serial.println("Connected to server");
    
    client.println("ON");
    Serial.println("Sent: ON");
    delay(2000);

    client.println("OFF");
    Serial.println("Sent: OFF");
    delay(2000);

    client.stop();
  } else {
    Serial.println("Connection failed");
  }
  delay(3000);
}
