#ifndef VIEWMODELS_SPEEDVIEWMODEL_H
#define VIEWMODELS_SPEEDVIEWMODEL_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

namespace hmi {

class SpeedViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(double speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(double normalizedSpeed READ normalizedSpeed NOTIFY speedChanged)
    Q_PROPERTY(double maxSpeed READ maxSpeed CONSTANT)
    Q_PROPERTY(QString speedText READ speedText NOTIFY speedChanged)
    Q_PROPERTY(QString unit READ unit NOTIFY unitChanged)

public:
    explicit SpeedViewModel(QObject *parent = nullptr);

    double speed() const { return m_speed; }
    double normalizedSpeed() const { return m_speed / m_maxSpeed; }
    double maxSpeed() const { return m_maxSpeed; }
    QString speedText() const;
    QString unit() const { return m_useImperial ? QStringLiteral("mph") : QStringLiteral("km/h"); }

    Q_INVOKABLE void toggleUnit();

public slots:
    void onSpeedChanged(double kmh);

signals:
    void speedChanged();
    void unitChanged();

private:
    double m_speed = 0.0;
    double m_maxSpeed = 280.0;
    bool   m_useImperial = false;
};

} // namespace hmi

#endif // VIEWMODELS_SPEEDVIEWMODEL_H
