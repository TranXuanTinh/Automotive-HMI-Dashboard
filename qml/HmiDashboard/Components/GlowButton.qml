import QtQuick 2.15
import QtQuick.Controls 2.15
import HmiDashboard 1.0

Button {
    id: root

    property color glowColor: Theme.accentCyan
    property color baseColor: Theme.surface
    property color textColor: Theme.textPrimary
    property real glowIntensity: 0.0
    property real borderRadius: Theme.radiusMd
    property bool isActive: false

    implicitWidth: 120
    implicitHeight: 44

    background: Rectangle {
        radius: root.borderRadius
        color: root.isActive ? Qt.darker(root.glowColor, 2.5) : root.baseColor
        border.width: 1
        border.color: root.isActive ? root.glowColor
                      : root.hovered ? Qt.lighter(Theme.surfaceBorder, 1.3)
                      : Theme.surfaceBorder

        // Glow rectangle
        Rectangle {
            anchors.fill: parent
            anchors.margins: -4
            radius: root.borderRadius + 4
            color: root.glowColor
            opacity: root.glowIntensity * 0.3
            visible: root.glowIntensity > 0.01
        }

        Behavior on border.color {
            ColorAnimation { duration: Theme.animFast }
        }

        Behavior on color {
            ColorAnimation { duration: Theme.animFast }
        }
    }

    contentItem: Text {
        text: root.text
        color: root.isActive ? root.glowColor : root.textColor
        font.pixelSize: Theme.fontBody
        font.family: "Inter"
        font.weight: root.isActive ? Font.DemiBold : Font.Normal
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        Behavior on color {
            ColorAnimation { duration: Theme.animFast }
        }
    }

    // Hover glow animation
    states: [
        State {
            name: "hovered"
            when: root.hovered && !root.pressed
            PropertyChanges { target: root; glowIntensity: 0.5 }
        },
        State {
            name: "pressed"
            when: root.pressed
            PropertyChanges { target: root; glowIntensity: 1.0 }
        }
    ]

    transitions: [
        Transition {
            to: "*"
            NumberAnimation {
                property: "glowIntensity"
                duration: Theme.animFast
                easing.type: Easing.OutQuad
            }
        }
    ]
}
