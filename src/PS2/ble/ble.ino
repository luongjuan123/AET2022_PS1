#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define LED_PIN 2

// UUID tự tạo
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_SENSOR_UUID    "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHAR_LED_UUID       "cd20c738-2c42-4a58-840a-c3b73a1b8e47"

BLECharacteristic *sensorChar;
BLECharacteristic *ledChar;

class LEDCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* characteristic) {
    std::string value = characteristic->getValue();
    if (value == "1") digitalWrite(LED_PIN, HIGH);
    else digitalWrite(LED_PIN, LOW);
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  BLEDevice::init("ESP32_BLE");

  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);

  sensorChar = service->createCharacteristic(
    CHAR_SENSOR_UUID,
    BLECharacteristic::PROPERTY_READ
  );

  ledChar = service->createCharacteristic(
    CHAR_LED_UUID,
    BLECharacteristic::PROPERTY_WRITE
  );
  ledChar->setCallbacks(new LEDCallback());

  service->start();
  BLEDevice::startAdvertising();
}

void loop() {
  int temp = random(20, 40); // dữ liệu cảm biến giả lập
  sensorChar->setValue(temp);
  delay(2000);
}
