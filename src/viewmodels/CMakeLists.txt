add_library(hmi_viewmodels STATIC
    SpeedViewModel.h
    SpeedViewModel.cpp
    RpmViewModel.h
    RpmViewModel.cpp
    TellTaleViewModel.h
    TellTaleViewModel.cpp
    AdasViewModel.h
    AdasViewModel.cpp
    HvacViewModel.h
    HvacViewModel.cpp
    MediaPlayerViewModel.h
    MediaPlayerViewModel.cpp
    VehicleSettingsViewModel.h
    VehicleSettingsViewModel.cpp
    DashboardStateManager.h
    DashboardStateManager.cpp
    WatchdogManager.h
    WatchdogManager.cpp
)

target_include_directories(hmi_viewmodels
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hmi_viewmodels
    PUBLIC
        hmi_core
        hmi_services
        Qt5::Core
    PRIVATE
        Qt5::Quick
)
