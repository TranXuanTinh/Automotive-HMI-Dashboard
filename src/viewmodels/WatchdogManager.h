#ifndef VIEWMODELS_WATCHDOGMANAGER_H
#define VIEWMODELS_WATCHDOGMANAGER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <core/WatchdogTimer.h>

namespace hmi {

class DashboardStateManager;

/// Manages the software watchdog for functional safety.
/// Runs the WatchdogTimer on a dedicated thread and kicks it
/// from the GUI thread via a QTimer.
class WatchdogManager : public QObject
{
    Q_OBJECT

public:
    explicit WatchdogManager(DashboardStateManager *stateManager,
                              QObject *parent = nullptr);
    ~WatchdogManager() override;

    void start();
    void stop();

private:
    WatchdogTimer         *m_watchdog = nullptr;
    QThread                m_watchdogThread;
    QTimer                 m_kickTimer;
    DashboardStateManager *m_stateManager = nullptr;
};

} // namespace hmi

#endif // VIEWMODELS_WATCHDOGMANAGER_H
