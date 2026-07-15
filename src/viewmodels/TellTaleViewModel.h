#ifndef VIEWMODELS_TELLTALEVIEWMODEL_H
#define VIEWMODELS_TELLTALEVIEWMODEL_H

#include <QAbstractListModel>
#include <QtQmlIntegration/qqmlintegration.h>
#include <core/VehicleData.h>
#include <array>

namespace hmi {

class TellTaleViewModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        IconSourceRole,
        StateRole,
        IsActiveRole,
        ColorRole,
        IsBlinkingRole
    };

    explicit TellTaleViewModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void onTellTaleChanged(hmi::TellTaleId id, hmi::TellTaleState state);

private:
    struct TellTaleInfo {
        TellTaleId    id;
        QString       name;
        QString       iconSource;
        TellTaleState state = TellTaleState::Off;
        QString       activeColor;
    };

    static QString colorForTellTale(TellTaleId id);
    static QString nameForTellTale(TellTaleId id);
    static QString iconForTellTale(TellTaleId id);

    std::array<TellTaleInfo, static_cast<size_t>(TellTaleId::Count)> m_tellTales;
};

} // namespace hmi

#endif // VIEWMODELS_TELLTALEVIEWMODEL_H
