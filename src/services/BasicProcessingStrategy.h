#ifndef SERVICES_BASICPROCESSINGSTRATEGY_H
#define SERVICES_BASICPROCESSINGSTRATEGY_H

#include <core/IAdasProcessingStrategy.h>

namespace hmi {

/// Pass-through processing strategy (fallback for basic radar/lidar sensors).
/// Applies only a minimal confidence threshold — no NMS.
class BasicProcessingStrategy : public IAdasProcessingStrategy
{
public:
    explicit BasicProcessingStrategy(float confidenceThreshold = 0.3f);

    AdasFrame process(const AdasFrame &rawFrame) override;
    QString name() const override { return QStringLiteral("Basic Radar"); }

private:
    float m_confidenceThreshold;
};

} // namespace hmi

#endif // SERVICES_BASICPROCESSINGSTRATEGY_H
