#ifndef CORE_IVEHICLESPEEDOBSERVER_H
#define CORE_IVEHICLESPEEDOBSERVER_H

namespace hmi {

/// Segregated observer interface: only speed data.
/// UI components needing only speed implement this instead of
/// a monolithic IVehicleDataObserver — Interface Segregation Principle.
class IVehicleSpeedObserver
{
public:
    virtual ~IVehicleSpeedObserver() = default;
    virtual void onSpeedChanged(double kmh) = 0;
};

} // namespace hmi

#endif // CORE_IVEHICLESPEEDOBSERVER_H
