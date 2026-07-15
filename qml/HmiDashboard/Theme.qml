pragma Singleton
import QtQuick 2.15

QtObject {
    // ── Colors ──────────────────────────────────────────────────────────
    readonly property color background:       "#0A0E17"
    readonly property color backgroundLight:  "#131A2B"
    readonly property color surface:          "#1A2236"
    readonly property color surfaceLight:     "#243048"
    readonly property color surfaceBorder:    "#2A3654"

    readonly property color accentCyan:       "#00D4FF"
    readonly property color accentGreen:      "#00E676"
    readonly property color warningAmber:     "#FFB800"
    readonly property color dangerRed:        "#FF3D57"
    readonly property color infoPurple:       "#B388FF"

    readonly property color textPrimary:      "#FFFFFF"
    readonly property color textSecondary:    "#8899B4"
    readonly property color textDim:          "#4A5568"

    // ── Gauge-specific colors ───────────────────────────────────────────
    readonly property color gaugeSafe:        "#00E676"
    readonly property color gaugeWarning:     "#FFB800"
    readonly property color gaugeDanger:      "#FF3D57"
    readonly property color gaugeBackground:  "#1A2236"
    readonly property color gaugeTrack:       "#2A3654"
    readonly property color needleColor:      "#FFFFFF"

    // ── ADAS bounding box colors ────────────────────────────────────────
    readonly property color adasVehicle:      "#00E676"
    readonly property color adasPedestrian:   "#FFD740"
    readonly property color adasCyclist:      "#FF6E40"
    readonly property color adasSign:         "#448AFF"

    // ── Spacing ─────────────────────────────────────────────────────────
    readonly property int spacingXs:  4
    readonly property int spacingSm:  8
    readonly property int spacingMd:  16
    readonly property int spacingLg:  24
    readonly property int spacingXl:  32
    readonly property int spacingXxl: 48

    // ── Border radius ───────────────────────────────────────────────────
    readonly property int radiusSm:   8
    readonly property int radiusMd:   12
    readonly property int radiusLg:   16
    readonly property int radiusXl:   24
    readonly property int radiusFull: 999

    // ── Font sizes ──────────────────────────────────────────────────────
    readonly property int fontCaption:  11
    readonly property int fontBody:     14
    readonly property int fontTitle:    18
    readonly property int fontHeading:  24
    readonly property int fontDisplay:  36
    readonly property int fontHero:     64
    readonly property int fontGauge:    80

    // ── Glassmorphism ───────────────────────────────────────────────────
    readonly property real glassOpacity: 0.15
    readonly property int  glassBlur:    20

    // ── Animation durations ─────────────────────────────────────────────
    readonly property int animFast:     150
    readonly property int animNormal:   300
    readonly property int animSlow:     500
    readonly property int animVerySlow: 800
}
