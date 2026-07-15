#!/bin/bash

# Exit on any error
set -e

# Default values
BUILD_TYPE="Release"
ACTION="build"
BUILD_DIR="build"
QT_DIR=""
JOBS=$(nproc 2>/dev/null || echo 4)

# Display help
show_help() {
    echo "🚗 Automotive HMI Dashboard - Automated Build Script"
    echo "===================================================="
    echo "Usage: ./build.sh [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -h, --help           Show this help message"
    echo "  -q, --qt-dir PATH    Path to Qt 5 gcc_64 directory (Required for first configuration)"
    echo "                       Example: ~/Qt/5.15.13/gcc_64"
    echo "  -t, --type TYPE      Build type: Release or Debug (Default: Release)"
    echo "  -a, --action ACTION  Action to perform: configure, build, clean, run (Default: build)"
    echo "                       Note: 'build' automatically configures if needed."
    echo "  -j, --jobs N         Number of parallel build jobs (Default: $JOBS)"
    echo ""
    echo "Examples:"
    echo "  1. Initial configure and build:"
    echo "     ./build.sh -q ~/Qt/5.15.13/gcc_64"
    echo ""
    echo "  2. Run the application:"
    echo "     ./build.sh -a run"
    echo ""
    echo "  3. Clean the build directory:"
    echo "     ./build.sh -a clean"
    echo ""
    echo "  4. Build in Debug mode:"
    echo "     ./build.sh -t Debug -a build"
    echo ""
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -h|--help)
            show_help
            exit 0
            ;;
        -q|--qt-dir)
            QT_DIR="$2"
            shift 2
            ;;
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -a|--action)
            ACTION="$2"
            shift 2
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        *)
            echo "❌ Error: Unknown option: $1"
            echo ""
            show_help
            exit 1
            ;;
    esac
done

configure() {
    echo "⚙️ Configuring project ($BUILD_TYPE mode)..."
    
    if [ -z "$QT_DIR" ]; then
        if [ ! -d "$BUILD_DIR" ]; then
            echo "⚠️  No Qt directory provided. Assuming Qt 5 is installed system-wide."
        fi
        # Re-configure without needing the prefix path if it was already configured
        cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    else
        # Full configure with Qt path
        cmake -S . -B "$BUILD_DIR" -DCMAKE_PREFIX_PATH="$QT_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
    fi
    echo "✅ Configuration complete."
}

build() {
    if [ ! -d "$BUILD_DIR" ]; then
        configure
    fi
    echo "🔨 Building project (using $JOBS parallel jobs)..."
    cmake --build "$BUILD_DIR" -j"$JOBS"
    echo "✅ Build complete."
}

clean() {
    echo "🧹 Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    echo "✅ Cleaned."
}

run() {
    build # Automatically build first to ensure all QML/C++ changes are compiled
    local EXE="$BUILD_DIR/src/app/hmi_dashboard"
    if [ ! -f "$EXE" ]; then
        echo "❌ Error: Executable not found at $EXE"
        exit 1
    fi
    echo "🚀 Running Automotive HMI Dashboard..."
    "$EXE"
}

# Execute the requested action
case $ACTION in
    configure)
        configure
        ;;
    build)
        build
        ;;
    clean)
        clean
        ;;
    run)
        run
        ;;
    *)
        echo "❌ Error: Unknown action '$ACTION'"
        echo "Valid actions are: configure, build, clean, run"
        exit 1
        ;;
esac
