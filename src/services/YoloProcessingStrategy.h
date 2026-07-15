#ifndef SERVICES_YOLOPROCESSINGSTRATEGY_H
#define SERVICES_YOLOPROCESSINGSTRATEGY_H

#include <core/IAdasProcessingStrategy.h>

namespace hmi {

/// YOLO-inspired processing strategy: applies confidence filtering
/// and non-maximum suppression (NMS) to raw ADAS frames.
class YoloProcessingStrategy : public IAdasProcessingStrategy
{
public:
    explicit YoloProcessingStrategy(float confidenceThreshold = 0.5f,
                                     float nmsThreshold = 0.45f);

    AdasFrame process(const AdasFrame &rawFrame) override;
    QString name() const override { return QStringLiteral("YOLO NMS"); }

private:
    float computeIoU(const BoundingBox &a, const BoundingBox &b) const;

    float m_confidenceThreshold;
    float m_nmsThreshold;
};

} // namespace hmi

#endif // SERVICES_YOLOPROCESSINGSTRATEGY_H
