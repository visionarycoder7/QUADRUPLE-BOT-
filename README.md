# 🐾 8-DOF Quadruped Robot

An **8-DOF quadruped robot** developed as part of the **WTL & MeitY Certification-Based Industrial Training Programme** by **Group-E, Department of Electronics & Communication Engineering, Cooch Behar Government Engineering College (CGEC)**.

The project combines **embedded systems, servo control, mechanical CAD design, 3D printing, and robotics** to develop a four-legged robotic platform capable of stable standing and serving as a foundation for walking gait and autonomous navigation.

---

## 📌 Project Overview

A quadruped robot is a four-legged mobile robot designed to achieve locomotion using coordinated leg movements.

In this project, each leg contains:

- **1 Hip joint**
- **1 Knee joint**

This provides:

> **4 legs × 2 DOF = 8 Degrees of Freedom**

The robot uses an **ESP32** as the central controller and a **PCA9685 16-channel PWM servo driver** to control eight SG90S metal-gear micro servos.

The mechanical structure was designed using **FreeCAD** and fabricated using **FDM 3D printing**.

---

## 🎯 Objectives

The major objectives of the project are:

- Design and develop a functional **8-DOF quadruped robot**
- Implement servo control using an **ESP32**
- Control multiple servos using a **PCA9685 PWM driver**
- Design the robot chassis using **FreeCAD**
- Fabricate mechanical components using **FDM 3D printing**
- Develop and test the electronics and servo-control system
- Implement a stable standing pose
- Establish a foundation for future walking and turning gaits
- Gain practical experience in:
  - Embedded Systems
  - Robotics
  - Electronics
  - Mechanical Design
  - CAD Modelling
  - Additive Manufacturing

---

## 🧠 System Architecture

```text
                 ┌─────────────────────┐
                 │       ESP32          │
                 │  Central Controller  │
                 └──────────┬──────────┘
                            │
                     I2C Communication
                     SDA → GPIO 21
                     SCL → GPIO 22
                            │
                            ▼
                 ┌─────────────────────┐
                 │      PCA9685        │
                 │  16-Channel PWM     │
                 │    Servo Driver     │
                 └──────────┬──────────┘
                            │
              ┌─────────────┼─────────────┐
              │             │             │
              ▼             ▼             ▼
          Hip Servos    Knee Servos    Other Channels
              │             │
              └─────────────┼─────────────┘
                            ▼
                   8 × SG90S Servos
                            │
                            ▼
                    Quadruped Robot
```

### Power Architecture

The ESP32 communicates with the PCA9685 through I2C, while the servo power rail is supplied separately.

```text
External 5V Supply
       │
       ▼
PCA9685 V+ ───────► Servo Power Rail
       │
       ├── CH0 → Front Left Hip
       ├── CH1 → Front Left Knee
       ├── CH2 → Front Right Hip
       ├── CH3 → Front Right Knee
       ├── CH4 → Rear Left Hip
       ├── CH5 → Rear Left Knee
       ├── CH6 → Rear Right Hip
       └── CH7 → Rear Right Knee
```

> ⚠️ **Important:** The PCA9685 `V+` terminal requires an external 5V supply for powering the servos. The PCA9685 `VCC` connection to the ESP32 is for logic power and is not the servo power rail.

---

## 🔌 Electronics Components

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 Development Board | 1 | Main controller |
| PCA9685 16-Channel PWM Driver | 1 | Multi-servo control |
| SG90S Metal Gear Servo | 8 | Hip & knee actuation |
| 5V External Supply | 1 | Servo power |
| 3D Printed Chassis | 1 set | Mechanical structure |
| Power Switch | 1 | Power control |

---

## 📡 ESP32 → PCA9685 Connections

| ESP32 | PCA9685 |
|---|---|
| 3.3V | VCC |
| GND | GND |
| GPIO 21 | SDA |
| GPIO 22 | SCL |

### PCA9685 I2C Address

The PCA9685 was verified using an I2C scanner.

```text
I2C Device Found:
0x40
```

Therefore:

```text
PCA9685 I2C Address = 0x40
```

---

## 🦿 Servo Channel Mapping

The eight servos are connected to PCA9685 channels **CH0–CH7**.

| Channel | Location | Joint |
|---|---|---|
| CH0 | Front Left | Hip |
| CH1 | Front Left | Knee |
| CH2 | Front Right | Hip |
| CH3 | Front Right | Knee |
| CH4 | Rear Left | Hip |
| CH5 | Rear Left | Knee |
| CH6 | Rear Right | Hip |
| CH7 | Rear Right | Knee |

---

# 🛠️ Mechanical Design

The complete chassis was designed using **FreeCAD** using a parametric modelling workflow.

The robot consists primarily of:

1. Core Body
2. Head Box
3. Four Upper Legs
4. Four Lower Legs

### Mechanical Structure

```text
                   HEAD BOX
              ┌───────────────┐
              │ ESP32 +       │
              │ PCA9685       │
              └───────┬───────┘
                      │
              ┌───────┴───────┐
              │   CORE BODY   │
              └─┬───────────┬─┘
                │           │
          Upper Leg     Upper Leg
                │           │
          Lower Leg     Lower Leg
                │           │
              Foot        Foot

          Rear legs follow the
          same 2-DOF structure.
```

---

## 📐 Component Dimensions

| Component | Dimensions |
|---|---|
| Core Body | 110 × 85 × 4 mm |
| Head Box | 85 × 65 × 45 mm |
| Upper Leg | 45 × 10 × 5 mm |
| Lower Leg | 55 × 10 × 5 mm |

### Core Body

The central chassis contains mounting positions for the four hip servos.

### Head Box

The head box houses:

- ESP32
- PCA9685
- Power switch
- Provision for future sensors

### Upper Leg

Each upper leg is driven by a hip servo.

### Lower Leg

Each lower leg is driven by a knee servo.

---

# 🖨️ 3D Printing

The mechanical components were fabricated using **Fused Deposition Modelling (FDM)**.

### Manufacturing Workflow

```text
FreeCAD CAD Model
       ↓
     STL Export
       ↓
      Slicer
       ↓
    G-code
       ↓
   FDM Printer
       ↓
3D Printed Component
       ↓
    Assembly
```

The components were fabricated in the **CGEC 3D Printing Lab**.

---

## 🧱 Materials

Two thermoplastic materials were used:

### ABS

Used for:

- Core Body
- Head Box

Selected for its stiffness and suitability for structural components.

### PLA

Used for:

- 4 × Upper Legs
- 4 × Lower Legs

---

## ⚙️ Printing Parameters

| Parameter | Value |
|---|---:|
| Layer Height | 0.2 mm |
| Infill Density | 40% |
| Perimeter Walls | 4 |
| Nozzle Diameter | 0.4 mm |
| Print Speed | 50 mm/s |
| Support | As required |

---

# 💻 Software & Programming

The project uses the **Arduino IDE** with ESP32 board support.

### Libraries

```cpp
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
```

### Libraries Used

| Library | Purpose |
|---|---|
| ESP32Servo | Direct servo control using ESP32 PWM |
| Wire | I2C communication |
| Adafruit_PWMServoDriver | PCA9685 servo control |

---

# 🧪 Testing & Debugging

One of the major practical debugging challenges was related to the **PCA9685 servo power rail**.

### Problem

Initially, all eight servos were unresponsive.

The first assumption could have been a problem with:

- ESP32
- I2C communication
- PCA9685
- Software
- Servo connections

However, an I2C scan confirmed:

```text
PCA9685 detected at:
0x40
```

This confirmed that the ESP32 and PCA9685 were communicating correctly.

### Root Cause

The PCA9685 `V+` servo power rail was measured at:

```text
0.10 V
```

instead of the expected approximately:

```text
4.8 – 5.2 V
```

### Solution

An external 5V supply was connected directly to the PCA9685 `V+` terminal.

After the correction:

```text
V+ = 4.92 – 5.05 V
```

The servos immediately responded.

### Key Lesson

> **Always verify the actuator power rail before assuming that the problem is caused by firmware or communication.**

---

# ✅ Testing Results

The complete servo system was tested after resolving the power issue.

### I2C Test

```text
ESP32
  ↓
GPIO21 / GPIO22
  ↓
SDA / SCL
  ↓
PCA9685
  ↓
0x40
```

### Servo Test

All eight servos successfully passed the individual movement test.

| Servo | Channel | 0° | 180° |
|---|---|:---:|:---:|
| Front Left Hip | CH0 | ✅ | ✅ |
| Front Left Knee | CH1 | ✅ | ✅ |
| Front Right Hip | CH2 | ✅ | ✅ |
| Front Right Knee | CH3 | ✅ | ✅ |
| Rear Left Hip | CH4 | ✅ | ✅ |
| Rear Left Knee | CH5 | ✅ | ✅ |
| Rear Right Hip | CH6 | ✅ | ✅ |
| Rear Right Knee | CH7 | ✅ | ✅ |

### Result

**All 8 servos successfully operated across the tested 0°–180° range.**

---

# 🚧 Development Status

The project was divided into nine development phases.

| Phase | Development Stage | Status |
|---:|---|---|
| 1 | Component Verification | ✅ Complete |
| 2 | CAD Design in FreeCAD | ✅ Complete |
| 3 | 3D Printing | ✅ Complete |
| 4 | Servo Calibration | ✅ Complete |
| 5 | Standing Pose | ✅ Complete |
| 6 | Walking Gait | 🔄 In Progress |
| 7 | Turning Gait | 📋 Planned |
| 8 | Sensor Integration | 📋 Planned |
| 9 | Autonomous Navigation | 🔮 Future |

### Current Progress

```text
Completed:  ██████████░░░░░░░░  5 / 9 phases
```

The presentation reports approximately **55% phase completion**.

---

# 🧭 Future Development

The project is intended to evolve beyond the current standing-pose platform.

### Phase 6 — Walking Gait

Develop coordinated leg trajectories and walking patterns using the eight available degrees of freedom.

Potential future implementation:

```text
Inverse Kinematics
       ↓
Leg Trajectory Generation
       ↓
Joint Angle Calculation
       ↓
Servo Commands
       ↓
Walking Gait
```

### Phase 7 — Turning

Implement coordinated movements that allow the robot to turn left and right.

### Phase 8 — Sensor Integration

Future sensors can be integrated to provide environmental awareness.

Possible applications include:

- Obstacle detection
- Distance measurement
- Orientation sensing
- Environmental monitoring

### Phase 9 — Autonomous Navigation

The ESP32's wireless capability provides a foundation for future:

- Wireless teleoperation
- Remote control
- Autonomous navigation
- OTA firmware updates

---

# 🌐 Potential Applications

Quadruped robots can be adapted for several real-world applications:

- 🔍 Search and rescue
- ⚙️ Rough-terrain inspection
- 🎖️ Defence and reconnaissance
- 🏥 Medical and rehabilitation assistance
- 🔬 Robotics research
- 🏭 Industrial inspection
- 🏗️ Infrastructure monitoring

---

# 📁 Suggested Repository Structure

```text
Quadruped-Robot/
│
├── README.md
│
├── Arduino/
│   ├── Servo_Test/
│   │   └── Servo_Test.ino
│   │
│   ├── I2C_Scanner/
│   │   └── I2C_Scanner.ino
│   │
│   └── PCA9685_Control/
│       └── PCA9685_Control.ino
│
├── CAD/
│   ├── Core_Body/
│   ├── Head_Box/
│   ├── Upper_Leg/
│   ├── Lower_Leg/
│   └── Assembly/
│
├── 3D_Models/
│   ├── STL/
│   └── GCODE/
│
├── Documentation/
│   └── Quadruped_Robot_Presentation.pptx
│
└── Images/
    ├── CAD/
    ├── 3D_Printing/
    ├── Electronics/
    └── Final_Robot/
```

---


**WTL & MeitY Certification-Based Industrial Training Programme**

**Department of Electronics & Communication Engineering**  
**Cooch Behar Government Engineering College**  
**2026**

---

# 📚 References

1. Previous Batch Project Report — *3D Printing and Embedded Systems*, CGEC, WTL & MeitY Project, 2024.
2. Espressif Systems — *ESP32 Technical Reference Manual*, v5.3.
3. NXP Semiconductors — *PCA9685 16-channel 12-bit PWM I2C-bus LED Controller Datasheet*.
4. Tower Pro — *SG90S Metal Gear Micro Servo Datasheet*.
5. FreeCAD Community — *FreeCAD: Your Own 3D Parametric Modeler*.

---

# ⭐ Key Takeaways

This project provided hands-on experience in the complete development cycle of a robotic system:

```text
Concept
   ↓
Electronics Design
   ↓
Component Testing
   ↓
CAD Modelling
   ↓
3D Printing
   ↓
Mechanical Assembly
   ↓
Embedded Programming
   ↓
Servo Calibration
   ↓
Standing Pose
   ↓
Walking Gait
   ↓
Autonomous Navigation
```

The completed platform establishes a **functional 8-DOF quadruped hardware and software foundation**, with future work focused on walking gait generation, turning, sensor integration, and autonomous navigation.
