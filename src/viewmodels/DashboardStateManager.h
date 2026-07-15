#ifndef VIEWMODELS_DASHBOARDSTATEMANAGER_H
#define VIEWMODELS_DASHBOARDSTATEMANAGER_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

namespace hmi {

/// State Pattern implementation for dashboard mode management.
/// States: Normal, Sport, Parking, SafeMode
/// Each state configures the dashboard layout, gauge styling, and features.
class DashboardStateManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString currentState READ currentState NOTIFY stateChanged)
    Q_PROPERTY(QString accentColor READ accentColor NOTIFY stateChanged)
    Q_PROPERTY(bool isClusterVisible READ isClusterVisible NOTIFY stateChanged)
    Q_PROPERTY(bool isInfotainmentVisible READ isInfotainmentVisible NOTIFY stateChanged)
    Q_PROPERTY(bool isSafeMode READ isSafeMode NOTIFY stateChanged)
    Q_PROPERTY(double clusterWidthRatio READ clusterWidthRatio NOTIFY stateChanged)

public:
    enum class State {
        Normal,
        Sport,
        Parking,
        SafeMode
    };
    Q_ENUM(State)

    explicit DashboardStateManager(QObject *parent = nullptr);

    QString currentState() const;
    QString accentColor() const;
    bool isClusterVisible() const;
    bool isInfotainmentVisible() const;
    bool isSafeMode() const { return m_state == State::SafeMode; }
    double clusterWidthRatio() const;

    Q_INVOKABLE void setNormalMode();
    Q_INVOKABLE void setSportMode();
    Q_INVOKABLE void setParkingMode();

public slots:
    void activateSafeMode();

signals:
    void stateChanged();

private:
    State m_state = State::Normal;
};

} // namespace hmi

#endif // VIEWMODELS_DASHBOARDSTATEMANAGER_H
