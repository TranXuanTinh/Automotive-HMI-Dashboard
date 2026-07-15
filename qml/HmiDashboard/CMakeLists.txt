set_source_files_properties(Theme.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_library(hmi_dashboard_qml STATIC)

qt_add_qml_module(hmi_dashboard_qml
    URI HmiDashboard
    QML_FILES
        Main.qml
        Theme.qml
)

target_link_libraries(hmi_dashboard_qml PUBLIC
    Qt6::Quick
)
