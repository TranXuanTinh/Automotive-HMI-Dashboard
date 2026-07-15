#include "VehicleSettingsViewModel.h"
#include <QVariantMap>

namespace hmi {

VehicleSettingsViewModel::VehicleSettingsViewModel(QObject *parent)
    : QObject(parent)
{
    m_doors = {
        { QStringLiteral("Front Left"),  true },
        { QStringLiteral("Front Right"), true },
        { QStringLiteral("Rear Left"),   true },
        { QStringLiteral("Rear Right"),  true },
        { QStringLiteral("Trunk"),       true }
    };
}

QVariantList VehicleSettingsViewModel::doorLockStates() const
{
    QVariantList list;
    for (const auto &door : m_doors) {
        QVariantMap map;
        map[QStringLiteral("name")] = door.name;
        map[QStringLiteral("isLocked")] = door.isLocked;
        list.append(map);
    }
    return list;
}

bool VehicleSettingsViewModel::allDoorsLocked() const
{
    for (const auto &door : m_doors) {
        if (!door.isLocked) return false;
    }
    return true;
}

void VehicleSettingsViewModel::toggleDoorLock(int doorIndex)
{
    if (doorIndex < 0 || doorIndex >= m_doors.size()) return;
    m_doors[doorIndex].isLocked = !m_doors[doorIndex].isLocked;
    emit doorLocksChanged();
}

void VehicleSettingsViewModel::lockAll()
{
    for (auto &door : m_doors) door.isLocked = true;
    emit doorLocksChanged();
}

void VehicleSettingsViewModel::unlockAll()
{
    for (auto &door : m_doors) door.isLocked = false;
    emit doorLocksChanged();
}

void VehicleSettingsViewModel::setAmbientColor(const QColor &color)
{
    if (m_ambientColor == color) return;
    m_ambientColor = color;
    emit ambientChanged();
}

void VehicleSettingsViewModel::setAmbientIntensity(double intensity)
{
    m_ambientIntensity = qBound(0.0, intensity, 1.0);
    emit ambientChanged();
}

} // namespace hmi
