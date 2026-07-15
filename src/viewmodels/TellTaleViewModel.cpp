#include "TellTaleViewModel.h"

namespace hmi {

TellTaleViewModel::TellTaleViewModel(QObject *parent)
    : QAbstractListModel(parent)
{
    for (int i = 0; i < static_cast<int>(TellTaleId::Count); ++i) {
        auto id = static_cast<TellTaleId>(i);
        m_tellTales[static_cast<size_t>(i)] = {
            id,
            nameForTellTale(id),
            iconForTellTale(id),
            TellTaleState::Off,
            colorForTellTale(id)
        };
    }
}

int TellTaleViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(TellTaleId::Count);
}

QVariant TellTaleViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
        index.row() >= static_cast<int>(TellTaleId::Count))
        return {};

    const auto &tt = m_tellTales[static_cast<size_t>(index.row())];

    switch (role) {
    case NameRole:       return tt.name;
    case IconSourceRole: return tt.iconSource;
    case StateRole:      return static_cast<int>(tt.state);
    case IsActiveRole:   return tt.state != TellTaleState::Off;
    case ColorRole:      return tt.activeColor;
    case IsBlinkingRole: return tt.state == TellTaleState::Blinking;
    default:             return {};
    }
}

QHash<int, QByteArray> TellTaleViewModel::roleNames() const
{
    return {
        { NameRole,       "name" },
        { IconSourceRole, "iconSource" },
        { StateRole,      "state" },
        { IsActiveRole,   "isActive" },
        { ColorRole,      "color" },
        { IsBlinkingRole, "isBlinking" }
    };
}

void TellTaleViewModel::onTellTaleChanged(hmi::TellTaleId id, hmi::TellTaleState state)
{
    int row = static_cast<int>(id);
    if (row < 0 || row >= static_cast<int>(TellTaleId::Count))
        return;

    m_tellTales[static_cast<size_t>(row)].state = state;

    QModelIndex idx = index(row);
    emit dataChanged(idx, idx, { StateRole, IsActiveRole, IsBlinkingRole });
}

QString TellTaleViewModel::colorForTellTale(TellTaleId id)
{
    switch (id) {
    case TellTaleId::CheckEngine:    return QStringLiteral("#FFB800");  // amber
    case TellTaleId::ABS:            return QStringLiteral("#FFB800");
    case TellTaleId::TirePressure:   return QStringLiteral("#FFB800");
    case TellTaleId::Seatbelt:       return QStringLiteral("#FF3D57");  // red
    case TellTaleId::BrakeWarning:   return QStringLiteral("#FF3D57");
    case TellTaleId::HighBeam:       return QStringLiteral("#00D4FF");  // blue
    case TellTaleId::TurnSignalLeft: return QStringLiteral("#00E676");  // green
    case TellTaleId::TurnSignalRight:return QStringLiteral("#00E676");
    case TellTaleId::Battery:        return QStringLiteral("#FF3D57");
    case TellTaleId::OilPressure:    return QStringLiteral("#FF3D57");
    case TellTaleId::Temperature:    return QStringLiteral("#FF3D57");
    case TellTaleId::DoorAjar:       return QStringLiteral("#FFB800");
    case TellTaleId::Airbag:         return QStringLiteral("#FF3D57");
    case TellTaleId::TractionControl:return QStringLiteral("#FFB800");
    default:                         return QStringLiteral("#FFFFFF");
    }
}

QString TellTaleViewModel::nameForTellTale(TellTaleId id)
{
    switch (id) {
    case TellTaleId::CheckEngine:    return QStringLiteral("Check Engine");
    case TellTaleId::ABS:            return QStringLiteral("ABS");
    case TellTaleId::TirePressure:   return QStringLiteral("Tire Pressure");
    case TellTaleId::Seatbelt:       return QStringLiteral("Seatbelt");
    case TellTaleId::BrakeWarning:   return QStringLiteral("Brake");
    case TellTaleId::HighBeam:       return QStringLiteral("High Beam");
    case TellTaleId::TurnSignalLeft: return QStringLiteral("Left Turn");
    case TellTaleId::TurnSignalRight:return QStringLiteral("Right Turn");
    case TellTaleId::Battery:        return QStringLiteral("Battery");
    case TellTaleId::OilPressure:    return QStringLiteral("Oil Pressure");
    case TellTaleId::Temperature:    return QStringLiteral("Temperature");
    case TellTaleId::DoorAjar:       return QStringLiteral("Door Ajar");
    case TellTaleId::Airbag:         return QStringLiteral("Airbag");
    case TellTaleId::TractionControl:return QStringLiteral("Traction Ctrl");
    default:                         return QStringLiteral("Unknown");
    }
}

QString TellTaleViewModel::iconForTellTale(TellTaleId id)
{
    // SVG icon names — will be matched to actual files in resources
    switch (id) {
    case TellTaleId::CheckEngine:    return QStringLiteral("engine");
    case TellTaleId::ABS:            return QStringLiteral("abs");
    case TellTaleId::TirePressure:   return QStringLiteral("tire");
    case TellTaleId::Seatbelt:       return QStringLiteral("seatbelt");
    case TellTaleId::BrakeWarning:   return QStringLiteral("brake");
    case TellTaleId::HighBeam:       return QStringLiteral("highbeam");
    case TellTaleId::TurnSignalLeft: return QStringLiteral("turn_left");
    case TellTaleId::TurnSignalRight:return QStringLiteral("turn_right");
    case TellTaleId::Battery:        return QStringLiteral("battery");
    case TellTaleId::OilPressure:    return QStringLiteral("oil");
    case TellTaleId::Temperature:    return QStringLiteral("temperature");
    case TellTaleId::DoorAjar:       return QStringLiteral("door");
    case TellTaleId::Airbag:         return QStringLiteral("airbag");
    case TellTaleId::TractionControl:return QStringLiteral("traction");
    default:                         return QStringLiteral("warning");
    }
}

} // namespace hmi
