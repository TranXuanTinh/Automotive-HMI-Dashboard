#ifndef CORE_IADASPROCESSINGSTRATEGY_H
#define CORE_IADASPROCESSINGSTRATEGY_H

#include "AdasData.h"

namespace hmi {

/// Strategy pattern interface for ADAS data processing algorithms.
/// The system can swap between different processing behaviours
/// at runtime depending on the active sensor suite:
///   - YoloProcessingStrategy: applies NMS + confidence filtering
///   - BasicProcessingStrategy: pass-through (radar/lidar fallback)
class IAdasProcessingStrategy
{
public:
    virtual ~IAdasProcessingStrategy() = default;

    /// Process a raw ADAS frame, returning a filtered/refined frame.
    virtual AdasFrame process(const AdasFrame &rawFrame) = 0;

    /// Human-readable name for logging / UI display.
    virtual QString name() const = 0;
};

} // namespace hmi

#endif // CORE_IADASPROCESSINGSTRATEGY_H
