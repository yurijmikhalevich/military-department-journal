#ifndef UNIVERSITYGROUPMODEL_H
#define UNIVERSITYGROUPMODEL_H

#include <QSqlTableModel>

#include "qt4table-steroids/steroidsmodel.h"

class UniversityGroupModel : public SteroidsModel<QSqlTableModel>
{
    Q_OBJECT
public:
    explicit UniversityGroupModel(QObject *parent = 0);
    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int columnCount(const QModelIndex &parent) const;
    
};

#include <QSortFilterProxyModel>

class TestSort : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit TestSort(QObject *parent = 0) :
        QSortFilterProxyModel(parent) {}
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const
    {
        if (left.column() == 3) {
            return left.data().toInt() < right.data().toInt();
        }
        return QSortFilterProxyModel::lessThan(left, right);
    }
};

#endif // UNIVERSITYGROUPMODEL_H
