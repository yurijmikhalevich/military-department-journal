#ifndef TROOPMODEL_H
#define TROOPMODEL_H

#include <QSqlRelationalTableModel>

/**
 * @brief The TroopModel class
 */
class TroopModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit TroopModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

private slots:
    void addCalculatedColumns();
};

#endif // TROOPMODEL_H
