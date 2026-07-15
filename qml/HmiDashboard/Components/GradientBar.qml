import QtQuick
import QtQuick.Shapes

Item {
    id: root

    property real value: 0.0
    property real maxValue: 1.0
    property color barColor: Theme.accentCyan
    property color trackColor: Theme.gaugeTrack
    property real barHeight: 6

    implicitWidth: 200
    implicitHeight: barHeight + 4

    Rectangle {
        id: track
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: root.barHeight
        radius: root.barHeight / 2
        color: root.trackColor
    }

    Rectangle {
        id: fill
        anchors.verticalCenter: parent.verticalCenter
        width: Math.max(root.barHeight, parent.width * (root.value / root.maxValue))
        height: root.barHeight
        radius: root.barHeight / 2
        color: root.barColor

        Behavior on width {
            NumberAnimation { duration: Theme.animNormal; easing.type: Easing.OutQuad }
        }

        // Gradient shine effect
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.7; color: Qt.lighter(root.barColor, 1.3) }
                GradientStop { position: 1.0; color: root.barColor }
            }
            opacity: 0.5
        }
    }
}
