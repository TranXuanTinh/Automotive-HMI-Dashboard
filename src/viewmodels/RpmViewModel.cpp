#include "RpmViewModel.h"

namespace hmi {

RpmViewModel::RpmViewModel(QObject *parent)
    : QObject(parent)
{
}

QString RpmViewModel::gearText() const
{
    if (m_gear == 0) return QStringLiteral("N");
    if (m_gear == 9) return QStringLiteral("R");
    return QString::number(m_gear);
}

QString RpmViewModel::rpmText() const
{
    return QString::number(static_cast<int>(m_rpm));
}

void RpmViewModel::onRpmChanged(double rpm, uint8_t gear)
{
    bool rpmDiff = !qFuzzyCompare(m_rpm, rpm);
    bool gearDiff = m_gear != static_cast<int>(gear);

    m_rpm = rpm;
    m_gear = static_cast<int>(gear);

    if (rpmDiff) emit rpmChanged();
    if (gearDiff) emit gearChanged();
}

} // namespace hmi
