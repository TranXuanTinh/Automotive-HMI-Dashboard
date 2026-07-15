import QtQuick
import QtQuick.Layouts
import HmiDashboard.Components

Item {
    id: root

    ColumnLayout {
        anchors.fill: parent
        spacing: Theme.spacingLg

        // ── Album art area ──────────────────────────────────────────────
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            // Album art placeholder with gradient
            Rectangle {
                id: albumArt
                anchors.centerIn: parent
                width: Math.min(parent.width * 0.5, parent.height * 0.7)
                height: width
                radius: Theme.radiusLg
                color: Theme.surface

                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.darker(dashboardState.accentColor, 3) }
                    GradientStop { position: 1.0; color: Theme.surface }
                }

                // Vinyl record effect
                Rectangle {
                    anchors.centerIn: parent
                    width: parent.width * 0.85
                    height: width
                    radius: width / 2
                    color: "transparent"
                    border.width: 1
                    border.color: Qt.rgba(1, 1, 1, 0.1)

                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width * 0.3
                        height: width
                        radius: width / 2
                        color: Qt.rgba(1, 1, 1, 0.05)
                    }

                    RotationAnimator on rotation {
                        running: mediaViewModel.isPlaying
                        from: 0
                        to: 360
                        duration: 8000
                        loops: Animation.Infinite
                    }
                }

                // Music note icon
                Text {
                    anchors.centerIn: parent
                    text: "♫"
                    color: Qt.rgba(1, 1, 1, 0.3)
                    font.pixelSize: parent.width * 0.25
                }
            }

            // ── Track info overlay ──────────────────────────────────────
            Column {
                anchors.left: albumArt.right
                anchors.leftMargin: Theme.spacingLg
                anchors.verticalCenter: albumArt.verticalCenter
                anchors.right: parent.right
                spacing: Theme.spacingSm

                Text {
                    width: parent.width
                    text: mediaViewModel.title
                    color: Theme.textPrimary
                    font.pixelSize: Theme.fontTitle
                    font.weight: Font.Bold
                    font.family: "Inter"
                    elide: Text.ElideRight
                }

                Text {
                    width: parent.width
                    text: mediaViewModel.artist
                    color: Theme.textSecondary
                    font.pixelSize: Theme.fontBody
                    font.family: "Inter"
                    elide: Text.ElideRight
                }

                Text {
                    width: parent.width
                    text: mediaViewModel.album
                    color: Theme.textDim
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                    elide: Text.ElideRight
                }
            }
        }

        // ── Progress bar ────────────────────────────────────────────────
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            // Seekable progress bar
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 20

                GradientBar {
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width
                    value: mediaViewModel.progress
                    maxValue: 1.0
                    barColor: dashboardState.accentColor
                    barHeight: 4
                }

                // Seek handle
                Rectangle {
                    x: parent.width * mediaViewModel.progress - 6
                    anchors.verticalCenter: parent.verticalCenter
                    width: 12
                    height: 12
                    radius: 6
                    color: dashboardState.accentColor
                    visible: mediaViewModel.isPlaying || mediaViewModel.progress > 0

                    Behavior on x {
                        NumberAnimation { duration: 50 }
                    }
                }

                TapHandler {
                    onTapped: function(eventPoint) {
                        var progress = eventPoint.position.x / parent.width
                        mediaViewModel.seek(Math.max(0, Math.min(1, progress)))
                    }
                }
            }

            // Time labels
            RowLayout {
                Layout.fillWidth: true
                Text {
                    text: mediaViewModel.positionText
                    color: Theme.textSecondary
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                }
                Item { Layout.fillWidth: true }
                Text {
                    text: mediaViewModel.durationText
                    color: Theme.textSecondary
                    font.pixelSize: Theme.fontCaption
                    font.family: "Inter"
                }
            }
        }

        // ── Playback controls ───────────────────────────────────────────
        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: Theme.spacingLg

            GlowButton {
                text: "⏮"
                width: 48; height: 48
                borderRadius: 24
                glowColor: dashboardState.accentColor
                onClicked: mediaViewModel.previous()
            }

            // Play/Pause — larger
            GlowButton {
                text: mediaViewModel.isPlaying ? "⏸" : "▶"
                width: 64; height: 64
                borderRadius: 32
                glowColor: dashboardState.accentColor
                isActive: mediaViewModel.isPlaying
                onClicked: mediaViewModel.togglePlayPause()
            }

            GlowButton {
                text: "⏭"
                width: 48; height: 48
                borderRadius: 24
                glowColor: dashboardState.accentColor
                onClicked: mediaViewModel.next()
            }
        }
    }
}
