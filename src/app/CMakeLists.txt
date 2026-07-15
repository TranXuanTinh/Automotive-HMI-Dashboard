qt_add_executable(hmi_dashboard
    main.cpp
)

target_link_libraries(hmi_dashboard PRIVATE
    hmi_core
    hmi_services
    hmi_viewmodels
    hmi_dashboard_qml
    hmi_dashboard_components
    hmi_dashboard_cluster
    hmi_dashboard_infotainment
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::QmlIntegration
)
