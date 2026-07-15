import QtQuick
import QtQuick.Layouts
import HmiDashboard.Components

Item {
    id: root

    Rectangle {
        anchors.fill: parent
        color: Theme.background
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Theme.spacingMd
        spacing: 0

        // ── Tab header ──────────────────────────────────────────────────
        Row {
            Layout.fillWidth: true
            Layout.preferredHeight: 44
            spacing: Theme.spacingSm

            Repeater {
                model: [
                    { text: qsTr("Climate"), icon: "❄" },
                    { text: qsTr("Media"),   icon: "♫" },
                    { text: qsTr("Vehicle"), icon: "⚙" }
                ]

                GlowButton {
                    required property int index
                    required property var modelData
                    text: modelData.icon + " " + modelData.text
                    isActive: tabStack.currentIndex === index
                    glowColor: dashboardState.accentColor
                    width: (root.width - Theme.spacingMd * 2 - Theme.spacingSm * 2) / 3

                    onClicked: tabStack.currentIndex = index
                }
            }
        }

        Item { Layout.preferredHeight: Theme.spacingMd }

        // ── Content stack ───────────────────────────────────────────────
        StackLayout {
            id: tabStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: 0

            HvacPanel {}
            MediaPlayer {}
            VehicleSettings {}
        }
    }
}
