import QtQuick
import HmiDashboard.Components

CircularGauge {
    id: root

    value: speedViewModel.speed
    minValue: 0
    maxValue: speedViewModel.maxSpeed
    startAngle: 135
    sweepAngle: 270
    tickCount: 14
    warningThreshold: 0.7
    dangerThreshold: 0.85
    label: speedViewModel.unit
    valueText: speedViewModel.speedText
    arcWidth: 10

    implicitWidth: 320
    implicitHeight: 320

    // Digital speed display glow
    Rectangle {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: gaugeRadius * 0.05
        width: 120
        height: 120
        radius: 60
        color: "transparent"
        border.width: 1
        border.color: Qt.rgba(0, 0.83, 1.0, 0.15)
    }

    // Unit toggle tap area
    TapHandler {
        onTapped: speedViewModel.toggleUnit()
    }
}
