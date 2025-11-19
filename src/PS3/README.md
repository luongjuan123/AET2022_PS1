# ESP32 ESP-NOW Example

This project demonstrates **ESP32 communication using ESP-NOW**.  
It consists of **two sketches**: **Sender** and **Receiver**.

---

## Features
- Send and receive short messages between ESP32 devices without Wi-Fi network
- Display sender MAC address and message on Receiver
- Callback on successful or failed transmission on Sender

---

## 🖥 Receiver

- Listens for incoming ESP-NOW messages
- Prints sender MAC address and message to Serial Monitor

**Key points:**
- Uses `esp_now_register_recv_cb()` to receive data
- No loop processing needed for receiving
- Serial output example:

