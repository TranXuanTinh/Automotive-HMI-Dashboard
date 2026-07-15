import QtQuick
import QtQuick.Shapes

Item {
    id: root

    // ── Public API ──────────────────────────────────────────────────────
    property real value: 0
    property real minValue: 0
    property real maxValue: 280
    property real startAngle: 135
    property real sweepAngle: 270
    property int tickCount: 10
    property real warningThreshold: 0.75
    property real dangerThreshold: 0.9
    property color safeColor: Theme.gaugeSafe
    property color warningColor: Theme.gaugeWarning
    property color dangerColor: Theme.gaugeDanger
    property color trackColor: Theme.gaugeTrack
    property color needleColor: Theme.needleColor
    property real arcWidth: 8
    property real needleWidth: 3
    property string label: ""
    property string valueText: ""

    implicitWidth: 280
    implicitHeight: 280

    readonly property real normalizedValue: (value - minValue) / (maxValue - minValue)
    readonly property real centerX: width / 2
    readonly property real centerY: height / 2
    readonly property real gaugeRadius: Math.min(width, height) / 2 - arcWidth - 10

    // ── Background track arc ────────────────────────────────────────────
    Shape {
        anchors.fill: parent
        layer.enabled: true
        layer.samples: 4

        ShapePath {
            fillColor: "transparent"
            strokeColor: root.trackColor
            strokeWidth: root.arcWidth
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: root.centerX
                centerY: root.centerY
                radiusX: root.gaugeRadius
                radiusY: root.gaugeRadius
                startAngle: root.startAngle - 90
                sweepAngle: root.sweepAngle
            }
        }

        // ── Active value arc ────────────────────────────────────────────
        ShapePath {
            fillColor: "transparent"
            strokeColor: root.normalizedValue >= root.dangerThreshold
                         ? root.dangerColor
                         : root.normalizedValue >= root.warningThreshold
                           ? root.warningColor
                           : root.safeColor
            strokeWidth: root.arcWidth + 2
            capStyle: ShapePath.RoundCap

            PathAngleArc {
                centerX: root.centerX
                centerY: root.centerY
                radiusX: root.gaugeRadius
                radiusY: root.gaugeRadius
                startAngle: root.startAngle - 90
                sweepAngle: root.normalizedValue * root.sweepAngle
            }
        }
    }

    // ── Tick marks ──────────────────────────────────────────────────────
    Repeater {
        model: root.tickCount + 1

        Item {
            required property int index

            readonly property real tickAngle: root.startAngle + (index / root.tickCount) * root.sweepAngle
            readonly property real rad: tickAngle * Math.PI / 180
            readonly property bool isMajor: index % 2 === 0
            readonly property real innerR: root.gaugeRadius - (isMajor ? 18 : 12)
            readonly property real outerR: root.gaugeRadius - 4

            Rectangle {
                width: isMajor ? 2 : 1
                height: isMajor ? 14 : 8
                color: Theme.textDim
                x: root.centerX + innerR * Math.cos(rad) - width / 2
                y: root.centerY + innerR * Math.sin(rad) - height / 2
                rotation: tickAngle + 90
                antialiasing: true
            }

            // Tick labels for major ticks
            Text {
                visible: isMajor
                text: Math.round(root.minValue + (index / root.tickCount) * (root.maxValue - root.minValue))
                color: Theme.textDim
                font.pixelSize: Theme.fontCaption
                font.family: "Inter"
                x: root.centerX + (innerR - 16) * Math.cos(rad) - width / 2
                y: root.centerY + (innerR - 16) * Math.sin(rad) - height / 2
            }
        }
    }

    // ── Needle ──────────────────────────────────────────────────────────
    Rectangle {
        id: needle
        width: root.needleWidth
        height: root.gaugeRadius - 20
        color: root.needleColor
        radius: root.needleWidth / 2
        antialiasing: true
        x: root.centerX - width / 2
        y: root.centerY - height + 10
        transformOrigin: Item.Bottom

        rotation: root.startAngle + root.normalizedValue * root.sweepAngle

        Behavior on rotation {
            RotationAnimator {
                duration: Theme.animNormal
                easing.type: Easing.OutQuad
            }
        }

        // Glow effect on needle
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            color: root.normalizedValue >= root.dangerThreshold
                   ? root.dangerColor
                   : root.normalizedValue >= root.warningThreshold
                     ? root.warningColor
                     : root.safeColor
            opacity: 0.6
            scale: 2.5
            visible: root.normalizedValue > 0.01
        }
    }

    // ── Center hub ──────────────────────────────────────────────────────
    Rectangle {
        width: 16
        height: 16
        radius: 8
        color: Theme.textPrimary
        anchors.centerIn: parent

        Rectangle {
            width: 8
            height: 8
            radius: 4
            color: Theme.background
            anchors.centerIn: parent
        }
    }

    // ── Value display ───────────────────────────────────────────────────
    Column {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: root.gaugeRadius * 0.3
        spacing: 2

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.valueText
            color: Theme.textPrimary
            font.pixelSize: Theme.fontDisplay
            font.weight: Font.Bold
            font.family: "Inter"
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.label
            color: Theme.textSecondary
            font.pixelSize: Theme.fontCaption
            font.family: "Inter"
            font.letterSpacing: 2
        }
    }
}
