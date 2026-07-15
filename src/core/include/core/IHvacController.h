#ifndef CORE_IHVACCONTROLLER_H
#define CORE_IHVACCONTROLLER_H

#include <QObject>
#include "HvacData.h"

namespace hmi {

/// Abstract interface for HVAC hardware control.
/// Decouples ViewModels from concrete hardware — Dependency Inversion.
class IHvacController : public QObject
{
    Q_OBJECT

public:
    explicit IHvacController(QObject *parent = nullptr) : QObject(parent) {}
    ~IHvacController() override = default;

    virtual void setDriverTemperature(double tempC) = 0;
    virtual void setPassengerTemperature(double tempC) = 0;
    virtual void setFanSpeed(int level) = 0;
    virtual void setAirflowMode(AirflowMode mode) = 0;
    virtual void setAcEnabled(bool enabled) = 0;
    virtual void setRecirculationEnabled(bool enabled) = 0;
    virtual void setSyncEnabled(bool enabled) = 0;

    virtual HvacState currentState() const = 0;

signals:
    void stateChanged(const hmi::HvacState &state);
};

} // namespace hmi

#endif // CORE_IHVACCONTROLLER_H
