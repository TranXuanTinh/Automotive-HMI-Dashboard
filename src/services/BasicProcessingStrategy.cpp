#include "BasicProcessingStrategy.h"
#include <algorithm>

namespace hmi {

BasicProcessingStrategy::BasicProcessingStrategy(float confidenceThreshold)
    : m_confidenceThreshold(confidenceThreshold)
{
}

AdasFrame BasicProcessingStrategy::process(const AdasFrame &rawFrame)
{
    AdasFrame result;
    result.timestampMs = rawFrame.timestampMs;

    std::copy_if(rawFrame.objects.begin(), rawFrame.objects.end(),
                 std::back_inserter(result.objects),
                 [this](const DetectedObject &obj) {
                     return obj.confidence >= m_confidenceThreshold;
                 });

    return result;
}

} // namespace hmi
