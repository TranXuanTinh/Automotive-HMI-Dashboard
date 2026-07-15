#include "HvacViewModel.h"
#include <core/IHvacController.h>

namespace hmi {

HvacViewModel::HvacViewModel(QObject *parent)
    : QObject(parent)
{
}

void HvacViewModel::setController(IHvacController *controller)
{
    m_controller = controller;
    if (m_controller) {
        connect(m_controller, &IHvacController::stateChanged,
                this, &HvacViewModel::onStateChanged);
        m_state = m_controller->currentState();
        emit stateChanged();
    }
}

void HvacViewModel::setDriverTemperature(double temp)
{
    if (m_controller) m_controller->setDriverTemperature(temp);
}

void HvacViewModel::setPassengerTemperature(double temp)
{
    if (m_controller) m_controller->setPassengerTemperature(temp);
}

void HvacViewModel::setFanSpeed(int level)
{
    if (m_controller) m_controller->setFanSpeed(level);
}

void HvacViewModel::setAirflowMode(int mode)
{
    if (m_controller) m_controller->setAirflowMode(static_cast<AirflowMode>(mode));
}

void HvacViewModel::toggleAc()
{
    if (m_controller) m_controller->setAcEnabled(!m_state.isAcOn);
}

void HvacViewModel::toggleRecirc()
{
    if (m_controller) m_controller->setRecirculationEnabled(!m_state.isRecircOn);
}

void HvacViewModel::toggleSync()
{
    if (m_controller) m_controller->setSyncEnabled(!m_state.isSyncOn);
}

void HvacViewModel::increaseDriverTemp()
{
    setDriverTemperature(m_state.driverTemp + 0.5);
}

void HvacViewModel::decreaseDriverTemp()
{
    setDriverTemperature(m_state.driverTemp - 0.5);
}

void HvacViewModel::increasePassengerTemp()
{
    setPassengerTemperature(m_state.passengerTemp + 0.5);
}

void HvacViewModel::decreasePassengerTemp()
{
    setPassengerTemperature(m_state.passengerTemp - 0.5);
}

void HvacViewModel::onStateChanged(const hmi::HvacState &state)
{
    m_state = state;
    emit stateChanged();
}

} // namespace hmi
