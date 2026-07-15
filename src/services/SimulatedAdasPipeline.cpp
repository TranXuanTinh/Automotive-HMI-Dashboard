#include "SimulatedAdasPipeline.h"
#include <QRandomGenerator>
#include <QDateTime>
#include <cmath>

namespace hmi {

SimulatedAdasPipeline::SimulatedAdasPipeline(QObject *parent)
    : IAdasSensor(parent)
{
    m_timer.setInterval(100);  // 10 Hz — typical camera frame rate for ADAS
    connect(&m_timer, &QTimer::timeout, this, &SimulatedAdasPipeline::generateFrame);
}

SimulatedAdasPipeline::~SimulatedAdasPipeline()
{
    stop();
}

void SimulatedAdasPipeline::start()
{
    if (m_running) return;
    m_running = true;
    m_frameCount = 0;
    m_timer.start();
}

void SimulatedAdasPipeline::stop()
{
    m_running = false;
    m_timer.stop();
}

bool SimulatedAdasPipeline::isRunning() const
{
    return m_running;
}

void SimulatedAdasPipeline::generateFrame()
{
    ++m_frameCount;

    AdasFrame frame;
    frame.timestampMs = static_cast<uint64_t>(QDateTime::currentMSecsSinceEpoch());

    auto *rng = QRandomGenerator::global();

    // Generate 2–5 objects with smooth movement via sinusoidal paths
    int objectCount = rng->bounded(2, 6);
    for (int i = 0; i < objectCount; ++i) {
        DetectedObject obj;
        obj.trackId = i;

        // Sinusoidal movement for smooth animation
        double phase = (m_frameCount + i * 50) * 0.02;
        obj.box.x = static_cast<float>(0.1 + 0.3 * std::sin(phase + i) + 0.3);
        obj.box.y = static_cast<float>(0.2 + 0.15 * std::cos(phase * 0.7 + i * 1.5) + 0.2);
        obj.box.width = static_cast<float>(0.05 + 0.04 * std::sin(phase * 0.3));
        obj.box.height = static_cast<float>(0.08 + 0.06 * std::sin(phase * 0.4));

        // Clamp to viewport
        obj.box.x = std::clamp(obj.box.x, 0.0f, 0.9f);
        obj.box.y = std::clamp(obj.box.y, 0.0f, 0.85f);
        obj.box.width = std::clamp(obj.box.width, 0.03f, 0.15f);
        obj.box.height = std::clamp(obj.box.height, 0.04f, 0.2f);

        // Cycle through object classes deterministically per track ID
        obj.cls = static_cast<ObjectClass>(i % 4);
        obj.confidence = static_cast<float>(0.7 + 0.3 * std::abs(std::sin(phase)));

        frame.objects.push_back(obj);
    }

    emit frameReceived(frame);
}

} // namespace hmi
