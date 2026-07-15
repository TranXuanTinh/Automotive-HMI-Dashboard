import QtQuick
import QtQuick.Layouts
import HmiDashboard.Components

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: Theme.spacingLg

        Text {
            text: qsTr("VEHICLE SETTINGS")
            color: Theme.textSecondary
            font.pixelSize: Theme.fontCaption
            font.family: "Inter"
            font.letterSpacing: 3
            font.weight: Font.DemiBold
            Layout.alignment: Qt.AlignHCenter
        }

        // ── Door locks ──────────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 220
            radius: Theme.radiusMd
            color: Theme.surface

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Theme.spacingMd
                spacing: Theme.spacingSm

                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        text: qsTr("Door Locks")
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontTitle
                        font.weight: Font.DemiBold
                        font.family: "Inter"
                    }
                    Item { Layout.fillWidth: true }
                    GlowButton {
                        text: settingsViewModel.allDoorsLocked ? qsTr("Unlock All") : qsTr("Lock All")
                        width: 100; height: 32
                        glowColor: settingsViewModel.allDoorsLocked ? Theme.accentGreen : Theme.dangerRed
                        isActive: settingsViewModel.allDoorsLocked
                        onClicked: {
                            if (settingsViewModel.allDoorsLocked)
                                settingsViewModel.unlockAll()
                            else
                                settingsViewModel.lockAll()
                        }
                    }
                }

                // Top-down car with door indicators
                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    // Car body outline
                    Rectangle {
                        anchors.centerIn: parent
                        width: 80
                        height: 140
                        radius: 20
                        color: "transparent"
                        border.width: 2
                        border.color: Theme.surfaceBorder
                    }

                    // Door indicators
                    Repeater {
                        model: settingsViewModel.doorLockStates

                        Rectangle {
                            required property int index
                            required property var modelData

                            readonly property bool isLocked: modelData.isLocked
                            readonly property bool isLeft: index === 0 || index === 2
                            readonly property bool isFront: index < 2
                            readonly property bool isTrunk: index === 4

                            x: isTrunk ? parent.width / 2 - width / 2
                               : isLeft ? parent.width / 2 - 60 - width
                               : parent.width / 2 + 60

                            y: isTrunk ? parent.height / 2 + 50
                               : isFront ? parent.height / 2 - 50
                               : parent.height / 2 + 10

                            width: isTrunk ? 60 : 24
                            height: isTrunk ? 24 : 40
                            radius: 4
                            color: isLocked ? Qt.rgba(0, 0.9, 0.46, 0.2) : Qt.rgba(1, 0.24, 0.34, 0.2)
                            border.width: 2
                            border.color: isLocked ? Theme.accentGreen : Theme.dangerRed

                            Text {
                                anchors.centerIn: parent
                                text: isLocked ? "🔒" : "🔓"
                                font.pixelSize: isTrunk ? 12 : 10
                            }

                            TapHandler {
                                onTapped: settingsViewModel.toggleDoorLock(index)
                            }

                            Behavior on border.color {
                                ColorAnimation { duration: Theme.animFast }
                            }
                        }
                    }
                }
            }
        }

        // ── Ambient lighting ────────────────────────────────────────────
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: Theme.radiusMd
            color: Theme.surface

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Theme.spacingMd
                spacing: Theme.spacingSm

                Text {
                    text: qsTr("Ambient Lighting")
                    color: Theme.textPrimary
                    font.pixelSize: Theme.fontTitle
                    font.weight: Font.DemiBold
                    font.family: "Inter"
                }

                // Color presets
                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: Theme.spacingSm

                    Repeater {
                        model: [
                            "#00D4FF", "#FF3D57", "#00E676",
                            "#B388FF", "#FFB800", "#FF6E40",
                            "#448AFF", "#E040FB"
                        ]

                        Rectangle {
                            required property int index
                            required property string modelData

                            width: 36; height: 36; radius: 18
                            color: modelData
                            border.width: settingsViewModel.ambientColor.toString().toUpperCase() ===
                                          modelData.toUpperCase() ? 3 : 0
                            border.color: "#FFFFFF"

                            TapHandler {
                                onTapped: settingsViewModel.setAmbientColor(modelData)
                            }

                            scale: tapArea.pressed ? 0.9 : 1.0
                            Behavior on scale {
                                ScaleAnimator { duration: Theme.animFast }
                            }
                            TapHandler { id: tapArea }
                        }
                    }
                }

                // Intensity
                RowLayout {
                    Layout.fillWidth: true
                    spacing: Theme.spacingSm

                    Text {
                        text: qsTr("Intensity")
                        color: Theme.textSecondary
                        font.pixelSize: Theme.fontCaption
                        font.family: "Inter"
                    }

                    GradientBar {
                        Layout.fillWidth: true
                        value: settingsViewModel.ambientIntensity
                        maxValue: 1.0
                        barColor: settingsViewModel.ambientColor
                        barHeight: 6
                    }

                    Text {
                        text: Math.round(settingsViewModel.ambientIntensity * 100) + "%"
                        color: Theme.textSecondary
                        font.pixelSize: Theme.fontCaption
                        font.family: "Inter"
                    }
                }

                // Ambient preview strip
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 4
                    radius: 2
                    color: settingsViewModel.ambientColor
                    opacity: settingsViewModel.ambientIntensity

                    Behavior on color {
                        ColorAnimation { duration: Theme.animNormal }
                    }
                }
            }
        }

        // ── Dashboard mode selector ─────────────────────────────────────
        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: Theme.spacingSm

            GlowButton {
                text: qsTr("Normal")
                isActive: dashboardState.currentState === "normal"
                glowColor: "#00D4FF"
                onClicked: dashboardState.setNormalMode()
            }
            GlowButton {
                text: qsTr("Sport")
                isActive: dashboardState.currentState === "sport"
                glowColor: "#FF3D57"
                onClicked: dashboardState.setSportMode()
            }
            GlowButton {
                text: qsTr("Parking")
                isActive: dashboardState.currentState === "parking"
                glowColor: "#00E676"
                onClicked: dashboardState.setParkingMode()
            }
        }
    }
}
