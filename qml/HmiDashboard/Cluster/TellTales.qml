import QtQuick

Item {
    id: root

    implicitWidth: 500
    implicitHeight: 60

    Rectangle {
        anchors.fill: parent
        color: Theme.surface
        radius: Theme.radiusMd
        opacity: 0.5
    }

    // ── Tell-tale grid ──────────────────────────────────────────────────
    Row {
        anchors.centerIn: parent
        spacing: Theme.spacingSm

        Repeater {
            model: tellTaleViewModel

            TellTaleIndicator {
                required property int index
                required property string name
                required property string iconSource
                required property int state
                required property bool isActive
                required property string color
                required property bool isBlinking
            }
        }
    }
}
