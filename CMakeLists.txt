cmake_minimum_required(VERSION 3.15)

project(HmiDashboard
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Quick QuickControls2 Gui REQUIRED)

# ── C++ libraries ────────────────────────────────────────────────────────
add_subdirectory(src/core)
add_subdirectory(src/services)
add_subdirectory(src/viewmodels)

# ── Application ──────────────────────────────────────────────────────────
add_subdirectory(src/app)
