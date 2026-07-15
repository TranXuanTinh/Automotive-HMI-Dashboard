cmake_minimum_required(VERSION 3.16)

project(HmiDashboard
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2 QmlIntegration)

qt_standard_project_setup()

# ── C++ libraries ────────────────────────────────────────────────────────
add_subdirectory(src/core)
add_subdirectory(src/services)
add_subdirectory(src/viewmodels)

# ── QML modules ──────────────────────────────────────────────────────────
add_subdirectory(qml/HmiDashboard)
add_subdirectory(qml/HmiDashboard/Components)
add_subdirectory(qml/HmiDashboard/Cluster)
add_subdirectory(qml/HmiDashboard/Infotainment)

# ── Application ──────────────────────────────────────────────────────────
add_subdirectory(src/app)
