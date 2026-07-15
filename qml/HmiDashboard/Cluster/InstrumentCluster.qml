import QtQuick 2.15
import QtQuick.Shapes 1.15
import QtQuick.Layouts 1.15
import HmiDashboard 1.0

Item {
    id: root

    // Live clock and date strings
    property string timeString: "14:16"
    property string dateString: "12/08/2023"

    Timer {
        interval: 1000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            var date = new Date()
            timeString = Qt.formatTime(date, "hh:mm")
            dateString = Qt.formatDate(date, "dd/MM/yyyy")
        }
    }

    // ── Outer Capsule Frame (Mockup Frame) ──────────────────────────────────
    Rectangle {
        anchors.fill: parent
        anchors.margins: Theme.spacingSm
        color: "#0B0F19"
        border.width: 8
        border.color: Theme.accentCyan
        radius: 80
        clip: true

        // ── Top Bar with Status / Clock / Date ──────────────────────────────
        Rectangle {
            id: topBar
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.45
            height: 38
            color: "#111625"
            radius: 12

            // Top bar border styling
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Qt.rgba(0, 0.83, 1.0, 0.2)
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.spacingLg
                anchors.rightMargin: Theme.spacingLg

                // Left headlight icon
                Text {
                    text: "⛯"
                    color: Theme.accentCyan
                    font.pixelSize: 16
                    font.weight: Font.Bold
                    Layout.alignment: Qt.AlignVCenter
                }

                Item { Layout.fillWidth: true }

                // Live Clock
                Text {
                    text: root.timeString
                    color: Theme.textPrimary
                    font.pixelSize: 14
                    font.weight: Font.Bold
                    font.family: "Inter"
                    Layout.alignment: Qt.AlignVCenter
                }

                Item { Layout.fillWidth: true }

                // Live Date
                Text {
                    text: root.dateString
                    color: Theme.textSecondary
                    font.pixelSize: 12
                    font.family: "Inter"
                    Layout.alignment: Qt.AlignVCenter
                }
            }
        }

        // ── Main Dashboard Layout Grid ───────────────────────────────────────
        RowLayout {
            anchors.fill: parent
            anchors.topMargin: 50
            anchors.bottomMargin: 50
            anchors.leftMargin: Theme.spacingXl
            anchors.rightMargin: Theme.spacingXl
            spacing: Theme.spacingLg

            // ── Left Column: Lights Tell-tales ──
            Column {
                Layout.preferredWidth: 40
                Layout.fillHeight: true
                spacing: Theme.spacingMd
                Layout.alignment: Qt.AlignVCenter

                Repeater {
                    model: tellTaleViewModel
                    delegate: Loader {
                        active: index === 5 || index === 6 || index === 7 || index === 10
                        sourceComponent: TellTaleIndicator {
                            name: model.name
                            iconSource: model.iconSource
                            state: model.state
                            isActive: model.isActive
                            color: model.color
                            isBlinking: model.isBlinking
                        }
                    }
                }
            }

            // ── Left Panel: Battery Charge ──
            Item {
                Layout.preferredWidth: 200
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter

                // Battery Gauge Ring
                Shape {
                    anchors.fill: parent
                    layer.enabled: true
                    layer.samples: 4

                    ShapePath {
                        fillColor: "transparent"
                        strokeColor: Theme.gaugeTrack
                        strokeWidth: 8
                        capStyle: ShapePath.RoundCap
                        PathAngleArc {
                            centerX: parent.width / 2
                            centerY: parent.height / 2
                            radiusX: 75
                            radiusY: 75
                            startAngle: -210
                            sweepAngle: 240
                        }
                    }

                    ShapePath {
                        fillColor: "transparent"
                        strokeColor: Theme.accentCyan
                        strokeWidth: 10
                        capStyle: ShapePath.RoundCap
                        PathAngleArc {
                            centerX: parent.width / 2
                            centerY: parent.height / 2
                            radiusX: 75
                            radiusY: 75
                            startAngle: -210
                            sweepAngle: 240 * 0.88 // Fixed 88% charge from mockup
                        }
                    }
                }

                Column {
                    anchors.centerIn: parent
                    spacing: 4
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "88%"
                        color: Theme.textPrimary
                        font.pixelSize: 32
                        font.weight: Font.Bold
                        font.family: "Inter"
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: qsTr("Battery charge")
                        color: Theme.textSecondary
                        font.pixelSize: Theme.fontCaption
                        font.family: "Inter"
                    }
                }
            }

            // ── Center Panel: Live Speed & Road ADAS ──
            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignVCenter

                // Speed Circular Arc (No needle, matching mockup)
                Item {
                    id: speedArcArea
                    width: 240
                    height: 240
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 20

                    Shape {
                        anchors.fill: parent
                        layer.enabled: true
                        layer.samples: 4

                        // Base track
                        ShapePath {
                            fillColor: "transparent"
                            strokeColor: Theme.gaugeTrack
                            strokeWidth: 6
                            capStyle: ShapePath.RoundCap
                            PathAngleArc {
                                centerX: 120
                                centerY: 120
                                radiusX: 95
                                radiusY: 95
                                startAngle: -220
                                sweepAngle: 260
                            }
                        }

                        // Speed fill arc
                        ShapePath {
                            fillColor: "transparent"
                            strokeColor: Theme.accentCyan
                            strokeWidth: 8
                            capStyle: ShapePath.RoundCap
                            PathAngleArc {
                                centerX: 120
                                centerY: 120
                                radiusX: 95
                                radiusY: 95
                                startAngle: -220
                                sweepAngle: 260 * (speedViewModel.speed / speedViewModel.maxSpeed)
                            }
                        }
                    }

                    // Ticks around the speed gauge
                    Repeater {
                        model: 21
                        Item {
                            readonly property real angle: -220 + (index / 20) * 260
                            readonly property real rad: angle * Math.PI / 180
                            x: 120 + 82 * Math.cos(rad) - width / 2
                            y: 120 + 82 * Math.sin(rad) - height / 2
                            width: 2; height: 6

                            Rectangle {
                                anchors.fill: parent
                                color: index / 20 <= (speedViewModel.speed / speedViewModel.maxSpeed) ? Theme.accentCyan : Theme.textDim
                            }
                        }
                    }

                    // Center live speed display
                    Column {
                        anchors.centerIn: parent
                        spacing: 2
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: speedViewModel.speedText
                            color: Theme.textPrimary
                            font.pixelSize: 52
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: speedViewModel.unit.toUpperCase()
                            color: Theme.accentCyan
                            font.pixelSize: 12
                            font.weight: Font.Bold
                            font.family: "Inter"
                            font.letterSpacing: 1
                        }
                    }


                }

                // ADAS Road View
                Item {
                    id: roadView
                    width: 220
                    height: 140
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter

                    // Perspective Road Canvas
                    Canvas {
                        anchors.fill: parent
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.clearRect(0, 0, width, height)

                            // Road Polygon
                            var grad = ctx.createLinearGradient(width/2, 0, width/2, height)
                            grad.addColorStop(0, "#111625")
                            grad.addColorStop(1, "#182238")
                            ctx.fillStyle = grad
                            ctx.beginPath()
                            ctx.moveTo(width * 0.46, 0)
                            ctx.lineTo(width * 0.54, 0)
                            ctx.lineTo(width * 0.88, height)
                            ctx.lineTo(width * 0.12, height)
                            ctx.closePath()
                            ctx.fill()

                            // Side borders
                            ctx.strokeStyle = "#3A4B6E"
                            ctx.lineWidth = 3
                            ctx.beginPath()
                            ctx.moveTo(width * 0.46, 0)
                            ctx.lineTo(width * 0.12, height)
                            ctx.moveTo(width * 0.54, 0)
                            ctx.lineTo(width * 0.88, height)
                            ctx.stroke()

                            // Center dashed lane line
                            ctx.strokeStyle = "#FFFFFF"
                            ctx.lineWidth = 1.5
                            ctx.setLineDash([8, 12])
                            ctx.beginPath()
                            ctx.moveTo(width * 0.5, 0)
                            ctx.lineTo(width * 0.5, height)
                            ctx.stroke()
                        }
                    }

                    // Procedural white car driving on road
                    Item {
                        id: carIcon
                        width: 36
                        height: 56
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: 10

                        // Main Body
                        Rectangle {
                            anchors.fill: parent
                            color: "#FFFFFF"
                            radius: 8
                            border.width: 1.5
                            border.color: "#8FA3C7"
                        }
                        // Windshield
                        Rectangle {
                            width: 28
                            height: 14
                            anchors.top: parent.top
                            anchors.topMargin: 10
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#182238"
                            radius: 3
                        }
                        // Rear Window
                        Rectangle {
                            width: 28
                            height: 12
                            anchors.bottom: parent.bottom
                            anchors.bottomMargin: 8
                            anchors.horizontalCenter: parent.horizontalCenter
                            color: "#182238"
                            radius: 3
                        }
                        // Left tail light (Red)
                        Rectangle {
                            width: 6
                            height: 4
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            anchors.leftMargin: 4
                            color: "#FF3D57"
                            radius: 1
                        }
                        // Right tail light (Red)
                        Rectangle {
                            width: 6
                            height: 4
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            anchors.rightMargin: 4
                            color: "#FF3D57"
                            radius: 1
                        }
                        // Mirrors
                        Rectangle { width: 3; height: 6; x: -3; y: 18; color: "#FFFFFF"; radius: 1 }
                        Rectangle { width: 3; height: 6; x: parent.width; y: 18; color: "#FFFFFF"; radius: 1 }
                    }

                    // Circular Speed Limit / Range sign "228" below the car
                    Rectangle {
                        width: 44
                        height: 44
                        radius: 22
                        color: "#0B0F19"
                        border.width: 4
                        border.color: "#FF3D57"
                        anchors.bottom: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottomMargin: -16
                        z: 10

                        Text {
                            anchors.centerIn: parent
                            text: "228"
                            color: Theme.accentCyan
                            font.pixelSize: 13
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                    }
                }
            }

            // ── Right Panel: Trip Information ──
            ColumnLayout {
                Layout.preferredWidth: 200
                Layout.fillHeight: true
                spacing: Theme.spacingMd
                Layout.alignment: Qt.AlignVCenter

                // Distance Trip Row
                RowLayout {
                    spacing: Theme.spacingMd
                    Text {
                        text: "🛣"
                        color: Theme.accentCyan
                        font.pixelSize: 24
                    }
                    Column {
                        Text {
                            text: "188 KM"
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontTitle
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            text: qsTr("Distance")
                            color: Theme.textSecondary
                            font.pixelSize: Theme.fontCaption
                            font.family: "Inter"
                        }
                    }
                }

                // Fuel Consumption / MPG Row
                RowLayout {
                    spacing: Theme.spacingMd
                    Text {
                        text: "⛽"
                        color: Theme.accentCyan
                        font.pixelSize: 24
                    }
                    Column {
                        Text {
                            text: "34 mpg"
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontTitle
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            text: qsTr("Avg. Fuel Usage")
                            color: Theme.textSecondary
                            font.pixelSize: Theme.fontCaption
                            font.family: "Inter"
                        }
                    }
                }

                // Average Speed Row
                RowLayout {
                    spacing: Theme.spacingMd
                    Text {
                        text: "⏱"
                        color: Theme.accentCyan
                        font.pixelSize: 24
                    }
                    Column {
                        Text {
                            text: "78 mph"
                            color: Theme.textPrimary
                            font.pixelSize: Theme.fontTitle
                            font.weight: Font.Bold
                            font.family: "Inter"
                        }
                        Text {
                            text: qsTr("Avg. Speed")
                            color: Theme.textSecondary
                            font.pixelSize: Theme.fontCaption
                            font.family: "Inter"
                        }
                    }
                }
            }

            // ── Right Column: Safety Tell-tales ──
            Column {
                Layout.preferredWidth: 40
                Layout.fillHeight: true
                spacing: Theme.spacingMd
                Layout.alignment: Qt.AlignVCenter

                Repeater {
                    model: tellTaleViewModel
                    delegate: Loader {
                        active: index === 1 || index === 2 || index === 4
                        sourceComponent: TellTaleIndicator {
                            name: model.name
                            iconSource: model.iconSource
                            state: model.state
                            isActive: model.isActive
                            color: model.color
                            isBlinking: model.isBlinking
                        }
                    }
                }
            }
        }

        // ── Bottom Bar Info (Temp / Live stats / Dynamic Gear) ──────────────
        RowLayout {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: Theme.spacingLg
            height: 40

            // Left Side: Temp & horizontal progress bar + speed
            RowLayout {
                spacing: Theme.spacingMd
                Layout.alignment: Qt.AlignLeft

                Text {
                    text: "100.6 °F"
                    color: Theme.textPrimary
                    font.pixelSize: 13
                    font.weight: Font.DemiBold
                    font.family: "Inter"
                }

                Rectangle {
                    width: 60
                    height: 5
                    radius: 2
                    color: Theme.gaugeTrack

                    Rectangle {
                        width: parent.width * 0.6
                        height: parent.height
                        radius: parent.radius
                        color: Theme.accentCyan
                    }
                }

                Text {
                    text: speedViewModel.speedText + " " + speedViewModel.unit.toUpperCase()
                    color: Theme.textSecondary
                    font.pixelSize: 13
                    font.family: "Inter"
                }
            }

            Item { Layout.fillWidth: true }

            // Right Side: READY state + P R N D gear selector
            RowLayout {
                spacing: Theme.spacingSm
                Layout.alignment: Qt.AlignRight

                Text {
                    text: "READY"
                    color: Theme.accentGreen
                    font.pixelSize: 14
                    font.weight: Font.Bold
                    font.family: "Inter"
                    font.letterSpacing: 1
                }

                Item { Layout.preferredWidth: 8 }

                // P R N D Selector
                Row {
                    spacing: 12
                    Text {
                        text: "P"
                        color: (rpmViewModel.gear === 0 && speedViewModel.speed === 0) ? Theme.textPrimary : Theme.textDim
                        font.pixelSize: 14
                        font.weight: (rpmViewModel.gear === 0 && speedViewModel.speed === 0) ? Font.Bold : Font.Normal
                        font.family: "Inter"
                    }
                    Text {
                        text: "R"
                        color: rpmViewModel.gear === 9 ? Theme.textPrimary : Theme.textDim
                        font.pixelSize: 14
                        font.weight: rpmViewModel.gear === 9 ? Font.Bold : Font.Normal
                        font.family: "Inter"
                    }
                    Text {
                        text: "N"
                        color: (rpmViewModel.gear === 0 && speedViewModel.speed > 0) ? Theme.textPrimary : Theme.textDim
                        font.pixelSize: 14
                        font.weight: (rpmViewModel.gear === 0 && speedViewModel.speed > 0) ? Font.Bold : Font.Normal
                        font.family: "Inter"
                    }
                    Text {
                        text: "D"
                        color: (rpmViewModel.gear >= 1 && rpmViewModel.gear <= 8) ? Theme.textPrimary : Theme.textDim
                        font.pixelSize: 14
                        font.weight: (rpmViewModel.gear >= 1 && rpmViewModel.gear <= 8) ? Font.Bold : Font.Normal
                        font.family: "Inter"
                    }
                }
            }
        }
    }

    // ── Safe mode fallback ──────────────────────────────────────────────────
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

    // ── ADAS overlay ──
    AdasOverlay {
        anchors.fill: parent
    }
}
