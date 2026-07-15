#include "WatchdogManager.h"
#include "DashboardStateManager.h"
#include <QDebug>

namespace hmi {

WatchdogManager::WatchdogManager(DashboardStateManager *stateManager, QObject *parent)
    : QObject(parent)
    , m_stateManager(stateManager)
{
    m_watchdog = new WatchdogTimer(500);  // 500ms timeout
    m_watchdog->moveToThread(&m_watchdogThread);

    // Kick timer runs on GUI thread — proves the GUI thread is alive
    m_kickTimer.setInterval(100);
    connect(&m_kickTimer, &QTimer::timeout, m_watchdog, &WatchdogTimer::kick);

    // Watchdog expiry → safe mode
    connect(m_watchdog, &WatchdogTimer::watchdogExpired,
            m_stateManager, &DashboardStateManager::activateSafeMode,
            Qt::QueuedConnection);

    connect(&m_watchdogThread, &QThread::started, m_watchdog, &WatchdogTimer::start);
    connect(&m_watchdogThread, &QThread::finished, m_watchdog, &QObject::deleteLater);
}

WatchdogManager::~WatchdogManager()
{
    stop();
}

void WatchdogManager::start()
{
    m_watchdogThread.start();
    m_kickTimer.start();
    qDebug() << "[WatchdogManager] Started — GUI thread kick every 100ms, timeout 500ms";
}

void WatchdogManager::stop()
{
    m_kickTimer.stop();
    m_watchdogThread.quit();
    m_watchdogThread.wait();
}

} // namespace hmi
