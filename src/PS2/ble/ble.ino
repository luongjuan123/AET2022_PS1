#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;

bool deviceConnected = false;

#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" 
#define CHARACTERISTIC_UUID "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" // notify
#define WRITE_UUID          "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // write

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

class WriteCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();
    if (rxValue.length() > 0) {
      Serial.print("Received from phone: ");
      Serial.println(rxValue.c_str());
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32-gggkBLE");   // ↔️ Tên BLE (giống SSID)
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Notify characteristic (ESP32 → Phone)
  pCharacteristic = pService->createCharacteristic(
                     CHARACTERISTIC_UUID,
                     BLECharacteristic::PROPERTY_NOTIFY
                   );
  pCharacteristic->addDescriptor(new BLE2902());

  // Write characteristic (Phone → ESP32)
  BLECharacteristic *pWrite = pService->createCharacteristic(
                                WRITE_UUID,
                                BLECharacteristic::PROPERTY_WRITE
                              );
  pWrite->setCallbacks(new WriteCallback());

  pService->start();

  // Bắt đầu quảng bá BLE
  pServer->getAdvertising()->start();
  Serial.println("BLE started, waiting for connection...");
}

void loop() {
  if (deviceConnected) {

    String msg = "";

    // Read serial input (non-blocking)
    if (Serial.available()) {
      msg = Serial.readStringUntil('\n');   // Read line
    } else {
      msg = "Hello from ESP32";             // Default message
    }

    // Send via BLE
    pCharacteristic->setValue(msg.c_str());
    pCharacteristic->notify();

    Serial.println("Sent: " + msg);

    delay(2000);
  }
}

