# ESP32 BLE UART Example

Simple ESP32 BLE example to send/receive data via BLE.

## Features
- Advertise as BLE device: `ESP32-gggkBLE`
- Notify characteristic: ESP32 → Phone
- Write characteristic: Phone → ESP32
- Serial input → BLE, BLE input → Serial

## BLE Info

| Type | UUID | Direction |
|------|------|-----------|
| Service | 6E400001-B5A3-F393-E0A9-E50E24DCCA9E | — |
| Notify | 6E400003-B5A3-F393-E0A9-E50E24DCCA9E | ESP32 → Phone |
| Write | 6E400002-B5A3-F393-E0A9-E50E24DCCA9E | Phone → ESP32 |

## Usage
1. Connect via nRF Connect or LightBlue
2. Enable notifications on Notify characteristic
3. Send text to Write characteristic
4. Check Serial Monitor for messages

## Notes
- Sends `"Hello from ESP32"` every 2s if no Serial input
- BLE messages received from phone are printed to Serial
