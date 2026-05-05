# 🏠 Automatic Smart Roof Project

An Arduino-based automatic retractable roof system that opens and closes based on weather conditions.

---

## 📋 Overview

This project creates a **smart roof system** that automatically:
- ✅ **Closes** when rain is detected
- ✅ **Closes** at night/dark conditions  
- ✅ **Opens** during sunny weather
- ✅ Shows status via LED indicators

**Use Cases:** Drying clothes, protecting plants, greenhouse automation

---

## 🔧 Components Required

| # | Component | Qty | Purpose |
|---|-----------|-----|---------|
| 1 | Arduino Uno/Nano | 1 | Main microcontroller |
| 2 | Rain Sensor Module | 1 | Detects water/rain |
| 3 | LDR (Photoresistor) | 1 | Detects light level |
| 4 | 10K Ohm Resistor | 1 | For LDR |
| 5 | Servo Motor (SG90) | 1 | Moves the roof |
| 6 | LED Green | 1 | Roof open indicator |
| 7 | LED Red | 1 | Roof closed indicator |
| 8 | LED Yellow | 1 | Roof moving indicator |
| 9 | 220 Ohm Resistors | 3 | For LEDs |
| 10 | Breadboard | 1 | Connections |
| 11 | Jumper Wires | ~20 | Wiring |
| 12 | USB Cable Type-B | 1 | Programming |

---

## 🔌 Wiring Diagram

```
ARDUINO PIN     COMPONENT
-----------     ---------
A0          →   Rain Sensor (AO pin)
A1          →   LDR (with 10K to GND)
D2          →   Green LED → 220Ω → GND
D3          →   Red LED → 220Ω → GND
D4          →   Yellow LED → 220Ω → GND
D9          →   Servo Signal (Orange wire)
5V          →   Rain Sensor VCC, Servo VCC, LDR
GND         →   All grounds
```

### LDR Wiring:
```
    5V
     │
   [LDR]
     │
     ├──→ A1 (Arduino)
     │
   [10KΩ]
     │
    GND
```

---

## ⚙️ How It Works

| Condition | Rain Sensor | Light | Roof |
|-----------|-------------|-------|------|
| Raining | WET (< 500) | Any | 🔴 CLOSED |
| Dark/Night | DRY | LOW (< 300) | 🔴 CLOSED |
| Sunny Day | DRY | HIGH | 🟢 OPEN |

---

## 📥 Installation

1. Install **Arduino IDE** from https://www.arduino.cc/en/software
2. Connect Arduino via USB
3. Open `smart_roof/smart_roof.ino`
4. Select Board: `Tools → Board → Arduino Uno`
5. Select Port: `Tools → Port → COM#`
6. Click **Upload** (→ arrow button)

---

## 🔧 Calibration

Adjust these values in the code based on your sensors:

```cpp
const int RAIN_THRESHOLD = 500;    // Lower = more sensitive
const int LIGHT_THRESHOLD = 300;   // Lower = darker trigger
```

---

## 📁 Project Files

```
automatic_smart_roof/
├── smart_roof/
│   └── smart_roof.ino      ← Main code (Servo Motor)
├── smart_roof_dc_motor.ino ← Alternative (DC Motor + L298N)
├── README.md               ← This file
└── parts_list.txt          ← Shopping list
```

---

## 🎥 Reference

Based on: [Automatic Smart Roof - YouTube](https://www.youtube.com/watch?v=tZi2Qs9BlWw)
