import QtQuick 2.15
import QtQuick.Layouts 1.15
import "../Components"
import HmiDashboard 1.0

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: Theme.spacingLg

        // ── Title ───────────────────────────────────────────────────────
        Text {
            text: qsTr("CLIMATE CONTROL")
            color: Theme.textSecondary
            font.pixelSize: Theme.fontCaption
            font.family: "Inter"
            font.letterSpacing: 3
            font.weight: Font.DemiBold
            Layout.alignment: Qt.AlignHCenter
        }

        // ── Temperature controls ────────────────────────────────────────
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: Theme.spacingLg

            // Driver side
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: Theme.spacingSm

                Text {
                    text: qsTr("DRIVER")
                    color: Theme.textDim
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                    font.letterSpacing: 2
                    Layout.alignment: Qt.AlignHCenter
                }

                // Temperature display
                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 120
                    radius: 60
                    color: Theme.surface
                    border.width: 2
                    border.color: Qt.rgba(
                                      dashboardState.accentColor.r,
                                      dashboardState.accentColor.g,
                                      dashboardState.accentColor.b, 0.4)

                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: hvacViewModel.driverTemp.toFixed(1)
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontHeading
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "°C"
                            color: Theme.textSecondary
                            font.pixelSize: Theme.fontCaption
                            font.family: "Inter"
                        }
                    }
                }

                // Temp +/- buttons
                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: Theme.spacingMd

                    GlowButton {
                        text: "−"
                        width: 44; height: 44
                        borderRadius: 22
                        glowColor: Theme.accentCyan
                        onClicked: hvacViewModel.decreaseDriverTemp()
                    }
                    GlowButton {
                        text: "+"
                        width: 44; height: 44
                        borderRadius: 22
                        glowColor: Theme.dangerRed
                        onClicked: hvacViewModel.increaseDriverTemp()
                    }
                }
            }

            // ── Center controls ─────────────────────────────────────────
            ColumnLayout {
                Layout.fillHeight: true
                Layout.preferredWidth: 240
                spacing: Theme.spacingSm

                // Fan speed
                Text {
                    text: qsTr("FAN")
                    color: Theme.textDim
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                    font.letterSpacing: 2
                    Layout.alignment: Qt.AlignHCenter
                }

                GradientBar {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 12
                    value: hvacViewModel.fanSpeed
                    maxValue: hvacViewModel.maxFanSpeed
                    barColor: dashboardState.accentColor
                    barHeight: 8
                }

                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 4
                    GlowButton {
                        text: "−"; width: 36; height: 32; borderRadius: 8
                        onClicked: hvacViewModel.setFanSpeed(hvacViewModel.fanSpeed - 1)
                    }
                    Text {
                        text: hvacViewModel.fanSpeed
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontTitle
                        font.weight: Font.Bold
                        font.family: "Inter"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    GlowButton {
                        text: "+"; width: 36; height: 32; borderRadius: 8
                        onClicked: hvacViewModel.setFanSpeed(hvacViewModel.fanSpeed + 1)
                    }
                }

                Item { Layout.fillHeight: true }

                Image {
                    source: "qrc:/qml/HmiDashboard/assets/vinfast_vf8.png"
                    Layout.preferredWidth: 220
                    Layout.preferredHeight: 220
                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignHCenter
                }

                Item { Layout.fillHeight: true }

                // Toggle buttons
                GlowButton {
                    text: "A/C"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    isActive: hvacViewModel.isAcOn
                    glowColor: Theme.accentCyan
                    onClicked: hvacViewModel.toggleAc()
                }

                GlowButton {
                    text: "↻"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    isActive: hvacViewModel.isRecircOn
                    glowColor: Theme.accentCyan
                    onClicked: hvacViewModel.toggleRecirc()
                }

                GlowButton {
                    text: "SYNC"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 36
                    isActive: hvacViewModel.isSyncOn
                    glowColor: Theme.warningAmber
                    onClicked: hvacViewModel.toggleSync()
                }
            }

            // Passenger side
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: Theme.spacingSm

                Text {
                    text: qsTr("PASSENGER")
                    color: Theme.textDim
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                    font.letterSpacing: 2
                    Layout.alignment: Qt.AlignHCenter
                }

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 120
                    radius: 60
                    color: Theme.surface
                    border.width: 2
                    border.color: Qt.rgba(
                                      dashboardState.accentColor.r,
                                      dashboardState.accentColor.g,
                                      dashboardState.accentColor.b, 0.4)
                    opacity: hvacViewModel.isSyncOn ? 0.5 : 1.0

                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: hvacViewModel.passengerTemp.toFixed(1)
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontHeading
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "°C"
                            color: Theme.textSecondary
                            font.pixelSize: Theme.fontCaption
                            font.family: "Inter"
                        }
                    }
                }

                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: Theme.spacingMd
                    enabled: !hvacViewModel.isSyncOn

                    GlowButton {
                        text: "−"
                        width: 44; height: 44
                        borderRadius: 22
                        glowColor: Theme.accentCyan
                        onClicked: hvacViewModel.decreasePassengerTemp()
                    }
                    GlowButton {
                        text: "+"
                        width: 44; height: 44
                        borderRadius: 22
                        glowColor: Theme.dangerRed
                        onClicked: hvacViewModel.increasePassengerTemp()
                    }
                }
            }
        }

        // ── Airflow mode selector ───────────────────────────────────────
        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: Theme.spacingSm

            Repeater {
                model: [
                    { text: "↑",   mode: 0, label: qsTr("Face") },
                    { text: "↓",   mode: 1, label: qsTr("Feet") },
                    { text: "↕",   mode: 2, label: qsTr("Both") },
                    { text: "△",   mode: 3, label: qsTr("Defrost") },
                    { text: "▽△",  mode: 4, label: qsTr("Def+Feet") }
                ]

                GlowButton {
                    required property var modelData
                    text: modelData.text
                    width: 56; height: 40
                    isActive: hvacViewModel.airflowMode === modelData.mode
                    glowColor: dashboardState.accentColor
                    onClicked: hvacViewModel.setAirflowMode(modelData.mode)
                }
            }
        }
    }
}
