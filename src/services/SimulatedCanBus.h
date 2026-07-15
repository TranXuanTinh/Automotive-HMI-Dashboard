#ifndef SERVICES_SIMULATEDCANBUS_H
#define SERVICES_SIMULATEDCANBUS_H

#include <core/IVehicleBus.h>
#include <core/DataIntegrity.h>
#include <QTimer>
#include <QRandomGenerator>
#include <atomic>

namespace hmi {

/// Simulated CAN bus that generates realistic vehicle telemetry data.
/// Produces speed, RPM, and tell-tale data with proper checksums and
/// alive counters. Runs on a 20ms cycle (50 Hz) for <50ms latency.
class SimulatedCanBus : public IVehicleBus
{
    Q_OBJECT

public:
    explicit SimulatedCanBus(QObject *parent = nullptr);
    ~SimulatedCanBus() override;

    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void generateFrame();
    void generateTellTaleEvent();

private:
    SpeedData makeSpeedData(double kmh);
    RpmData makeRpmData(double rpm, uint8_t gear);
    TellTaleEvent makeTellTaleEvent(TellTaleId id, TellTaleState state);

    uint8_t computeGear(double speed) const;
    double computeRpm(double speed, uint8_t gear) const;

    QTimer          m_frameTimer;         // 20ms cycle — vehicle data
    QTimer          m_tellTaleTimer;      // 2s cycle — tell-tale changes
    std::atomic<bool> m_running{false};

    // Simulation state
    double   m_currentSpeed      = 0.0;
    double   m_targetSpeed       = 80.0;
    double   m_acceleration      = 2.0;   // km/h per cycle
    uint8_t  m_speedAliveCounter = 0;
    uint8_t  m_rpmAliveCounter   = 0;
    uint8_t  m_tellTaleAliveCounter = 0;
    int      m_cycleCount        = 0;
};

} // namespace hmi

#endif // SERVICES_SIMULATEDCANBUS_H
