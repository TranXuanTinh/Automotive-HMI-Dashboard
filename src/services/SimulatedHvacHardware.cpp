#include "SimulatedHvacHardware.h"
#include <cmath>

namespace hmi {

SimulatedHvacHardware::SimulatedHvacHardware(QObject *parent)
    : IHvacController(parent)
{
    m_responseTimer.setInterval(500);
    connect(&m_responseTimer, &QTimer::timeout, this, &SimulatedHvacHardware::simulateResponse);
    m_responseTimer.start();
}

void SimulatedHvacHardware::setDriverTemperature(double tempC)
{
    m_targetDriverTemp = std::clamp(tempC, 16.0, 30.0);
    if (m_state.isSyncOn)
        m_targetPassengerTemp = m_targetDriverTemp;
}

void SimulatedHvacHardware::setPassengerTemperature(double tempC)
{
    m_targetPassengerTemp = std::clamp(tempC, 16.0, 30.0);
}

void SimulatedHvacHardware::setFanSpeed(int level)
{
    m_state.fanSpeed = std::clamp(level, 0, 7);
    emit stateChanged(m_state);
}

void SimulatedHvacHardware::setAirflowMode(AirflowMode mode)
{
    m_state.airflowMode = mode;
    emit stateChanged(m_state);
}

void SimulatedHvacHardware::setAcEnabled(bool enabled)
{
    m_state.isAcOn = enabled;
    emit stateChanged(m_state);
}

void SimulatedHvacHardware::setRecirculationEnabled(bool enabled)
{
    m_state.isRecircOn = enabled;
    emit stateChanged(m_state);
}

void SimulatedHvacHardware::setSyncEnabled(bool enabled)
{
    m_state.isSyncOn = enabled;
    if (enabled)
        m_targetPassengerTemp = m_targetDriverTemp;
    emit stateChanged(m_state);
}

HvacState SimulatedHvacHardware::currentState() const
{
    return m_state;
}

void SimulatedHvacHardware::simulateResponse()
{
    bool changed = false;
    constexpr double step = 0.5;

    if (std::abs(m_state.driverTemp - m_targetDriverTemp) > 0.1) {
        if (m_state.driverTemp < m_targetDriverTemp)
            m_state.driverTemp = std::min(m_state.driverTemp + step, m_targetDriverTemp);
        else
            m_state.driverTemp = std::max(m_state.driverTemp - step, m_targetDriverTemp);
        changed = true;
    }

    if (std::abs(m_state.passengerTemp - m_targetPassengerTemp) > 0.1) {
        if (m_state.passengerTemp < m_targetPassengerTemp)
            m_state.passengerTemp = std::min(m_state.passengerTemp + step, m_targetPassengerTemp);
        else
            m_state.passengerTemp = std::max(m_state.passengerTemp - step, m_targetPassengerTemp);
        changed = true;
    }

    if (changed)
        emit stateChanged(m_state);
}

} // namespace hmi
