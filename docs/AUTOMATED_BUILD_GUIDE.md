# 🛠️ Automated Build Script Guide

To simplify compiling, cleaning, and running the Automotive HMI Dashboard, we provide an automated bash script: `build.sh`.

This script abstracts away the underlying CMake commands and provides a user-friendly CLI to manage the project build lifecycle.

---

## Make the script executable

Before using the script for the first time, you must ensure it has execution permissions. Open your terminal and run:

```bash
chmod +x build.sh
```

---

## Basic Usage

The script uses flags to determine what actions to take. 

### 1. Initial Build
For the very first build, CMake needs to know where your Qt 5 installation is located. Use the `-q` flag to point to the `gcc_64` folder inside your Qt directory.

```bash
./build.sh -q ~/Qt/5.15.13/gcc_64
```
*This command will automatically configure the project and then compile it using all available CPU cores.*

### 2. Subsequent Builds
Once the project has been configured once, CMake caches the Qt location. For future builds (after modifying C++ or QML code), you can simply run:

```bash
./build.sh
```

### 3. Running the Application
To launch the compiled HMI Dashboard directly from the script:

```bash
./build.sh -a run
```

### 4. Cleaning the Build
If you face caching issues or want to force a completely fresh build from scratch, use the `clean` action:

```bash
./build.sh -a clean
```
*Note: After cleaning, your next build will require the `-q` flag again since the cache was deleted.*

---

## Command Line Reference

You can view the help menu at any time by running `./build.sh -h` or `./build.sh --help`.

| Short | Long | Description | Default |
|-------|------|-------------|---------|
| `-h` | `--help` | Shows the help message and examples. | - |
| `-q` | `--qt-dir` | The absolute path to your Qt 5 `gcc_64` directory. | *(Empty)* |
| `-t` | `--type` | The CMake build type (`Release` or `Debug`). | `Release` |
| `-a` | `--action` | The action to execute (`configure`, `build`, `clean`, `run`). | `build` |
| `-j` | `--jobs` | Number of parallel compilation threads. | *All CPU cores* |

---

## Advanced Examples

**Build in Debug mode with a specific number of threads (e.g., 2):**
```bash
./build.sh -t Debug -j 2
```

**Configure the project without building it yet:**
```bash
./build.sh -q ~/Qt/5.15.13/gcc_64 -a configure
```

**Clean, reconfigure, and build in one command (using chaining):**
```bash
./build.sh -a clean && ./build.sh -q ~/Qt/5.15.13/gcc_64
```
