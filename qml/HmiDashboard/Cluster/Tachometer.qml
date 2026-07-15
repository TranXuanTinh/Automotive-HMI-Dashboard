import QtQuick 2.15
import "../Components"
import HmiDashboard 1.0

Item {
    id: root

    implicitWidth: 260
    implicitHeight: 260

    CircularGauge {
        id: gauge
        anchors.fill: parent

        value: rpmViewModel.rpm
        minValue: 0
        maxValue: rpmViewModel.maxRpm
        startAngle: 135
        sweepAngle: 270
        tickCount: 8
        warningThreshold: rpmViewModel.redlineRpm / rpmViewModel.maxRpm - 0.1
        dangerThreshold: rpmViewModel.redlineRpm / rpmViewModel.maxRpm
        label: "RPM"
        valueText: rpmViewModel.rpmText
        arcWidth: 8
        safeColor: dashboardState.accentColor
    }

    // ── Gear indicator ──────────────────────────────────────────────────
    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        width: 56
        height: 56
        radius: Theme.radiusMd
        color: Theme.surface
        border.width: 1
        border.color: Theme.surfaceBorder

        Text {
            anchors.centerIn: parent
            text: rpmViewModel.gearText
            color: dashboardState.accentColor
            font.pixelSize: Theme.fontHeading
            font.weight: Font.Bold
            font.family: "Inter"

            Behavior on color {
                ColorAnimation { duration: Theme.animNormal }
            }
        }
    }
}
