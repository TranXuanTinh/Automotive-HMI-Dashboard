#ifndef CORE_WATCHDOGTIMER_H
#define CORE_WATCHDOGTIMER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>

namespace hmi {

/// Software watchdog timer for functional safety (ISO 26262).
/// The UI thread must call kick() periodically. If the watchdog
/// is not kicked within the timeout period, it emits watchdogExpired()
/// signalling that the UI thread is hung and a safe-state fallback
/// should be activated.
class WatchdogTimer : public QObject
{
    Q_OBJECT

public:
    explicit WatchdogTimer(int timeoutMs = 500, QObject *parent = nullptr);
    ~WatchdogTimer() override;

    /// Start monitoring. Must be called from the watchdog's own thread.
    void start();

    /// Stop monitoring.
    void stop();

    /// Kick (reset) the watchdog. Thread-safe — called from the GUI thread.
    void kick();

    int timeoutMs() const { return m_timeoutMs; }

signals:
    /// Emitted when the watchdog expires (UI thread unresponsive).
    void watchdogExpired();

private slots:
    void checkTimeout();

private:
    int            m_timeoutMs;
    QTimer         m_checkTimer;
    QElapsedTimer  m_elapsed;
    QMutex         m_mutex;
    bool           m_kicked = false;
    bool           m_running = false;
};

} // namespace hmi

#endif // CORE_WATCHDOGTIMER_H
