#include <WiFi.h>

// ---- WiFi STA (WiFi nhà bạn) ----
const char* STA_SSID = "VJU Student";
const char* STA_PASS = "studentVJU@2022";

// ---- WiFi AP (WiFi ESP32 phát ra) ----
const char* AP_SSID = "ESP3afafaf2";
const char* AP_PASS = "juan12345678";

void setup() {
  Serial.begin(115200);
  delay(500);

  // --- Bật chế độ Dual Mode: STA + AP ---
  WiFi.mode(WIFI_AP_STA);

  // ===== KẾT NỐI TỚI ROUTER (STA) =====
  Serial.printf("Connecting to WiFi: %s...\n", STA_SSID);
  WiFi.begin(STA_SSID, STA_PASS);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to home WiFi!");
    Serial.print("STA IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to home WiFi!");
  }

  // ===== KHỞI TẠO AP =====
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println("AP Started!");
  Serial.print("AP SSID: ");
  Serial.println(AP_SSID);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  static int last = -1;
  int devices = WiFi.softAPgetStationNum();

  if (devices != last) {
    Serial.printf("📶 Devices connected to ESP32 AP: %d\n", devices);
    last = devices;
  }

  delay(2000);
}
