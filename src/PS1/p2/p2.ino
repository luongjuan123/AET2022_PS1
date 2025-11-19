#include <WiFi.h>

// Khai báo SSID và Password
const char* SSID = "ESP3";
const char* PASSWORD = "juan123";

void setup() {
  Serial.begin(115200);
  delay(500); // Đợi Serial sẵn sàng

  // --- Cấu hình IP tĩnh cho Access Point ---
  const IPAddress apIP(192, 168, 4, 1);
  const IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(SSID, PASSWORD);

  // --- In thông tin AP ---
  Serial.println("\n===== ESP32 Access Point Started =====");
  Serial.printf("SSID: %s\n", SSID);
  Serial.printf("Password: %s\n", PASSWORD);
  Serial.printf("AP IP Address: %s\n", WiFi.softAPIP().toString().c_str());
  Serial.println("======================================");
}

void loop() {
  static int lastClientCount = -1;
  const int currentClientCount = WiFi.softAPgetStationNum();

  // Chỉ in khi số lượng thiết bị thay đổi
  if (currentClientCount != lastClientCount) {
    Serial.printf("📶 Connected devices: %d\n", currentClientCount);
    lastClientCount = currentClientCount;
  }

  delay(2000);
}
