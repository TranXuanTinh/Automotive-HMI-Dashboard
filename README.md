# 🚗 Automotive HMI Dashboard

<div align="center">

**A comprehensive, safety-certified Automotive Human-Machine Interface built with Qt 6 / QML / C++17**

[![Qt](https://img.shields.io/badge/Qt-6.5+-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C++-17-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![ISO 26262](https://img.shields.io/badge/ISO_26262-ASIL_B/C-orange)](docs/ARCHITECTURE.md#functional-safety)

</div>

---

## Overview

This project implements a production-grade Automotive HMI system that combines a **digital Instrument Cluster** and an **Infotainment** system into a unified dashboard. It is designed for embedded Linux environments (Ubuntu 24.04) with GPU-accelerated rendering targeting a stable **60 FPS**.

The architecture strictly adheres to **SOLID principles**, employs the **MVVM pattern** with Qt's signal/slot mechanism, and incorporates **ISO 26262 functional safety** features including watchdog monitoring, data integrity checks, and ASIL/QM component separation.

<div align="center">

```
┌─────────────────────────────────────────────────────────────────────┐
│                    Automotive HMI Dashboard                         │
│                                                                     │
│  ┌───────────────────────────────┐  ┌────────────────────────────┐  │
│  │     INSTRUMENT CLUSTER        │  │      INFOTAINMENT          │  │
│  │        (ASIL B/C)             │  │         (QM)               │  │
│  │                               │  │                            │  │
│  │  ┌──────────┐ ┌──────────┐   │  │  ┌──────────────────────┐  │  │
│  │  │Speedometer│ │Tachometer│   │  │  │   Climate Control    │  │  │
│  │  │  0-280   │ │  0-8000  │   │  │  │  Driver ◉ Passenger  │  │  │
│  │  │  km/h    │ │   RPM    │   │  │  │  22.0°C    22.0°C    │  │  │
│  │  └──────────┘ └──────────┘   │  │  └──────────────────────┘  │  │
│  │                               │  │  ┌──────────────────────┐  │  │
│  │  ⚙ ◎ ◉ ⊘ ⊛ ◈ ◀ ▶ ⊞ ◆ ◇ ▣   │  │  │    Media Player      │  │  │
│  │  [Tell-tale Warning Lights]   │  │  │  ♫ Midnight Drive     │  │  │
│  │                               │  │  │  ▶ ━━━━━━━━━━◉━━     │  │  │
│  │  ┌──────────────────────────┐ │  │  └──────────────────────┘  │  │
│  │  │  ADAS Object Detection   │ │  │  ┌──────────────────────┐  │  │
│  │  │  Vehicle 95% │ Ped 87%  │ │  │  │  Vehicle Settings     │  │  │
│  │  └──────────────────────────┘ │  │  │  🔒 Door Locks        │  │  │
│  └───────────────────────────────┘  │  │  💡 Ambient Lighting   │  │  │
│                                      │  └──────────────────────┘  │  │
│  ═══════════════════════════════════════════════════════════════╡  │
│  [ NORMAL ]  [ SPORT ]  [ PARKING ]            Mode Selector    │  │
└─────────────────────────────────────────────────────────────────────┘
```

</div>

---

## ✨ Features

### Instrument Cluster (ASIL B/C — Safety-Critical)
- **Speedometer** — Real-time circular gauge (0–280 km/h) with color-coded thresholds, animated needle via `RotationAnimator`, and km/h ↔ mph toggle
- **Tachometer** — RPM gauge (0–8000 RPM) with redline zone indicator and integrated gear display (N, 1–8, R)
- **Tell-tale Warning Lights** — 14 safety indicators (Check Engine, ABS, Tire Pressure, Seatbelt, Brake, High Beam, Turn Signals, Battery, Oil Pressure, Temperature, Door Ajar, Airbag, Traction Control) with Off/On/Blinking/Error states
- **ADAS Visualization** — Real-time bounding box overlay for detected objects (Vehicle, Pedestrian, Cyclist, Traffic Sign) with class labels, confidence scores, and color-coded categories

### Infotainment (QM — Non-Safety)
- **Climate Control** — Dual-zone HVAC with driver/passenger temperature (16–30°C), 8-level fan speed, A/C toggle, recirculation, sync mode, and 5 airflow modes
- **Media Player** — 7-track demo playlist with play/pause/next/prev, seekable progress bar, rotating vinyl album art, formatted time display, and volume control
- **Vehicle Settings** — Top-down door lock visualization (5 doors with lock/unlock/lock-all), ambient lighting color picker (8 preset colors + intensity), and dashboard mode selector

### Dashboard Modes (State Pattern)
| Mode | Cluster Width | Accent Color | Description |
|------|--------------|--------------|-------------|
| **Normal** | 60% | Cyan `#00D4FF` | Standard driving mode |
| **Sport** | 70% | Red `#FF3D57` | Expanded cluster, performance focus |
| **Parking** | 50% | Green `#00E676` | Balanced layout for camera view |
| **Safe Mode** | 100% | Amber `#FFB800` | Text-only cluster, infotainment disabled |

### Functional Safety (ISO 26262)
- **CRC-8 Data Integrity** — Every incoming CAN frame validated with SAE J1850 polynomial checksums
- **Alive Counter Monitoring** — Detects stale, repeated, or out-of-sequence messages
- **Software Watchdog** — 500ms timeout; GUI thread kicks every 100ms; expiry triggers Safe Mode
- **ASIL/QM Separation** — Cluster operates independently; infotainment crash cannot affect telemetry display

---

## 🏗️ Tech Stack

| Component | Technology |
|-----------|-----------|
| **Language** | C++17 (backend), QML (frontend) |
| **Framework** | Qt 6.5+ (Qt Quick, Qt Quick Controls) |
| **Build System** | CMake 3.16+ |
| **Rendering** | OpenGL via Qt Quick Scene Graph |
| **Architecture** | MVVM + Observer + Strategy + State patterns |
| **Target OS** | Ubuntu 24.04 LTS (Embedded Linux) |

---

## 📁 Project Structure

```
HMI_QT/
├── CMakeLists.txt                          # Top-level project setup
├── README.md                               # This file
├── docs/
│   ├── ARCHITECTURE.md                     # Detailed architecture documentation
│   └── RUNNING_GUIDE.md                    # Build & run instructions
│
├── src/
│   ├── core/                               # Core library (no Qt Quick dependency)
│   │   ├── include/core/                   # Public headers
│   │   │   ├── VehicleData.h               # Speed/RPM/TellTale data structs
│   │   │   ├── AdasData.h                  # ADAS perception data structs
│   │   │   ├── HvacData.h                  # HVAC state data
│   │   │   ├── MediaData.h                 # Media playback data
│   │   │   ├── IVehicleBus.h               # Vehicle bus interface
│   │   │   ├── IVehicleSpeedObserver.h     # Segregated speed observer (ISP)
│   │   │   ├── IVehicleRpmObserver.h       # Segregated RPM observer (ISP)
│   │   │   ├── ITellTaleObserver.h         # Segregated tell-tale observer (ISP)
│   │   │   ├── IAdasSensor.h               # ADAS sensor interface
│   │   │   ├── IAdasProcessingStrategy.h   # Strategy pattern interface
│   │   │   ├── IHvacController.h           # HVAC hardware interface
│   │   │   ├── IMediaProvider.h            # Media source interface (OCP)
│   │   │   ├── DataIntegrity.h             # CRC-8 + alive counter validation
│   │   │   └── WatchdogTimer.h             # Software watchdog
│   │   └── src/
│   │       ├── DataIntegrity.cpp
│   │       └── WatchdogTimer.cpp
│   │
│   ├── services/                           # Concrete service implementations
│   │   ├── SimulatedCanBus.h/.cpp          # Simulated CAN bus (50 Hz)
│   │   ├── SimulatedAdasPipeline.h/.cpp    # Simulated ADAS detections (10 Hz)
│   │   ├── SimulatedHvacHardware.h/.cpp    # Simulated HVAC with response lag
│   │   ├── LocalFileMediaProvider.h/.cpp   # Demo playlist media provider
│   │   ├── YoloProcessingStrategy.h/.cpp   # YOLO NMS + confidence filtering
│   │   └── BasicProcessingStrategy.h/.cpp  # Pass-through radar fallback
│   │
│   ├── viewmodels/                         # MVVM ViewModel layer
│   │   ├── SpeedViewModel.h/.cpp           # Speed display + unit conversion
│   │   ├── RpmViewModel.h/.cpp             # RPM + gear display
│   │   ├── TellTaleViewModel.h/.cpp        # Tell-tale list model
│   │   ├── AdasViewModel.h/.cpp            # ADAS detections list model
│   │   ├── HvacViewModel.h/.cpp            # HVAC controls bridge
│   │   ├── MediaPlayerViewModel.h/.cpp     # Media playback bridge
│   │   ├── VehicleSettingsViewModel.h/.cpp # Door locks + ambient lighting
│   │   ├── DashboardStateManager.h/.cpp    # State Pattern (4 modes)
│   │   └── WatchdogManager.h/.cpp          # Watchdog coordination
│   │
│   └── app/
│       └── main.cpp                        # Application entry + DI wiring
│
└── qml/
    └── HmiDashboard/                       # QML module: HmiDashboard
        ├── Main.qml                        # Root window (1920×720)
        ├── Theme.qml                       # Design system singleton
        ├── Components/                     # QML module: HmiDashboard.Components
        │   ├── CircularGauge.qml           # Reusable gauge with Shape/ShapePath
        │   ├── GlowButton.qml             # Neon glow button
        │   └── GradientBar.qml            # Animated progress bar
        ├── Cluster/                        # QML module: HmiDashboard.Cluster
        │   ├── InstrumentCluster.qml       # ASIL container + safe mode
        │   ├── Speedometer.qml
        │   ├── Tachometer.qml
        │   ├── TellTales.qml
        │   ├── TellTaleIndicator.qml
        │   └── AdasOverlay.qml
        └── Infotainment/                   # QML module: HmiDashboard.Infotainment
            ├── InfotainmentPanel.qml       # Tabbed navigation
            ├── HvacPanel.qml
            ├── MediaPlayer.qml
            └── VehicleSettings.qml
```

---

## 🚀 Quick Start

### Prerequisites
- **Ubuntu 24.04 LTS** (or compatible Linux)
- **Qt 6.5+** (recommended: Qt 6.8 via [Qt Online Installer](https://www.qt.io/download-qt-installer))
- **CMake 3.16+**
- **GCC 11+** or **Clang 14+** (C++17 support required)
- **GPU with OpenGL 3.0+** support

### Build & Run

```bash
# Clone or navigate to the project
cd /path/to/HMI_QT

# Configure (adjust Qt path to your installation)
cmake -B build -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.0/gcc_64

# Build
cmake --build build -j$(nproc)

# Run
./build/src/app/hmi_dashboard
```

Press **Escape** to exit fullscreen, press again to quit.

> For detailed build instructions, troubleshooting, and configuration options, see [docs/RUNNING_GUIDE.md](docs/RUNNING_GUIDE.md).

---

## 📐 Architecture

The system follows a strict **layered architecture** with dependency inversion:

```
┌─────────────────────────────────────────────┐
│             QML (View Layer)                │  Theme.qml, Main.qml, Gauges, Panels
├─────────────────────────────────────────────┤
│          ViewModels (Bridge Layer)          │  SpeedVM, RpmVM, HvacVM, MediaVM, ...
├─────────────────────────────────────────────┤
│        Services (Implementation Layer)      │  SimulatedCanBus, AdasPipeline, ...
├─────────────────────────────────────────────┤
│       Core (Interfaces + Data Layer)        │  IVehicleBus, IAdasSensor, DataIntegrity
└─────────────────────────────────────────────┘
```

Key architectural decisions:
- **Core has ZERO Qt Quick dependency** — only Qt Core. This ensures testability and safety-critical code isolation.
- **All cross-layer communication uses abstract interfaces** — Dependency Inversion Principle.
- **Concrete implementations are injected in `main.cpp`** — single composition root.
- **Thread safety via Qt's queued connections** — data flows from worker threads to GUI thread safely.

> For the full architecture documentation with class diagrams, pattern analysis, and safety compliance details, see [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

---

## 🎨 Design System

The dashboard uses a dark automotive theme defined in `Theme.qml`:

| Token | Value | Usage |
|-------|-------|-------|
| `background` | `#0A0E17` | Main background |
| `surface` | `#1A2236` | Card/panel surfaces |
| `accentCyan` | `#00D4FF` | Normal mode accent |
| `dangerRed` | `#FF3D57` | Sport mode / brake warnings |
| `accentGreen` | `#00E676` | Parking mode / vehicle indicators |
| `warningAmber` | `#FFB800` | Safe mode / warning tell-tales |
| `textPrimary` | `#FFFFFF` | Primary text |
| `textSecondary` | `#8899B4` | Secondary text |

---

## 🔌 Extending the System

### Adding a New Media Source (e.g., Bluetooth)

1. Create `BluetoothMediaProvider.h/.cpp` implementing `IMediaProvider`
2. Add to `src/services/CMakeLists.txt`
3. In `main.cpp`, instantiate and inject instead of `LocalFileMediaProvider`
4. **No existing code modified** — Open/Closed Principle

### Adding a New ADAS Algorithm

1. Create a new class implementing `IAdasProcessingStrategy`
2. In `main.cpp`, call `adasVm.setProcessingStrategy(std::make_unique<NewStrategy>())`
3. **Swappable at runtime** — Strategy Pattern

### Adding a New Dashboard Mode

1. Add a new state to `DashboardStateManager::State` enum
2. Implement the state's `accentColor()`, `clusterWidthRatio()`, and visibility rules
3. Add a `Q_INVOKABLE` setter method
4. Add a button in `VehicleSettings.qml`

### Replacing Simulated Data with Real Hardware

1. Implement `IVehicleBus` with a real CAN bus adapter (e.g., SocketCAN)
2. Implement `IAdasSensor` with a real camera/YOLO pipeline
3. Inject in `main.cpp` — **all ViewModels and QML remain unchanged**

---

## 📄 Documentation

| Document | Description |
|----------|-------------|
| [README.md](README.md) | This file — project overview and quick start |
| [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) | Detailed architecture, SOLID analysis, pattern catalog, safety compliance |
| [docs/RUNNING_GUIDE.md](docs/RUNNING_GUIDE.md) | Step-by-step build instructions, Qt installation, troubleshooting |

---

## 📜 License

This project is provided for educational and demonstration purposes.

---

## 🙏 Acknowledgments

- **Qt Company** — Qt 6 framework and Qt AI Skills
- **ISO 26262** — Automotive functional safety standard
- **SAE J1850** — CRC polynomial for vehicle bus data integrity
