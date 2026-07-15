import QtQuick 2.15
import HmiDashboard 1.0

Item {
    id: root

    required property string name
    required property string iconSource
    required property int state   // 0=Off, 1=On, 2=Blinking, 3=Error
    required property bool isActive
    required property color color
    required property bool isBlinking

    implicitWidth: 36
    implicitHeight: 46

    opacity: root.isActive ? 1.0 : 0.2

    Behavior on opacity {
        OpacityAnimator { duration: Theme.animFast }
    }

    // ── Blinking animation ──────────────────────────────────────────────
    SequentialAnimation on opacity {
        id: blinkAnim
        running: root.isBlinking
        loops: Animation.Infinite
        NumberAnimation { to: 1.0; duration: 400 }
        NumberAnimation { to: 0.15; duration: 400 }
    }

    Column {
        anchors.fill: parent
        spacing: 2

        // ── Icon circle ─────────────────────────────────────────────────
        Rectangle {
            width: 32
            height: 32
            radius: 16
            anchors.horizontalCenter: parent.horizontalCenter
            color: root.isActive ? Qt.rgba(
                       root.color.r,
                       root.color.g,
                       root.color.b, 0.2)
                   : "transparent"
            border.width: 1
            border.color: root.isActive ? root.color : Theme.textDim

            Text {
                anchors.centerIn: parent
                text: {
                    // Unicode symbols for tell-tales
                    switch (root.iconSource) {
                    case "engine":     return "⚙"
                    case "abs":        return "◎"
                    case "tire":       return "◉"
                    case "seatbelt":   return "⊘"
                    case "brake":      return "⊛"
                    case "highbeam":   return "◈"
                    case "turn_left":  return "◀"
                    case "turn_right": return "▶"
                    case "battery":    return "⊞"
                    case "oil":        return "◆"
                    case "temperature":return "◇"
                    case "door":       return "▣"
                    case "airbag":     return "⊕"
                    case "traction":   return "◐"
                    default:           return "⚠"
                    }
                }
                color: root.isActive ? root.color : Theme.textDim
                font.pixelSize: 16
            }

            Behavior on color {
                ColorAnimation { duration: Theme.animFast }
            }
            Behavior on border.color {
                ColorAnimation { duration: Theme.animFast }
            }
        }

        // ── Label ───────────────────────────────────────────────────────
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: root.name
            color: root.isActive ? Theme.textSecondary : Theme.textDim
            font.pixelSize: 8
            font.family: "Inter"
            width: root.width
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideRight
        }
    }
}
