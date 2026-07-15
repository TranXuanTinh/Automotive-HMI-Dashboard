#include "YoloProcessingStrategy.h"
#include <algorithm>
#include <numeric>

namespace hmi {

YoloProcessingStrategy::YoloProcessingStrategy(float confidenceThreshold,
                                                 float nmsThreshold)
    : m_confidenceThreshold(confidenceThreshold)
    , m_nmsThreshold(nmsThreshold)
{
}

float YoloProcessingStrategy::computeIoU(const BoundingBox &a, const BoundingBox &b) const
{
    float x1 = std::max(a.x, b.x);
    float y1 = std::max(a.y, b.y);
    float x2 = std::min(a.x + a.width, b.x + b.width);
    float y2 = std::min(a.y + a.height, b.y + b.height);

    float intersection = std::max(0.0f, x2 - x1) * std::max(0.0f, y2 - y1);
    float areaA = a.width * a.height;
    float areaB = b.width * b.height;
    float unionArea = areaA + areaB - intersection;

    return (unionArea > 0.0f) ? intersection / unionArea : 0.0f;
}

AdasFrame YoloProcessingStrategy::process(const AdasFrame &rawFrame)
{
    AdasFrame result;
    result.timestampMs = rawFrame.timestampMs;

    // 1. Confidence filtering
    std::vector<DetectedObject> filtered;
    std::copy_if(rawFrame.objects.begin(), rawFrame.objects.end(),
                 std::back_inserter(filtered),
                 [this](const DetectedObject &obj) {
                     return obj.confidence >= m_confidenceThreshold;
                 });

    // 2. Sort by confidence (descending) for NMS
    std::sort(filtered.begin(), filtered.end(),
              [](const DetectedObject &a, const DetectedObject &b) {
                  return a.confidence > b.confidence;
              });

    // 3. Non-maximum suppression
    std::vector<bool> suppressed(filtered.size(), false);
    for (size_t i = 0; i < filtered.size(); ++i) {
        if (suppressed[i]) continue;

        result.objects.push_back(filtered[i]);

        for (size_t j = i + 1; j < filtered.size(); ++j) {
            if (suppressed[j]) continue;
            if (filtered[i].cls != filtered[j].cls) continue;

            if (computeIoU(filtered[i].box, filtered[j].box) > m_nmsThreshold) {
                suppressed[j] = true;
            }
        }
    }

    return result;
}

} // namespace hmi
