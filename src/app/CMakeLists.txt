qt5_add_resources(QML_RESOURCES ../../qml.qrc)

add_executable(hmi_dashboard
    main.cpp
    ${QML_RESOURCES}
)

target_link_libraries(hmi_dashboard PRIVATE
    hmi_core
    hmi_services
    hmi_viewmodels
    Qt5::Core
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::Gui
)
