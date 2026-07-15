#include "SpeedViewModel.h"

namespace hmi {

SpeedViewModel::SpeedViewModel(QObject *parent)
    : QObject(parent)
{
}

QString SpeedViewModel::speedText() const
{
    double displaySpeed = m_useImperial ? m_speed * 0.621371 : m_speed;
    return QString::number(static_cast<int>(displaySpeed));
}

void SpeedViewModel::toggleUnit()
{
    m_useImperial = !m_useImperial;
    emit unitChanged();
    emit speedChanged();
}

void SpeedViewModel::onSpeedChanged(double kmh)
{
    if (qFuzzyCompare(m_speed, kmh))
        return;
    m_speed = kmh;
    emit speedChanged();
}

} // namespace hmi
