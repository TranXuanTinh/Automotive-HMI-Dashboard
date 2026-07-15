#ifndef CORE_ADASDATA_H
#define CORE_ADASDATA_H

#include <cstdint>
#include <vector>
#include <QMetaType>

namespace hmi {

// ── Object classification from perception pipeline ──────────────────────
enum class ObjectClass : uint8_t {
    Vehicle = 0,
    Pedestrian,
    Cyclist,
    TrafficSign,
    TrafficLight,
    Unknown
};

// ── Normalised bounding box (0.0–1.0 viewport coordinates) ─────────────
struct BoundingBox {
    float x      = 0.0f;   // top-left X
    float y      = 0.0f;   // top-left Y
    float width  = 0.0f;
    float height = 0.0f;
};

// ── Single detected object ─────────────────────────────────────────────
struct DetectedObject {
    BoundingBox  box;
    ObjectClass  cls        = ObjectClass::Unknown;
    float        confidence = 0.0f;   // 0.0–1.0
    int          trackId    = -1;     // stable ID across frames
};

// ── Complete ADAS frame ────────────────────────────────────────────────
struct AdasFrame {
    std::vector<DetectedObject> objects;
    uint64_t timestampMs = 0;
};

} // namespace hmi

Q_DECLARE_METATYPE(hmi::DetectedObject)
Q_DECLARE_METATYPE(hmi::AdasFrame)
Q_DECLARE_METATYPE(hmi::ObjectClass)

#endif // CORE_ADASDATA_H
