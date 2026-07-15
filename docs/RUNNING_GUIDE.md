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

## 2. Installing Qt 6.5+

This project requires **Qt 6.5 or higher** (Qt 6.8 is recommended). Qt 5 (e.g., Qt 5.15) is **NOT** supported due to the use of modern QML modules (`qt_add_qml_module`).

The recommended way to install Qt 6 on Linux is via the Qt Online Installer.

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
3. Under the **Qt** node, expand the latest Qt 6 version (e.g., **Qt 6.8.x**).
4. Select the **Desktop gcc 64-bit** component.
5. (Optional) You can uncheck Android/iOS components to save disk space.
6. Complete the installation. Note the installation path (usually `~/Qt` or `/opt/Qt`).

---

## 3. Building the Project

We will use CMake to configure and build the project, passing the path to the newly installed Qt 6.

### Step 3.1: Configure with CMake

Replace `/path/to/Qt/6.x.x/gcc_64` with your actual Qt 6 installation path (e.g., `$HOME/Qt/6.8.0/gcc_64`).

```bash
cd /path/to/HMI_QT

# Configure the build directory
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=$HOME/Qt/6.8.0/gcc_64 -DCMAKE_BUILD_TYPE=Release
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

### Error: `Could NOT find Qt6` during CMake configuration
**Cause:** CMake cannot find your Qt 6 installation.
**Solution:** Ensure you pass the correct `-DCMAKE_PREFIX_PATH` pointing directly to the `gcc_64` folder inside your Qt version folder.
```bash
cmake -B build -DCMAKE_PREFIX_PATH=/home/username/Qt/6.8.0/gcc_64
```

### Error: `Unrecognized CMake command "qt_standard_project_setup"`
**Cause:** You are picking up an older version of Qt (like Qt 5.15) from your system packages instead of your Qt 6 installation.
**Solution:** Delete your `build` directory entirely (`rm -rf build`) and re-run the CMake configure command with the correct `CMAKE_PREFIX_PATH`.

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
**Cause:** The QML modules were not properly generated or linked by CMake.
**Solution:** Ensure you are using at least CMake 3.19+ and Qt 6.5+. Clean your build directory and recompile. The `qt_add_qml_module` command generates a C++ plugin that links directly into the executable, so no physical `.qmlc` files need to be installed on the system.
