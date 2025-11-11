7  void setup() {
8    Serial.begin(115200);
9    delay(500); // Đảm bảo Serial sẵn sàng
10
11   // Cấu hình IP tĩnh cho Access Point
12   IPAddress apIP(192, 168, 4, 1);
13   IPAddress subnet(255, 255, 255, 0);
14
15   // Khởi tạo Access Point
16   WiFi.softAPConfig(apIP, apIP, subnet);
17   WiFi.softAP(SSID, PASSWORD);
18
19   // Hiển thị thông tin
20   Serial.println("\n===== ESP32 Access Point Started =====");
21   Serial.printf("SSID: %s\n", SSID);
22   Serial.printf("Password: %s\n", PASSWORD);
23   Serial.printf("AP IP Address: %s\n", WiFi.softAPIP().toString().c_str());
24   Serial.println("===============================");
25  }
26
27  void loop() {
28    static int lastClientCount = -1; // Lưu số client lần trước
29    int currentClientCount = WiFi.softAPgetStationNum();
30
31   // Chỉ in khi có thay đổi
32   if (currentClientCount != lastClientCount) {
33     Serial.printf("📶 Connected devices: %d\n", currentClientCount);
34     lastClientCount = currentClientCount;
35   }
36
37   delay(2000);
38  }
