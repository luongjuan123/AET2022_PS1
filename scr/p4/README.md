# Problem 4: ESP32 WiFi Client Communication

## Overview
This program connects the ESP32 to a Wi-Fi network and sends data to a remote server using TCP (WiFiClient).  
It repeatedly connects to the server, sends simple messages (`ON` and `OFF`), and then closes the connection.

## Features
- Connects ESP32 to a specified Wi-Fi network  
- Establishes a TCP connection to a server (host and port)  
- Sends alternating messages "ON" and "OFF" every few seconds  
- Prints connection and transmission status via Serial Monitor  


