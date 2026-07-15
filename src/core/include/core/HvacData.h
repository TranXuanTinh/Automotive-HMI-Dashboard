#ifndef CORE_HVACDATA_H
#define CORE_HVACDATA_H

#include <cstdint>
#include <QMetaType>

namespace hmi {

// ── Airflow distribution mode ───────────────────────────────────────────
enum class AirflowMode : uint8_t {
    Face = 0,
    Feet,
    FaceAndFeet,
    Defrost,
    DefrostAndFeet
};

// ── Complete HVAC zone state ────────────────────────────────────────────
struct HvacState {
    double      driverTemp     = 22.0;   // °C
    double      passengerTemp  = 22.0;   // °C
    int         fanSpeed       = 3;      // 0–7
    bool        isAcOn         = false;
    bool        isRecircOn     = false;
    bool        isSyncOn       = false;  // sync driver/passenger
    AirflowMode airflowMode    = AirflowMode::Face;
};

} // namespace hmi

Q_DECLARE_METATYPE(hmi::HvacState)
Q_DECLARE_METATYPE(hmi::AirflowMode)

#endif // CORE_HVACDATA_H
