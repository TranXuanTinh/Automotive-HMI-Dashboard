#ifndef VIEWMODELS_VEHICLESETTINGSVIEWMODEL_H
#define VIEWMODELS_VEHICLESETTINGSVIEWMODEL_H

#include <QObject>
#include <QColor>
#include <QVariantList>
#include <QtQmlIntegration/qqmlintegration.h>

namespace hmi {

class VehicleSettingsViewModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QVariantList doorLockStates READ doorLockStates NOTIFY doorLocksChanged)
    Q_PROPERTY(QColor ambientColor READ ambientColor NOTIFY ambientChanged)
    Q_PROPERTY(double ambientIntensity READ ambientIntensity NOTIFY ambientChanged)
    Q_PROPERTY(bool allDoorsLocked READ allDoorsLocked NOTIFY doorLocksChanged)

public:
    explicit VehicleSettingsViewModel(QObject *parent = nullptr);

    QVariantList doorLockStates() const;
    QColor ambientColor() const { return m_ambientColor; }
    double ambientIntensity() const { return m_ambientIntensity; }
    bool allDoorsLocked() const;

    Q_INVOKABLE void toggleDoorLock(int doorIndex);
    Q_INVOKABLE void lockAll();
    Q_INVOKABLE void unlockAll();
    Q_INVOKABLE void setAmbientColor(const QColor &color);
    Q_INVOKABLE void setAmbientIntensity(double intensity);

signals:
    void doorLocksChanged();
    void ambientChanged();

private:
    struct DoorState {
        QString name;
        bool    isLocked = true;
    };

    QList<DoorState> m_doors;
    QColor           m_ambientColor{0, 212, 255};  // cyan default
    double           m_ambientIntensity = 0.7;
};

} // namespace hmi

#endif // VIEWMODELS_VEHICLESETTINGSVIEWMODEL_H
