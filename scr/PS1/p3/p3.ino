#include <WiFi.h>

const char* ap_ssid = "MyESP32AP";
const char* ap_password = "password123";

bool apEnabled = false;
bool staConnected = false;

void startAP() {
  if (apEnabled) {
    Serial.println("⚠️ Access Point is already running!");
    return;
  }

  WiFi.mode(WIFI_AP_STA); // Keep STA active for scanning later
  IPAddress apIP(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(ap_ssid, ap_password);

  apEnabled = true;

  Serial.println("✅ Access Point started!");
  Serial.print("SSID: "); Serial.println(ap_ssid);
  Serial.print("Password: "); Serial.println(ap_password);
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());
}

void stopAP() {
  if (!apEnabled) {
    Serial.println("⚠️ Access Point is not running!");
    return;
  }

  WiFi.softAPdisconnect(true);
  apEnabled = false;
  Serial.println("🛑 Access Point stopped.");
}

void connectSTA() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("⚠️ Already connected to a Wi-Fi network.");
    return;
  }

  Serial.println("🔍 Scanning for Wi-Fi networks...");
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("❌ No Wi-Fi networks found!");
    return;
  }

  Serial.println("\n📶 Available networks:");
  for (int i = 0; i < n; i++) {
    Serial.printf("%d. %s (Signal: %d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }

  Serial.print("\nEnter number of Wi-Fi to connect: ");
  while (!Serial.available());
  int choice = Serial.parseInt();
  while (Serial.available()) Serial.read(); // Clear buffer

  if (choice < 1 || choice > n) {
    Serial.println("❌ Invalid choice!");
    return;
  }

  String ssid = WiFi.SSID(choice - 1);
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

  Serial.printf("Connecting to %s...\n", ssid.c_str());
  WiFi.begin(ssid.c_str(), password.c_str());

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    staConnected = true;
    Serial.println("✅ Connected to Wi-Fi!");
    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("❌ Failed to connect to Wi-Fi!");
    WiFi.disconnect();
  }
}

void disconnectSTA() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠️ Not connected to any Wi-Fi network.");
    return;
  }

  WiFi.disconnect();
  staConnected = false;
  Serial.println("🛑 Disconnected from Wi-Fi.");
}

void showStatus() {
  Serial.println("\n--- 📋 Current Status ---");

  Serial.print("AP Mode: ");
  Serial.println(apEnabled ? "🟢 ON" : "🔴 OFF");

  if (apEnabled) {
    Serial.print("Connected Devices: ");
    Serial.println(WiFi.softAPgetStationNum());
  }

  Serial.print("STA Mode: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("🟢 Connected");
    Serial.print("SSID: "); Serial.println(WiFi.SSID());
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println("🔴 Not Connected");
  }

  Serial.println("--------------------------\n");
}

void printMenu() {
  Serial.println("\n=== ESP32 WiFi Mode Controller ===");
  Serial.println("1 - Start Access Point");
  Serial.println("2 - Stop Access Point");
  Serial.println("3 - Connect to Wi-Fi");
  Serial.println("4 - Disconnect Wi-Fi");
  Serial.println("5 - Show Status");
  Serial.println("6 - Reprint Menu");
  Serial.println("-------------------------------");
  Serial.print("Enter command: ");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.mode(WIFI_AP_STA);

  printMenu();
}

void loop() {
  if (Serial.available()) {
    int cmd = Serial.parseInt();
    while (Serial.available()) Serial.read(); // Clear extra input

    switch (cmd) {
      case 1: startAP(); break;
      case 2: stopAP(); break;
      case 3: connectSTA(); break;
      case 4: disconnectSTA(); break;
      case 5: showStatus(); break;
      case 6: printMenu(); break;
      default:
        Serial.println("❌ Invalid command. Try 1-6.");
        break;
    }

    Serial.print("\nEnter next command: ");
  }

  delay(100);
}
