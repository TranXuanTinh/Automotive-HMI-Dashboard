qt_add_library(hmi_dashboard_components STATIC)

qt_add_qml_module(hmi_dashboard_components
    URI HmiDashboard.Components
    QML_FILES
        CircularGauge.qml
        GlowButton.qml
        GradientBar.qml
)

target_link_libraries(hmi_dashboard_components PUBLIC
    Qt6::Quick
    hmi_dashboard_qml
)
