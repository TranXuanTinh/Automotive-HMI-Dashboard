#include "core/DataIntegrity.h"
#include <cstring>

namespace hmi {

// CRC-8 lookup table using SAE J1850 polynomial (0x1D)
const std::array<uint8_t, 256> DataIntegrity::s_crc8Table = [] {
    std::array<uint8_t, 256> table{};
    constexpr uint8_t poly = 0x1D;
    for (int i = 0; i < 256; ++i) {
        uint8_t crc = static_cast<uint8_t>(i);
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x80)
                crc = static_cast<uint8_t>((crc << 1) ^ poly);
            else
                crc = static_cast<uint8_t>(crc << 1);
        }
        table[static_cast<size_t>(i)] = crc;
    }
    return table;
}();

DataIntegrity::DataIntegrity() = default;

uint8_t DataIntegrity::computeCrc8(const uint8_t *data, size_t length)
{
    uint8_t crc = 0xFF; // initial value
    for (size_t i = 0; i < length; ++i) {
        crc = s_crc8Table[crc ^ data[i]];
    }
    return crc ^ 0xFF; // final XOR
}

bool DataIntegrity::checkAliveCounter(uint8_t received, uint8_t &expected)
{
    // Alive counter wraps at 15 (4-bit counter, common in CAN)
    constexpr uint8_t maxCounter = 15;

    if (received == expected) {
        expected = static_cast<uint8_t>((expected + 1) % (maxCounter + 1));
        return true;
    }

    // Allow one skipped frame (noise tolerance)
    uint8_t nextExpected = static_cast<uint8_t>((expected + 1) % (maxCounter + 1));
    if (received == nextExpected) {
        expected = static_cast<uint8_t>((received + 1) % (maxCounter + 1));
        return true;
    }

    // Counter is out of sequence — reject
    expected = static_cast<uint8_t>((received + 1) % (maxCounter + 1));
    return false;
}

bool DataIntegrity::validateSpeed(const SpeedData &data)
{
    // Verify CRC-8 over the payload (speed value bytes)
    uint8_t payload[8];
    std::memcpy(payload, &data.kmh, sizeof(data.kmh));
    uint8_t computed = computeCrc8(payload, sizeof(data.kmh));

    if (computed != data.checksum) {
        ++m_invalidFrames;
        return false;
    }

    // Verify alive counter sequence
    if (m_firstSpeedFrame) {
        m_expectedSpeedAlive = static_cast<uint8_t>((data.aliveCounter + 1) % 16);
        m_firstSpeedFrame = false;
        ++m_validFrames;
        return true;
    }

    if (!checkAliveCounter(data.aliveCounter, m_expectedSpeedAlive)) {
        ++m_invalidFrames;
        return false;
    }

    ++m_validFrames;
    return true;
}

bool DataIntegrity::validateRpm(const RpmData &data)
{
    uint8_t payload[9];
    std::memcpy(payload, &data.rpm, sizeof(data.rpm));
    payload[sizeof(data.rpm)] = data.gear;
    uint8_t computed = computeCrc8(payload, sizeof(data.rpm) + 1);

    if (computed != data.checksum) {
        ++m_invalidFrames;
        return false;
    }

    if (m_firstRpmFrame) {
        m_expectedRpmAlive = static_cast<uint8_t>((data.aliveCounter + 1) % 16);
        m_firstRpmFrame = false;
        ++m_validFrames;
        return true;
    }

    if (!checkAliveCounter(data.aliveCounter, m_expectedRpmAlive)) {
        ++m_invalidFrames;
        return false;
    }

    ++m_validFrames;
    return true;
}

bool DataIntegrity::validateTellTale(const TellTaleEvent &event)
{
    uint8_t payload[2];
    payload[0] = static_cast<uint8_t>(event.id);
    payload[1] = static_cast<uint8_t>(event.state);
    uint8_t computed = computeCrc8(payload, 2);

    if (computed != event.checksum) {
        ++m_invalidFrames;
        return false;
    }

    if (m_firstTellTaleFrame) {
        m_expectedTellTaleAlive = static_cast<uint8_t>((event.aliveCounter + 1) % 16);
        m_firstTellTaleFrame = false;
        ++m_validFrames;
        return true;
    }

    if (!checkAliveCounter(event.aliveCounter, m_expectedTellTaleAlive)) {
        ++m_invalidFrames;
        return false;
    }

    ++m_validFrames;
    return true;
}

void DataIntegrity::reset()
{
    m_expectedSpeedAlive = 0;
    m_expectedRpmAlive = 0;
    m_expectedTellTaleAlive = 0;
    m_firstSpeedFrame = true;
    m_firstRpmFrame = true;
    m_firstTellTaleFrame = true;
    m_validFrames = 0;
    m_invalidFrames = 0;
}

} // namespace hmi
