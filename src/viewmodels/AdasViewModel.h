#ifndef VIEWMODELS_ADASVIEWMODEL_H
#define VIEWMODELS_ADASVIEWMODEL_H

#include <QAbstractListModel>

#include <core/AdasData.h>
#include <core/IAdasProcessingStrategy.h>
#include <memory>

namespace hmi {

class AdasViewModel : public QAbstractListModel
{
    Q_OBJECT


    Q_PROPERTY(int objectCount READ objectCount NOTIFY objectCountChanged)
    Q_PROPERTY(QString strategyName READ strategyName NOTIFY strategyChanged)

public:
    enum Roles {
        XRole = Qt::UserRole + 1,
        YRole,
        WidthRole,
        HeightRole,
        ObjectClassRole,
        ClassNameRole,
        ConfidenceRole,
        TrackIdRole,
        ColorRole
    };

    explicit AdasViewModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int objectCount() const { return static_cast<int>(m_objects.size()); }
    QString strategyName() const;

    void setProcessingStrategy(std::unique_ptr<IAdasProcessingStrategy> strategy);

public slots:
    void onFrameReceived(const hmi::AdasFrame &frame);

signals:
    void objectCountChanged();
    void strategyChanged();

private:
    static QString classToName(ObjectClass cls);
    static QString classToColor(ObjectClass cls);

    std::vector<DetectedObject> m_objects;
    std::unique_ptr<IAdasProcessingStrategy> m_strategy;
};

} // namespace hmi

#endif // VIEWMODELS_ADASVIEWMODEL_H
