#include <WiFi.h>

const char* ssid = "MyESP32";
const char* password = "Juan123";

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  IPAddress apIP(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, subnet);
  Serial.print("Access Point IP Address: ");
  Serial.println(WiFi.softAPIP());

  Serial.print("Access point named ");
  Serial.print(ssid);
  Serial.println(" is paired to connect");
}

void loop() {
  int numClients = WiFi.softAPgetStationNum();  // Get connected devices number at specific time
  Serial.print("Connected devices: ");
  Serial.println(numClients);
  delay(3000);  
}