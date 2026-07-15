#ifndef CORE_IVEHICLEBUS_H
#define CORE_IVEHICLEBUS_H

#include <QObject>
#include "VehicleData.h"

namespace hmi {

/// Abstract interface for vehicle bus communication (CAN/LIN/simulated).
/// Implementations run on a background thread and emit signals when
/// new data frames arrive. ViewModels connect with Qt::QueuedConnection
/// to safely receive updates on the GUI thread.
class IVehicleBus : public QObject
{
    Q_OBJECT

public:
    explicit IVehicleBus(QObject *parent = nullptr) : QObject(parent) {}
    ~IVehicleBus() override = default;

    /// Start the bus data acquisition loop.
    virtual void start() = 0;

    /// Stop the bus data acquisition loop.
    virtual void stop() = 0;

    /// Check if the bus is currently running.
    virtual bool isRunning() const = 0;

signals:
    void speedDataReceived(const hmi::SpeedData &data);
    void rpmDataReceived(const hmi::RpmData &data);
    void tellTaleChanged(const hmi::TellTaleEvent &event);
    void busError(const QString &description);
};

} // namespace hmi

#endif // CORE_IVEHICLEBUS_H
