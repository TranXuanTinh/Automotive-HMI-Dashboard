qt_add_library(hmi_services STATIC
    SimulatedCanBus.h
    SimulatedCanBus.cpp
    SimulatedAdasPipeline.h
    SimulatedAdasPipeline.cpp
    SimulatedHvacHardware.h
    SimulatedHvacHardware.cpp
    LocalFileMediaProvider.h
    LocalFileMediaProvider.cpp
    YoloProcessingStrategy.h
    YoloProcessingStrategy.cpp
    BasicProcessingStrategy.h
    BasicProcessingStrategy.cpp
)

target_include_directories(hmi_services
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hmi_services
    PUBLIC
        hmi_core
    PRIVATE
        Qt6::Core
)
