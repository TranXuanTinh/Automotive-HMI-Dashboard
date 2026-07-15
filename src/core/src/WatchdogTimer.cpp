#include "core/WatchdogTimer.h"
#include <QMutexLocker>
#include <QDebug>

namespace hmi {

WatchdogTimer::WatchdogTimer(int timeoutMs, QObject *parent)
    : QObject(parent)
    , m_timeoutMs(timeoutMs)
{
    // Check at half the timeout interval for responsive detection
    m_checkTimer.setInterval(timeoutMs / 2);
    connect(&m_checkTimer, &QTimer::timeout, this, &WatchdogTimer::checkTimeout);
}

WatchdogTimer::~WatchdogTimer()
{
    stop();
}

void WatchdogTimer::start()
{
    QMutexLocker locker(&m_mutex);
    m_kicked = true;
    m_running = true;
    m_elapsed.start();
    m_checkTimer.start();
    qDebug() << "[Watchdog] Started with timeout" << m_timeoutMs << "ms";
}

void WatchdogTimer::stop()
{
    QMutexLocker locker(&m_mutex);
    m_running = false;
    m_checkTimer.stop();
    qDebug() << "[Watchdog] Stopped";
}

void WatchdogTimer::kick()
{
    QMutexLocker locker(&m_mutex);
    m_kicked = true;
    m_elapsed.restart();
}

void WatchdogTimer::checkTimeout()
{
    QMutexLocker locker(&m_mutex);

    if (!m_running)
        return;

    if (!m_kicked) {
        qCritical() << "[Watchdog] EXPIRED — UI thread unresponsive for"
                     << m_elapsed.elapsed() << "ms";
        locker.unlock();
        emit watchdogExpired();
        return;
    }

    if (m_elapsed.elapsed() > m_timeoutMs) {
        qCritical() << "[Watchdog] EXPIRED — timeout exceeded:"
                     << m_elapsed.elapsed() << "ms >" << m_timeoutMs << "ms";
        m_kicked = false;
        locker.unlock();
        emit watchdogExpired();
        return;
    }

    m_kicked = false;
}

} // namespace hmi
