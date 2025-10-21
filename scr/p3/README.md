# Problem 3: ESP32 Dual Mode Wi-Fi Controller (AP + STA)

## Overview
This program allows the ESP32 to operate in both **Access Point (AP)** and **Station (STA)** modes at the same time.  
Users can start or stop the access point, connect or disconnect from other Wi-Fi networks, and check the current status through the Serial Monitor.

## Features
- Start or stop Access Point mode  
- Connect or disconnect from external Wi-Fi networks  
- Show number of connected devices and current IPs  
- Simple text menu for interactive control via Serial Monitor  


## Usage
1. Upload the code to the ESP32.  
2. Open Serial Monitor at 115200 baud.  
3. Use the menu to control Wi-Fi modes:  
   - `1` Start Access Point  
   - `2` Stop Access Point  
   - `3` Connect to Wi-Fi  
   - `4` Disconnect Wi-Fi  
   - `5` Show current status  
   - `6` Reprint menu  

