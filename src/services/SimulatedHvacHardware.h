#ifndef SERVICES_SIMULATEDHVACHARDWARE_H
#define SERVICES_SIMULATEDHVACHARDWARE_H

#include <core/IHvacController.h>
#include <QTimer>

namespace hmi {

/// Simulated HVAC hardware controller.
/// Applies gradual temperature changes to simulate real HVAC response lag.
class SimulatedHvacHardware : public IHvacController
{
    Q_OBJECT

public:
    explicit SimulatedHvacHardware(QObject *parent = nullptr);

    void setDriverTemperature(double tempC) override;
    void setPassengerTemperature(double tempC) override;
    void setFanSpeed(int level) override;
    void setAirflowMode(AirflowMode mode) override;
    void setAcEnabled(bool enabled) override;
    void setRecirculationEnabled(bool enabled) override;
    void setSyncEnabled(bool enabled) override;

    HvacState currentState() const override;

private slots:
    void simulateResponse();

private:
    HvacState m_state;
    double    m_targetDriverTemp    = 22.0;
    double    m_targetPassengerTemp = 22.0;
    QTimer    m_responseTimer;
};

} // namespace hmi

#endif // SERVICES_SIMULATEDHVACHARDWARE_H
