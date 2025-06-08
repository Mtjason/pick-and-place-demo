# Pick-and-Place Control Demo: C++ Simulated PLC System

This project demonstrates a simulated **Pick-and-Place automation control system** written in C++, inspired by industrial PLC (Programmable Logic Controller) control logic.

> This simulation is designed as a **preparation project for Cohu software engineer interview**, integrating C++ logic with modular I/O components.

---

## 🔧 Project Structure

📁 project-root/
├── main.cpp # Main control loop
├── actuator.hpp # Actuator module (e.g. simulated arm control)
├── sensor.hpp # Sensor module (e.g. object detection simulation)
├── logger.hpp # Logger utilities
└── .vscode/
├── settings.json # VSCode C++ intellisense configuration
└── tasks.json # Build task for MSYS2 g++

---

## ⚙️ Features

- Modular structure for I/O simulation
- Simulated sensors and actuators
- Lightweight logger for debugging
- MSYS2 g++ compatible
- Suitable for embedded or PLC control concept practice

---

## 🚀 How to Build

Make sure you have `g++` installed (MSYS2 or WSL both fine):

```bash
g++ -std=c++17 main.cpp -o main.exe
