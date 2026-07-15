#ifndef SERVICES_SIMULATEDADASPIPELINE_H
#define SERVICES_SIMULATEDADASPIPELINE_H

#include <core/IAdasSensor.h>
#include <QTimer>

namespace hmi {

/// Simulated ADAS perception pipeline producing moving bounding boxes
/// with varying confidence scores and object classifications.
/// Implements IAdasSensor — Liskov-substitutable with a real YOLO pipeline.
class SimulatedAdasPipeline : public IAdasSensor
{
    Q_OBJECT

public:
    explicit SimulatedAdasPipeline(QObject *parent = nullptr);
    ~SimulatedAdasPipeline() override;

    void start() override;
    void stop() override;
    bool isRunning() const override;

private slots:
    void generateFrame();

private:
    QTimer m_timer;
    bool   m_running = false;
    int    m_frameCount = 0;
};

} // namespace hmi

#endif // SERVICES_SIMULATEDADASPIPELINE_H
