qt_add_library(hmi_dashboard_cluster STATIC)

qt_add_qml_module(hmi_dashboard_cluster
    URI HmiDashboard.Cluster
    QML_FILES
        InstrumentCluster.qml
        Speedometer.qml
        Tachometer.qml
        TellTales.qml
        TellTaleIndicator.qml
        AdasOverlay.qml
)

target_link_libraries(hmi_dashboard_cluster PUBLIC
    Qt6::Quick
    hmi_dashboard_qml
    hmi_dashboard_components
)
