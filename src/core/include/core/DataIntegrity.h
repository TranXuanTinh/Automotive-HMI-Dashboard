#ifndef CORE_DATAINTEGRITY_H
#define CORE_DATAINTEGRITY_H

#include <cstdint>
#include <array>
#include "VehicleData.h"

namespace hmi {

/// ISO 26262 data integrity validation for incoming CAN bus signals.
/// Provides CRC-8 checksum verification, alive-counter sequence checking,
/// and timeout detection for missing signals.
class DataIntegrity
{
public:
    DataIntegrity();

    /// Validate a speed data frame. Returns true if checksum and alive-counter are valid.
    bool validateSpeed(const SpeedData &data);

    /// Validate an RPM data frame.
    bool validateRpm(const RpmData &data);

    /// Validate a tell-tale event.
    bool validateTellTale(const TellTaleEvent &event);

    /// Compute CRC-8 checksum over a byte buffer (SAE J1850 polynomial).
    static uint8_t computeCrc8(const uint8_t *data, size_t length);

    /// Reset all internal counters (e.g. on bus restart).
    void reset();

    /// Statistics
    uint64_t validFrames() const { return m_validFrames; }
    uint64_t invalidFrames() const { return m_invalidFrames; }

private:
    bool checkAliveCounter(uint8_t received, uint8_t &expected);

    uint8_t  m_expectedSpeedAlive    = 0;
    uint8_t  m_expectedRpmAlive      = 0;
    uint8_t  m_expectedTellTaleAlive = 0;
    bool     m_firstSpeedFrame       = true;
    bool     m_firstRpmFrame         = true;
    bool     m_firstTellTaleFrame    = true;
    uint64_t m_validFrames           = 0;
    uint64_t m_invalidFrames         = 0;

    static const std::array<uint8_t, 256> s_crc8Table;
};

} // namespace hmi

#endif // CORE_DATAINTEGRITY_H
