#ifndef VIEWMODELS_HVACVIEWMODEL_H
#define VIEWMODELS_HVACVIEWMODEL_H

#include <QObject>

#include <core/HvacData.h>

namespace hmi {

class IHvacController;

class HvacViewModel : public QObject
{
    Q_OBJECT


    Q_PROPERTY(double driverTemp READ driverTemp NOTIFY stateChanged)
    Q_PROPERTY(double passengerTemp READ passengerTemp NOTIFY stateChanged)
    Q_PROPERTY(int fanSpeed READ fanSpeed NOTIFY stateChanged)
    Q_PROPERTY(bool isAcOn READ isAcOn NOTIFY stateChanged)
    Q_PROPERTY(bool isRecircOn READ isRecircOn NOTIFY stateChanged)
    Q_PROPERTY(bool isSyncOn READ isSyncOn NOTIFY stateChanged)
    Q_PROPERTY(int airflowMode READ airflowMode NOTIFY stateChanged)
    Q_PROPERTY(double minTemp READ minTemp CONSTANT)
    Q_PROPERTY(double maxTemp READ maxTemp CONSTANT)
    Q_PROPERTY(int maxFanSpeed READ maxFanSpeed CONSTANT)

public:
    explicit HvacViewModel(QObject *parent = nullptr);

    void setController(IHvacController *controller);

    double driverTemp() const { return m_state.driverTemp; }
    double passengerTemp() const { return m_state.passengerTemp; }
    int fanSpeed() const { return m_state.fanSpeed; }
    bool isAcOn() const { return m_state.isAcOn; }
    bool isRecircOn() const { return m_state.isRecircOn; }
    bool isSyncOn() const { return m_state.isSyncOn; }
    int airflowMode() const { return static_cast<int>(m_state.airflowMode); }
    double minTemp() const { return 16.0; }
    double maxTemp() const { return 30.0; }
    int maxFanSpeed() const { return 7; }

    Q_INVOKABLE void setDriverTemperature(double temp);
    Q_INVOKABLE void setPassengerTemperature(double temp);
    Q_INVOKABLE void setFanSpeed(int level);
    Q_INVOKABLE void setAirflowMode(int mode);
    Q_INVOKABLE void toggleAc();
    Q_INVOKABLE void toggleRecirc();
    Q_INVOKABLE void toggleSync();
    Q_INVOKABLE void increaseDriverTemp();
    Q_INVOKABLE void decreaseDriverTemp();
    Q_INVOKABLE void increasePassengerTemp();
    Q_INVOKABLE void decreasePassengerTemp();

public slots:
    void onStateChanged(const hmi::HvacState &state);

signals:
    void stateChanged();

private:
    IHvacController *m_controller = nullptr;
    HvacState        m_state;
};

} // namespace hmi

#endif // VIEWMODELS_HVACVIEWMODEL_H
