# 💡 Smart Lighting System with Automated Cutoff

![Status](https://img.shields.io/badge/Status-Completed-success)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![IoT](https://img.shields.io/badge/Cloud-Blynk_2.0-green)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)

## 📖 Overview
The **Smart Lighting System** is an IoT-based solution designed to maximize energy efficiency in smart homes and workplaces. It addresses the problem of electricity wastage by automating lighting based on real-time environmental data.

The system operates on a dual-mode logic:
1.  **Automatic Mode:** Uses **PIR Motion Sensors** and **LDR (Light Dependent Resistors)** to turn lights ON only when human presence is detected *and* the room is dark.
2.  **Manual Mode:** Allows the user to override automation and control lights remotely via the **Blynk IoT Mobile App**.

## 🛠️ Tech Stack
### Hardware
* **Microcontroller:** ESP32 (Wi-Fi enabled)
* **Sensors:** HC-SR501 PIR Motion Sensor
    * LDR (Light Dependent Resistor)
* **Actuators:** LED (Simulating Room Light)

### Software & Cloud
* **Embedded C/C++** (Arduino IDE)
* **Blynk IoT 2.0 Cloud** (for Dashboard & Mobile Interface)

## ✨ Key Features
* **Smart Energy Conservation:** Auto-cutoff turns the light OFF after 10 seconds of inactivity.
* **Environmental Awareness:** The light only triggers if the LDR detects low ambient light (< 1000 threshold).
* **Remote Monitoring:** Real-time LDR sensor data is visualized on the Blynk App Gauge.
* **Fault Tolerance:** Includes auto-reconnect logic to handle Wi-Fi or Server disconnections without manual reset.

## 📸 Architecture & Demo

### Circuit Diagram
<img width="607" height="458" alt="circuit" src="https://github.com/user-attachments/assets/d00807ae-cb2d-4e10-9f87-0fee52b2c510" />


### Blynk Dashboard
<img width="341" height="421" alt="BlynkIot" src="https://github.com/user-attachments/assets/9e9c6819-a2cf-445e-95c9-abe2aab5b3c2" />


## 🚀 How It Works (Logic Flow)
The system runs a continuous loop checking two main conditions:
1.  **Is it Dark?** (LDR Value check)
2.  **Is there Motion?** (PIR State check)

```cpp
// Logic Snippet
if (pirState == HIGH && ldrValue < lightThreshold) {
    turnLightON();
    startTimer();
} else if (timeSinceLastMotion > 10000) {
    turnLightOFF();
}
```

## 👥 Contributors
This project was developed by:
* **Krish Korat** 
* **Komal Kumar** 
* **Kavya Raj** 
* **Darp Lalani** 

**Guided By:**
* **Dr. Sudipta Banerjee**

*Department of Electronics & Telecommunication, Symbiosis Institute of Technology, Pune.*
