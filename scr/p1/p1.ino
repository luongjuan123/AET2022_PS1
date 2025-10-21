#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Scanning for Wi-Fi networks...");
  int n = WiFi.scanNetworks();  // Scan nearby networks

  if (n == 0) {
    Serial.println("No networks found. Restarting...");
    delay(2000);
    ESP.restart();
  }

  // Print list of networks
  Serial.println("\nAvailable networks:");
  for (int i = 0; i < n; i++) {
    Serial.print(String(i + 1) + ". ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (signal: ");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
    delay(10);
  }

  // Let user choose network
  Serial.print("\nEnter number of Wi-Fi to connect: ");
  while (!Serial.available());
  int choice = Serial.parseInt();
  Serial.println(choice);

  if (choice < 1 || choice > n) {
    Serial.println("Invalid choice. Restarting...");
    delay(2000);
    ESP.restart();
  }

  String ssid = WiFi.SSID(choice - 1);

  // Get password
  Serial.print("Enter password for ");
  Serial.print(ssid);
  Serial.print(": ");
  String password = "";
  while (password == "") {
    if (Serial.available()) {
      password = Serial.readStringUntil('\n');
      password.trim();
    }
  }

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid.c_str(), password.c_str());

  // Wait for connection
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect. Restarting...");
    delay(2000);
    ESP.restart();
  }
}

void loop() {
  Serial.prinln("Do you want to connect to another wifi ?");
  int option = Serial.parseInt();;

}
