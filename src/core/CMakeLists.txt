qt_add_library(hmi_core STATIC
    src/DataIntegrity.cpp
    src/WatchdogTimer.cpp
    include/core/VehicleData.h
    include/core/AdasData.h
    include/core/HvacData.h
    include/core/MediaData.h
    include/core/IVehicleBus.h
    include/core/IVehicleSpeedObserver.h
    include/core/IVehicleRpmObserver.h
    include/core/ITellTaleObserver.h
    include/core/IAdasSensor.h
    include/core/IAdasProcessingStrategy.h
    include/core/IHvacController.h
    include/core/IMediaProvider.h
    include/core/DataIntegrity.h
    include/core/WatchdogTimer.h
)

target_include_directories(hmi_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(hmi_core
    PUBLIC
        Qt6::Core
)
