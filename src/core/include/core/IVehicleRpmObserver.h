#ifndef CORE_IVEHICLERPMOBSERVER_H
#define CORE_IVEHICLERPMOBSERVER_H

#include <cstdint>

namespace hmi {

/// Segregated observer interface: only RPM + gear data.
class IVehicleRpmObserver
{
public:
    virtual ~IVehicleRpmObserver() = default;
    virtual void onRpmChanged(double rpm, uint8_t gear) = 0;
};

} // namespace hmi

#endif // CORE_IVEHICLERPMOBSERVER_H
