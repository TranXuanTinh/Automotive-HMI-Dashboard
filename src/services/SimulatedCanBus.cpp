#include "SimulatedCanBus.h"
#include <cstring>
#include <cmath>
#include <QDebug>

namespace hmi {

SimulatedCanBus::SimulatedCanBus(QObject *parent)
    : IVehicleBus(parent)
{
    m_frameTimer.setInterval(20);       // 50 Hz — well under the 50ms latency requirement
    m_tellTaleTimer.setInterval(2000);  // tell-tale state changes every 2s

    connect(&m_frameTimer, &QTimer::timeout, this, &SimulatedCanBus::generateFrame);
    connect(&m_tellTaleTimer, &QTimer::timeout, this, &SimulatedCanBus::generateTellTaleEvent);
}

SimulatedCanBus::~SimulatedCanBus()
{
    stop();
}

void SimulatedCanBus::start()
{
    if (m_running.exchange(true))
        return;

    m_currentSpeed = 0.0;
    m_targetSpeed = 80.0;
    m_speedAliveCounter = 0;
    m_rpmAliveCounter = 0;
    m_tellTaleAliveCounter = 0;
    m_cycleCount = 0;

    m_frameTimer.start();
    m_tellTaleTimer.start();
    qDebug() << "[SimulatedCanBus] Started — 50Hz frame generation";
}

void SimulatedCanBus::stop()
{
    if (!m_running.exchange(false))
        return;

    m_frameTimer.stop();
    m_tellTaleTimer.stop();
    qDebug() << "[SimulatedCanBus] Stopped";
}

bool SimulatedCanBus::isRunning() const
{
    return m_running.load();
}

void SimulatedCanBus::generateFrame()
{
    ++m_cycleCount;

    // Simulate driving pattern: accelerate → cruise → decelerate → repeat
    if (m_cycleCount % 500 == 0) {
        // Every 10 seconds, pick a new random target speed
        m_targetSpeed = QRandomGenerator::global()->bounded(20, 220);
        m_acceleration = QRandomGenerator::global()->bounded(5, 30) / 10.0;
    }

    // Smoothly approach target speed
    if (m_currentSpeed < m_targetSpeed) {
        m_currentSpeed = std::min(m_currentSpeed + m_acceleration, m_targetSpeed);
    } else if (m_currentSpeed > m_targetSpeed) {
        m_currentSpeed = std::max(m_currentSpeed - m_acceleration * 1.5, m_targetSpeed);
    }

    m_currentSpeed = std::clamp(m_currentSpeed, 0.0, 260.0);

    uint8_t gear = computeGear(m_currentSpeed);
    double rpm = computeRpm(m_currentSpeed, gear);

    emit speedDataReceived(makeSpeedData(m_currentSpeed));
    emit rpmDataReceived(makeRpmData(rpm, gear));
}

void SimulatedCanBus::generateTellTaleEvent()
{
    // Randomly toggle tell-tales for demonstration
    auto id = static_cast<TellTaleId>(
        QRandomGenerator::global()->bounded(static_cast<int>(TellTaleId::Count)));
    auto state = static_cast<TellTaleState>(
        QRandomGenerator::global()->bounded(3));  // Off, On, Blinking

    emit tellTaleChanged(makeTellTaleEvent(id, state));
}

SpeedData SimulatedCanBus::makeSpeedData(double kmh)
{
    SpeedData data;
    data.kmh = kmh;
    data.aliveCounter = m_speedAliveCounter;
    m_speedAliveCounter = (m_speedAliveCounter + 1) % 16;

    uint8_t payload[8];
    std::memcpy(payload, &data.kmh, sizeof(data.kmh));
    data.checksum = DataIntegrity::computeCrc8(payload, sizeof(data.kmh));

    return data;
}

RpmData SimulatedCanBus::makeRpmData(double rpm, uint8_t gear)
{
    RpmData data;
    data.rpm = rpm;
    data.gear = gear;
    data.aliveCounter = m_rpmAliveCounter;
    m_rpmAliveCounter = (m_rpmAliveCounter + 1) % 16;

    uint8_t payload[9];
    std::memcpy(payload, &data.rpm, sizeof(data.rpm));
    payload[sizeof(data.rpm)] = data.gear;
    data.checksum = DataIntegrity::computeCrc8(payload, sizeof(data.rpm) + 1);

    return data;
}

TellTaleEvent SimulatedCanBus::makeTellTaleEvent(TellTaleId id, TellTaleState state)
{
    TellTaleEvent event;
    event.id = id;
    event.state = state;
    event.aliveCounter = m_tellTaleAliveCounter;
    m_tellTaleAliveCounter = (m_tellTaleAliveCounter + 1) % 16;

    uint8_t payload[2] = {
        static_cast<uint8_t>(event.id),
        static_cast<uint8_t>(event.state)
    };
    event.checksum = DataIntegrity::computeCrc8(payload, 2);

    return event;
}

uint8_t SimulatedCanBus::computeGear(double speed) const
{
    if (speed < 1.0) return 0;      // neutral
    if (speed < 20.0) return 1;
    if (speed < 40.0) return 2;
    if (speed < 65.0) return 3;
    if (speed < 90.0) return 4;
    if (speed < 120.0) return 5;
    if (speed < 160.0) return 6;
    if (speed < 200.0) return 7;
    return 8;
}

double SimulatedCanBus::computeRpm(double speed, uint8_t gear) const
{
    if (gear == 0) return 800.0;  // idle

    // Simulate gear ratios for realistic RPM curve
    static const double gearRatios[] = {
        0.0, 3.8, 2.4, 1.7, 1.3, 1.0, 0.85, 0.72, 0.62
    };

    double ratio = gearRatios[std::min(static_cast<int>(gear), 8)];
    double rpm = 800.0 + (speed * ratio * 30.0);
    return std::clamp(rpm, 800.0, 8000.0);
}

} // namespace hmi
