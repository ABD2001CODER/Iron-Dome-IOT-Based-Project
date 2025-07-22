# 🛡️ Smart Iron Dome – An IoT-Based Laser Defense System

This project simulates a miniature, cost-effective version of modern missile defense systems using embedded hardware, IoT principles, and real-time radar visualization.

> **Built as a final year project at the University of Sri Jayewardenepura**  
> **Department of Physics | Supervised by Mr. K.S. Mannatunga**

---

## 🚀 Overview

The **Smart Iron Dome** detects and tracks incoming objects using ultrasonic sensors and servo motors. When a target is within range, a laser module simulates interception. A real-time radar interface visualizes the tracking process.

---

## 🎯 Key Features

- 🧭 **Dual Ultrasonic Sensors** – Detect objects within 25 cm range
- 🔁 **Servo Motor Tracking** – Smooth rotation towards detected objects
- 🔫 **Laser Module** – Activates on target detection
- 📊 **Radar UI** – Visualizes angle and distance in real time
- 🔔 **Buzzer and LED** – Provide feedback signals
- 🔌 **Fully embedded** using Arduino and Processing IDE

---

## ⚙️ Hardware Used

- Arduino Uno  
- 2 × HC-SR04 Ultrasonic Sensors  
- 2 × SG90 Servo Motors  
- Laser Module  
- Buzzer  
- LED  
- Breadboard, jumper wires, power supply

---

## 💻 Software & Libraries

- Arduino IDE (Embedded C)  
- Processing IDE (Java-based visualization)  
- Standard Arduino Libraries: `Servo.h`, `NewPing.h` (optional)

---

## 📈 System Workflow

1. Servo motors sweep to scan for objects
2. Ultrasonic sensors detect distance
3. If an object is detected ≤ 25 cm:
   - Servo aligns with object
   - Laser fires
   - Radar UI displays object location
   - LED and buzzer are triggered
4. Object data is visualized on a radar interface

---

## 🧠 Future Enhancements

- 🔄 PID control for smoother servo targeting
- 📷 ESP32-CAM integration for visual detection
- 🌐 IoT dashboard with cloud-based monitoring
- 🧠 AI-based object classification and alerting

---

## 👨‍💻 Author

**Ibralebbe Abdullah**  
`AS2021903` – Department of Physics  
University of Sri Jayewardenepura

---

## 🙏 Acknowledgments

- Mr. K.S. Mannatunga – Supervisor  
- University of Sri Jayewardenepura  
- My peers, mentors, and testers  
