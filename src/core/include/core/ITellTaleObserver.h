#ifndef CORE_ITELLTALEOBSERVER_H
#define CORE_ITELLTALEOBSERVER_H

#include "VehicleData.h"

namespace hmi {

/// Segregated observer interface: only tell-tale state changes.
class ITellTaleObserver
{
public:
    virtual ~ITellTaleObserver() = default;
    virtual void onTellTaleChanged(TellTaleId id, TellTaleState state) = 0;
};

} // namespace hmi

#endif // CORE_ITELLTALEOBSERVER_H
