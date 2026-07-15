#ifndef CORE_IADASSENSOR_H
#define CORE_IADASSENSOR_H

#include <QObject>
#include "AdasData.h"

namespace hmi {

/// Abstract interface for ADAS perception data sources.
/// A SimulatedAdasPipeline and a real YoloPerceptionPipeline both
/// implement this — Liskov Substitution Principle: the HMI consumes
/// data identically regardless of the concrete source.
class IAdasSensor : public QObject
{
    Q_OBJECT

public:
    explicit IAdasSensor(QObject *parent = nullptr) : QObject(parent) {}
    ~IAdasSensor() override = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isRunning() const = 0;

signals:
    void frameReceived(const hmi::AdasFrame &frame);
    void sensorError(const QString &description);
};

} // namespace hmi

#endif // CORE_IADASSENSOR_H
