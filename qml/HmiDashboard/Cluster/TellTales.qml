import QtQuick 2.15
import HmiDashboard 1.0

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

            Item {
                id: delegateItem
                width: 36
                height: 46

                required property string name
                required property string iconSource
                required property int state
                required property bool isActive
                required property color color
                required property bool isBlinking

                TellTaleIndicator {
                    name: delegateItem.name
                    iconSource: delegateItem.iconSource
                    state: delegateItem.state
                    isActive: delegateItem.isActive
                    color: delegateItem.color
                    isBlinking: delegateItem.isBlinking
                }
            }
        }
    }
}
