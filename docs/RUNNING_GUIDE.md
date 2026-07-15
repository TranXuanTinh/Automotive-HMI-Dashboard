# 🚀 Running Guide

This guide provides step-by-step instructions for installing dependencies, compiling, and running the Automotive HMI Dashboard on an Ubuntu 24.04 LTS (or similar) Linux environment.

---

## 1. Prerequisites

### System Requirements
- **OS:** Ubuntu 24.04 LTS (or compatible modern Linux distribution)
- **Compiler:** GCC 11+ or Clang 14+ (Must support C++17)
- **Build System:** CMake 3.16 or higher, Ninja (recommended) or Make
- **Graphics:** OpenGL 3.0+ capable GPU (Intel HD, AMD Radeon, or NVIDIA)

### Install Core Build Tools

Open a terminal and run:
```bash
sudo apt update
sudo apt install -y build-essential cmake ninja-build git mesa-common-dev libgl1-mesa-dev
```

---

## 2. Installing Qt 5.15.13

This project requires **Qt 5.15.13**.

The recommended way to install Qt 5.15 on Linux is via the system package manager (e.g. `sudo apt install qtbase5-dev qtdeclarative5-dev qml-module-qtquick-controls2 qml-module-qtquick-shapes qt5-qmake`) or the Qt Online Installer.

### Step 2.1: Download the Installer
1. Go to the [Qt Download Page](https://www.qt.io/download-qt-installer) (Open Source or Commercial).
2. Download the Linux installer (e.g., `qt-unified-linux-x64-online.run`).

### Step 2.2: Run the Installer
```bash
cd ~/Downloads
chmod +x qt-unified-linux-x64-online.run
./qt-unified-linux-x64-online.run
```

### Step 2.3: Select Components
During the installation wizard:
1. Log in with your Qt account.
2. Select **Custom Installation**.
3. Under the **Qt** node, expand **Qt 5.15.13**.
4. Select the **Desktop gcc 64-bit** component.
5. (Optional) You can uncheck Android/iOS components to save disk space.
6. Complete the installation. Note the installation path (usually `~/Qt` or `/opt/Qt`).

---

## 3. Building the Project

We will use CMake to configure and build the project, passing the path to the installed Qt 5.

### Step 3.1: Configure with CMake

If you installed Qt via the Online Installer, replace `/path/to/Qt/5.15.x/gcc_64` with your actual Qt 5 installation path (e.g., `$HOME/Qt/5.15.13/gcc_64`). If you used `apt`, you can omit `-DCMAKE_PREFIX_PATH`.

```bash
cd /path/to/HMI_QT

# Configure the build directory
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$HOME/Qt/5.15.13/gcc_64 -DCMAKE_BUILD_TYPE=Release
```

### Step 3.2: Compile

```bash
cmake --build build
```
*(If you didn't install Ninja and are using Make, use `cmake --build build -j$(nproc)` for a parallel build).*

---

## 4. Running the Dashboard

Once compilation is successful, you can run the executable directly:

```bash
./build/src/app/hmi_dashboard
```

### Controls & Interaction
- The application launches in **Fullscreen Mode**.
- **Exit Fullscreen:** Press the `Escape` key.
- **Quit:** Press `Escape` again while in windowed mode, or use `Alt+F4`.
- **Speed Unit Toggle:** Click/Tap on the speed unit ("km/h") on the speedometer to switch to "mph".
- **Dashboard Modes:** Use the "Normal / Sport / Parking" buttons in the Vehicle Settings tab to see the layout animate and colors change.

---

## 5. Troubleshooting

### Error: `Could NOT find Qt5` during CMake configuration
**Cause:** CMake cannot find your Qt 5 installation.
**Solution:** Ensure you pass the correct `-DCMAKE_PREFIX_PATH` pointing directly to the `gcc_64` folder inside your Qt version folder.
```bash
cmake -B build -DCMAKE_PREFIX_PATH=/home/username/Qt/5.15.13/gcc_64
```


### Error: Application fails to start or shows a blank white/black screen
**Cause:** Missing OpenGL drivers or Qt Wayland plugin issues on Ubuntu 24.04.
**Solution:** Try forcing the application to run on X11 or Wayland using environment variables:
```bash
# Force X11 backend
QT_QPA_PLATFORM=xcb ./build/src/app/hmi_dashboard

# OR Force Wayland backend
QT_QPA_PLATFORM=wayland ./build/src/app/hmi_dashboard
```

### Warning/Error: `module "HmiDashboard" is not installed`
**Cause:** The QRC resource file was not properly generated or linked by CMake.
**Solution:** Ensure your `qml.qrc` file includes all necessary QML files and that `qt5_add_resources` is correctly called in the `CMakeLists.txt`. Clean your build directory and recompile.
