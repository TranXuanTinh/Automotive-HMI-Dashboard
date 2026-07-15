import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import HmiDashboard.Cluster
import HmiDashboard.Infotainment

Window {
    id: root

    width: 1920
    height: 720
    visible: true
    color: Theme.background
    title: qsTr("Automotive HMI Dashboard")

    // Fullscreen on start
    visibility: Window.FullScreen

    // ── Ambient light strip (top + bottom) ──────────────────────────────
    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 2
        color: dashboardState.accentColor
        opacity: 0.6
        z: 10

        Behavior on color {
            ColorAnimation { duration: Theme.animNormal }
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 2
        color: dashboardState.accentColor
        opacity: 0.4
        z: 10

        Behavior on color {
            ColorAnimation { duration: Theme.animNormal }
        }
    }

    // ── Main layout: Cluster | Divider | Infotainment ───────────────────
    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ── Instrument Cluster (ASIL B/C) ───────────────────────────────
        InstrumentCluster {
            Layout.fillHeight: true
            Layout.preferredWidth: root.width * dashboardState.clusterWidthRatio

            Behavior on Layout.preferredWidth {
                NumberAnimation {
                    duration: Theme.animSlow
                    easing.type: Easing.InOutQuad
                }
            }
        }

        // ── Vertical divider ────────────────────────────────────────────
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 1
            color: Theme.surfaceBorder
            visible: dashboardState.isInfotainmentVisible
        }

        // ── Infotainment (QM) ───────────────────────────────────────────
        InfotainmentPanel {
            Layout.fillHeight: true
            Layout.fillWidth: true
            visible: dashboardState.isInfotainmentVisible

            Behavior on opacity {
                OpacityAnimator {
                    duration: Theme.animNormal
                }
            }
        }
    }

    // ── Mode indicator badge ────────────────────────────────────────────
    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: Theme.spacingSm
        width: modeBadgeText.width + Theme.spacingLg
        height: 28
        radius: 14
        color: Qt.rgba(0, 0, 0, 0.5)
        border.width: 1
        border.color: dashboardState.accentColor
        z: 10

        Text {
            id: modeBadgeText
            anchors.centerIn: parent
            text: dashboardState.currentState.toUpperCase()
            color: dashboardState.accentColor
            font.pixelSize: Theme.fontCaption
            font.weight: Font.DemiBold
            font.family: "Inter"
            font.letterSpacing: 2
        }

        Behavior on border.color {
            ColorAnimation { duration: Theme.animNormal }
        }
    }

    // ── Escape to exit fullscreen ───────────────────────────────────────
    Shortcut {
        sequence: "Escape"
        onActivated: {
            if (root.visibility === Window.FullScreen)
                root.visibility = Window.Windowed
            else
                Qt.quit()
        }
    }
}
