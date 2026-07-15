import QtQuick 2.15
import HmiDashboard 1.0

Item {
    id: root

    implicitWidth: parent ? parent.width : 400
    implicitHeight: parent ? parent.height : 300

    // ── ADAS bounding box overlay ───────────────────────────────────────
    Repeater {
        model: adasViewModel

        Item {
            id: detection

            required property double boxX
            required property double boxY
            required property double boxWidth
            required property double boxHeight
            required property string className
            required property double confidence
            required property int trackId
            required property color boxColor

            x: boxX * root.width
            y: boxY * root.height
            width: boxWidth * root.width
            height: boxHeight * root.height

            Behavior on x { NumberAnimation { duration: Theme.animFast; easing.type: Easing.OutQuad } }
            Behavior on y { NumberAnimation { duration: Theme.animFast; easing.type: Easing.OutQuad } }
            Behavior on width { NumberAnimation { duration: Theme.animFast; easing.type: Easing.OutQuad } }
            Behavior on height { NumberAnimation { duration: Theme.animFast; easing.type: Easing.OutQuad } }

            // Bounding box rectangle
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.width: 2
                border.color: detection.boxColor
                radius: 4
            }

            // Class label badge
            Rectangle {
                anchors.bottom: parent.top
                anchors.left: parent.left
                anchors.bottomMargin: 2
                height: 18
                width: labelText.width + 12
                radius: 4
                color: Qt.rgba(
                           detection.boxColor.r,
                           detection.boxColor.g,
                           detection.boxColor.b, 0.85)

                Text {
                    id: labelText
                    anchors.centerIn: parent
                    text: detection.className + " " +
                          Math.round(detection.confidence * 100) + "%"
                    color: "#FFFFFF"
                    font.pixelSize: 10
                    font.weight: Font.DemiBold
                    font.family: "Inter"
                }
            }

            // Corner marks for a more technical look
            Repeater {
                model: 4  // four corners
                Rectangle {
                    required property int index
                    width: 8
                    height: 2
                    color: detection.boxColor
                    x: (index % 2 === 0) ? 0 : detection.width - width
                    y: (index < 2) ? 0 : detection.height - height
                }
            }
            Repeater {
                model: 4
                Rectangle {
                    required property int index
                    width: 2
                    height: 8
                    color: detection.boxColor
                    x: (index % 2 === 0) ? 0 : detection.width - width
                    y: (index < 2) ? 0 : detection.height - height
                }
            }
        }
    }

    // ── Object count badge ──────────────────────────────────────────────
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: Theme.spacingSm
        width: countText.width + Theme.spacingMd
        height: 24
        radius: 12
        color: Qt.rgba(0, 0, 0, 0.6)
        border.width: 1
        border.color: Theme.accentCyan

        Text {
            id: countText
            anchors.centerIn: parent
            text: qsTr("ADAS: %1 objects").arg(adasViewModel.objectCount)
            color: Theme.accentCyan
            font.pixelSize: Theme.fontCaption
            font.family: "Inter"
            font.weight: Font.DemiBold
        }
    }
}
