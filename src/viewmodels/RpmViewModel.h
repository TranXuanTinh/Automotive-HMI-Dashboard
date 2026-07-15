#ifndef VIEWMODELS_RPMVIEWMODEL_H
#define VIEWMODELS_RPMVIEWMODEL_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

namespace hmi {

class RpmViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(double rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(double normalizedRpm READ normalizedRpm NOTIFY rpmChanged)
    Q_PROPERTY(double maxRpm READ maxRpm CONSTANT)
    Q_PROPERTY(double redlineRpm READ redlineRpm CONSTANT)
    Q_PROPERTY(int gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(QString gearText READ gearText NOTIFY gearChanged)
    Q_PROPERTY(QString rpmText READ rpmText NOTIFY rpmChanged)

public:
    explicit RpmViewModel(QObject *parent = nullptr);

    double rpm() const { return m_rpm; }
    double normalizedRpm() const { return m_rpm / m_maxRpm; }
    double maxRpm() const { return m_maxRpm; }
    double redlineRpm() const { return m_redlineRpm; }
    int gear() const { return m_gear; }
    QString gearText() const;
    QString rpmText() const;

public slots:
    void onRpmChanged(double rpm, uint8_t gear);

signals:
    void rpmChanged();
    void gearChanged();

private:
    double  m_rpm = 0.0;
    int     m_gear = 0;
    double  m_maxRpm = 8000.0;
    double  m_redlineRpm = 6500.0;
};

} // namespace hmi

#endif // VIEWMODELS_RPMVIEWMODEL_H
