#ifndef CORE_VEHICLEDATA_H
#define CORE_VEHICLEDATA_H

#include <cstdint>
#include <QMetaType>

namespace hmi {

// ── Tell-tale identifiers (safety-critical warning indicators) ──────────
enum class TellTaleId : uint8_t {
    CheckEngine = 0,
    ABS,
    TirePressure,
    Seatbelt,
    BrakeWarning,
    HighBeam,
    TurnSignalLeft,
    TurnSignalRight,
    Battery,
    OilPressure,
    Temperature,
    DoorAjar,
    Airbag,
    TractionControl,
    Count  // sentinel – must be last
};

// ── Tell-tale visual state ──────────────────────────────────────────────
enum class TellTaleState : uint8_t {
    Off = 0,
    On,
    Blinking,
    Error
};

// ── Raw speed frame from CAN bus ────────────────────────────────────────
struct SpeedData {
    double   kmh          = 0.0;
    uint8_t  checksum     = 0;
    uint8_t  aliveCounter = 0;
};

// ── Raw RPM frame from CAN bus ──────────────────────────────────────────
struct RpmData {
    double   rpm          = 0.0;
    uint8_t  gear         = 0;   // 0 = neutral/park, 1–8 = forward gears, 9 = reverse
    uint8_t  checksum     = 0;
    uint8_t  aliveCounter = 0;
};

// ── Tell-tale change event ──────────────────────────────────────────────
struct TellTaleEvent {
    TellTaleId    id    = TellTaleId::CheckEngine;
    TellTaleState state = TellTaleState::Off;
    uint8_t       checksum     = 0;
    uint8_t       aliveCounter = 0;
};

} // namespace hmi

Q_DECLARE_METATYPE(hmi::SpeedData)
Q_DECLARE_METATYPE(hmi::RpmData)
Q_DECLARE_METATYPE(hmi::TellTaleEvent)
Q_DECLARE_METATYPE(hmi::TellTaleId)
Q_DECLARE_METATYPE(hmi::TellTaleState)

#endif // CORE_VEHICLEDATA_H
