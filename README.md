# 🌡️ IoT Temperature Monitoring System

## 📋 Overview
This project implements a real-time temperature monitoring system using an ESP32 microcontroller, DHT22 sensor, and ThingSpeak cloud platform. The system continuously monitors ambient temperature, provides visual alerts (Red/Green LEDs), and sends data to the cloud for remote monitoring.

## 🎯 Aim
To design and simulate a real-time temperature monitoring system that displays temperature readings and generates warning messages when the temperature exceeds a predefined limit of 30°C.

## 📝 Problem Statement
Design and simulate a real-time clock and temperature monitoring system. This system will monitor the temperature and display a warning message when the temperature exceeds a predefined limit.

## 🔧 Components Used

### Hardware (Simulated in Wokwi)
| Component | Purpose |
|-----------|---------|
| ESP32 DevKit V1 | Main microcontroller with built-in WiFi |
| DHT22 Sensor | Measures temperature and humidity |
| Green LED | Normal status indicator |
| Red LED | Alarm indicator |
| 220Ω Resistor (x2) | Current limiting for LEDs |

### Software & Cloud
- **Wokwi** - Online Simulation Platform
- **Arduino C++** - Programming Language
- **ThingSpeak** - Cloud Platform for Data Visualization

## 📊 System Architecture

## ⚙️ Pin Configuration

| Component | ESP32 Pin |
|-----------|-----------|
| DHT22 DATA | GPIO 15 |
| DHT22 VCC | 3.3V |
| DHT22 GND | GND |
| Red LED | GPIO 13 |
| Green LED | GPIO 12 |

## 📈 Features

| Feature | Status |
|---------|--------|
| Real-time Temperature Monitoring | ✅ |
| Humidity Monitoring | ✅ |
| Visual LED Alerts | ✅ |
| ThingSpeak Cloud Integration | ✅ |
| Remote Data Visualization | ✅ |
| Threshold-based Alarms (30°C) | ✅ |

## 🚀 How to Run

### Prerequisites
1. Create a ThingSpeak account at [thingspeak.com](https://thingspeak.com)
2. Create a channel with 3 fields:
   - Field 1: Temperature (°C)
   - Field 2: Humidity (%)
   - Field 3: Alert Status (1/0)
3. Copy your Write API Key

### Steps
1. Open [Wokwi.com](https://wokwi.com)
2. Create a new ESP32 project
3. Copy `diagram.json` and `sketch.ino` into Wokwi
4. Replace `"YOUR_WRITE_API_KEY_HERE"` with your actual ThingSpeak API key
5. Install required libraries in Wokwi:
   - `DHT sensor library` by Adafruit
   - `ThingSpeak` by MathWorks
6. Start simulation
7. Open Serial Monitor to view readings
8. Click on DHT22 and adjust temperature slider to test the alarm

## 📊 Expected Output

### Serial Monitor - Normal State

### Serial Monitor - Alarm State

### LED Behavior
| Temperature | Red LED | Green LED |
|-------------|---------|-----------|
| ≤ 30°C | OFF | ON 🟢 |
| > 30°C | ON 🔴 | OFF |

## ☁️ ThingSpeak Dashboard
The system sends the following data:
- **Field 1:** Temperature (°C)
- **Field 2:** Humidity (%)
- **Field 3:** Alert Status (1 = Alarm, 0 = Normal)

## 📸 Screenshots

### Wokwi Circuit Diagram
*Add your screenshot here*

<img width="965" height="758" alt="image" src="https://github.com/user-attachments/assets/7cb2df14-564d-446b-a737-9899391b1261" />


## 🎯 Results
- ✅ Real-time temperature and humidity monitoring
- ✅ Visual alerts via LEDs
- ✅ Data successfully sent to ThingSpeak (HTTP 200)
- ✅ Remote monitoring via ThingSpeak dashboard

## 🔮 Future Enhancements
- Add buzzer for audible alerts
- Send email/SMS notifications
- Add LCD display for local readings
- Multiple sensor integration
- MQTT protocol implementation

## 📚 References
1. Espressif Systems. (2024). ESP32 Technical Reference Manual.
2. Adafruit Industries. (2024). DHT22 Humidity and Temperature Sensor Documentation.
3. MathWorks. (2024). ThingSpeak IoT Platform Documentation.
4. Wokwi Documentation. (2024). ESP32 Simulator Guide.

## 👨‍💻 Author
**Anushka Dubey**

## 📅 Date
2024

## 📄 License
This project is for educational purposes.

## 🙏 Acknowledgments
- Wokwi Team for the simulation platform
- ThingSpeak (MathWorks) for cloud services
- Cisco NetAcad for IoT learning resources
  
