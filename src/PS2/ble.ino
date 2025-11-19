#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_UUID           "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *dataChar;

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32_SEND_BLE");
  BLEServer *server = BLEDevice::createServer();
  BLEService *service = server->createService(SERVICE_UUID);

  dataChar = service->createCharacteristic(
    CHAR_UUID,
    BLECharacteristic::PROPERTY_READ
  );

  service->start();
  server->getAdvertising()->start();

  Serial.println("BLE Started – waiting for client...");
}

void loop() {
  int value = random(20, 40);
  dataChar->setValue(value);
  Serial.println("Sent value (READ): " + String(value));
  delay(2000);
}
