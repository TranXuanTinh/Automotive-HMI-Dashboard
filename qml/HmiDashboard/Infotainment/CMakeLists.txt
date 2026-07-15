qt_add_library(hmi_dashboard_infotainment STATIC)

qt_add_qml_module(hmi_dashboard_infotainment
    URI HmiDashboard.Infotainment
    QML_FILES
        InfotainmentPanel.qml
        HvacPanel.qml
        MediaPlayer.qml
        VehicleSettings.qml
)

target_link_libraries(hmi_dashboard_infotainment PUBLIC
    Qt6::Quick
    hmi_dashboard_qml
    hmi_dashboard_components
)
