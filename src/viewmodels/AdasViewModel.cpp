#include "AdasViewModel.h"

namespace hmi {

AdasViewModel::AdasViewModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int AdasViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return static_cast<int>(m_objects.size());
}

QVariant AdasViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 ||
        index.row() >= static_cast<int>(m_objects.size()))
        return {};

    const auto &obj = m_objects[static_cast<size_t>(index.row())];

    switch (role) {
    case XRole:           return static_cast<double>(obj.box.x);
    case YRole:           return static_cast<double>(obj.box.y);
    case WidthRole:       return static_cast<double>(obj.box.width);
    case HeightRole:      return static_cast<double>(obj.box.height);
    case ObjectClassRole: return static_cast<int>(obj.cls);
    case ClassNameRole:   return classToName(obj.cls);
    case ConfidenceRole:  return static_cast<double>(obj.confidence);
    case TrackIdRole:     return obj.trackId;
    case ColorRole:       return classToColor(obj.cls);
    default:              return {};
    }
}

QHash<int, QByteArray> AdasViewModel::roleNames() const
{
    return {
        { XRole,           "boxX" },
        { YRole,           "boxY" },
        { WidthRole,       "boxWidth" },
        { HeightRole,      "boxHeight" },
        { ObjectClassRole, "objectClass" },
        { ClassNameRole,   "className" },
        { ConfidenceRole,  "confidence" },
        { TrackIdRole,     "trackId" },
        { ColorRole,       "boxColor" }
    };
}

QString AdasViewModel::strategyName() const
{
    return m_strategy ? m_strategy->name() : QStringLiteral("None");
}

void AdasViewModel::setProcessingStrategy(std::unique_ptr<IAdasProcessingStrategy> strategy)
{
    m_strategy = std::move(strategy);
    emit strategyChanged();
}

void AdasViewModel::onFrameReceived(const hmi::AdasFrame &frame)
{
    AdasFrame processed = m_strategy ? m_strategy->process(frame) : frame;

    beginResetModel();
    m_objects = processed.objects;
    endResetModel();

    emit objectCountChanged();
}

QString AdasViewModel::classToName(ObjectClass cls)
{
    switch (cls) {
    case ObjectClass::Vehicle:      return QStringLiteral("Vehicle");
    case ObjectClass::Pedestrian:   return QStringLiteral("Pedestrian");
    case ObjectClass::Cyclist:      return QStringLiteral("Cyclist");
    case ObjectClass::TrafficSign:  return QStringLiteral("Traffic Sign");
    case ObjectClass::TrafficLight: return QStringLiteral("Traffic Light");
    default:                        return QStringLiteral("Unknown");
    }
}

QString AdasViewModel::classToColor(ObjectClass cls)
{
    switch (cls) {
    case ObjectClass::Vehicle:      return QStringLiteral("#00E676");  // green
    case ObjectClass::Pedestrian:   return QStringLiteral("#FFD740");  // yellow
    case ObjectClass::Cyclist:      return QStringLiteral("#FF6E40");  // orange
    case ObjectClass::TrafficSign:  return QStringLiteral("#448AFF");  // blue
    case ObjectClass::TrafficLight: return QStringLiteral("#E040FB");  // purple
    default:                        return QStringLiteral("#FFFFFF");
    }
}

} // namespace hmi
