import QtQuick

Item {
    id: root

    // ── Background ──────────────────────────────────────────────────────
    Rectangle {
        anchors.fill: parent
        color: Theme.background

        // Subtle radial gradient behind gauges
        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 0.8
            height: parent.height * 0.8
            radius: width / 2
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(0, 0.83, 1.0, 0.03) }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }
    }

    // ── Safe mode fallback ──────────────────────────────────────────────
    Rectangle {
        id: safeModeOverlay
        anchors.fill: parent
        color: "#000000"
        visible: dashboardState.isSafeMode
        z: 100

        Column {
            anchors.centerIn: parent
            spacing: Theme.spacingLg

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "⚠ SAFE MODE"
                color: Theme.warningAmber
                font.pixelSize: Theme.fontHeading
                font.weight: Font.Bold
                font.family: "Inter"
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.spacingXl

                Column {
                    spacing: 4
                    Text {
                        text: speedViewModel.speedText
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontHero
                        font.weight: Font.Bold
                        font.family: "Inter"
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: speedViewModel.unit
                        color: Theme.textSecondary
                        font.pixelSize: Theme.fontBody
                        font.family: "Inter"
                    }
                }

                Column {
                    spacing: 4
                    Text {
                        text: rpmViewModel.rpmText
                        color: Theme.textPrimary
                        font.pixelSize: Theme.fontDisplay
                        font.weight: Font.Bold
                        font.family: "Inter"
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("RPM")
                        color: Theme.textSecondary
                        font.pixelSize: Theme.fontBody
                        font.family: "Inter"
                    }
                }

                Text {
                    text: rpmViewModel.gearText
                    color: Theme.warningAmber
                    font.pixelSize: Theme.fontHero
                    font.weight: Font.Bold
                    font.family: "Inter"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    // ── Normal cluster layout ───────────────────────────────────────────
    Item {
        id: normalCluster
        anchors.fill: parent
        visible: !dashboardState.isSafeMode

        // ── Gauges row ──────────────────────────────────────────────────
        Row {
            id: gaugeRow
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -20
            spacing: Theme.spacingLg

            Speedometer {
                id: speedometer
                width: Math.min(root.width * 0.42, 340)
                height: width
            }

            Tachometer {
                id: tachometer
                width: Math.min(root.width * 0.34, 280)
                height: width
                anchors.verticalCenter: speedometer.verticalCenter
            }
        }

        // ── Tell-tales ──────────────────────────────────────────────────
        TellTales {
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Theme.spacingMd
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(parent.width - Theme.spacingLg * 2, 560)
        }

        // ── ADAS overlay ────────────────────────────────────────────────
        AdasOverlay {
            anchors.fill: parent
        }
    }
}
