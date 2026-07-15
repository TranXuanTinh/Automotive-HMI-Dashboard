#include "DashboardStateManager.h"
#include <QDebug>

namespace hmi {

DashboardStateManager::DashboardStateManager(QObject *parent)
    : QObject(parent)
{
}

QString DashboardStateManager::currentState() const
{
    switch (m_state) {
    case State::Normal:   return QStringLiteral("normal");
    case State::Sport:    return QStringLiteral("sport");
    case State::Parking:  return QStringLiteral("parking");
    case State::SafeMode: return QStringLiteral("safemode");
    }
    return QStringLiteral("normal");
}

QColor DashboardStateManager::accentColor() const
{
    switch (m_state) {
    case State::Normal:   return QColor(QStringLiteral("#00D4FF"));  // cyan
    case State::Sport:    return QColor(QStringLiteral("#FF3D57"));  // red
    case State::Parking:  return QColor(QStringLiteral("#00E676"));  // green
    case State::SafeMode: return QColor(QStringLiteral("#FFB800"));  // amber
    }
    return QColor(QStringLiteral("#00D4FF"));
}

bool DashboardStateManager::isClusterVisible() const
{
    return true;  // cluster always visible — ASIL requirement
}

bool DashboardStateManager::isInfotainmentVisible() const
{
    return m_state != State::SafeMode;
}

double DashboardStateManager::clusterWidthRatio() const
{
    switch (m_state) {
    case State::Normal:   return 0.6;
    case State::Sport:    return 0.7;   // more cluster space in sport mode
    case State::Parking:  return 0.5;   // balanced for camera view
    case State::SafeMode: return 1.0;   // full screen for cluster
    }
    return 0.6;
}

void DashboardStateManager::setNormalMode()
{
    if (m_state == State::SafeMode) return;  // cannot leave safe mode via UI
    m_state = State::Normal;
    qDebug() << "[DashboardState] → Normal Mode";
    emit stateChanged();
}

void DashboardStateManager::setSportMode()
{
    if (m_state == State::SafeMode) return;
    m_state = State::Sport;
    qDebug() << "[DashboardState] → Sport Mode";
    emit stateChanged();
}

void DashboardStateManager::setParkingMode()
{
    if (m_state == State::SafeMode) return;
    m_state = State::Parking;
    qDebug() << "[DashboardState] → Parking Mode";
    emit stateChanged();
}

void DashboardStateManager::activateSafeMode()
{
    m_state = State::SafeMode;
    qCritical() << "[DashboardState] → SAFE MODE ACTIVATED";
    emit stateChanged();
}

} // namespace hmi
