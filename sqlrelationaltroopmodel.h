#ifndef SQLRELATIONALTROOPMODEL_H
#define SQLRELATIONALTROOPMODEL_H

#include <QSqlRelationalTableModel>

/**
 * @brief The SqlRelationalTroopModel class
 */
class SqlRelationalTroopModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit SqlRelationalTroopModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;

private slots:
    void addCalculatedColumns();
};

#endif // SQLRELATIONALTROOPMODEL_H
