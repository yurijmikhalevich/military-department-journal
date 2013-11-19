#include "troopmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QTimer>

TroopModel::TroopModel(QObject *parent) :
    SteroidsModel<QSqlRelationalTableModel>(parent)
{
    setTable("troop");
    setJoinMode(QSqlRelationalTableModel::LeftJoin);
    setRelation(5, QSqlRelation("teacher", "id", "name"));
    setHeaderData(1, Qt::Horizontal, tr("Troop"));
    setHeaderData(2, Qt::Horizontal, tr("Year of training"));
    setHeaderData(3, Qt::Horizontal, tr("YGM", "Year of graduation from Faculty of Military Training"));
    setHeaderData(4, Qt::Horizontal, tr("Graduated"));
    setHeaderData(5, Qt::Horizontal, tr("Curator"));
    select();
}

QVariant TroopModel::data(const QModelIndex &item, int role) const
{
    if (item.column() == 6 && role == Qt::DisplayRole) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) AS count FROM student WHERE troop_id = ?");
        query.addBindValue(this->record(item.row()).value("id"));
        if (query.exec() && query.next()) {
            return query.record().value("count");
        }
        return QVariant();
    }
    return SteroidsModel<QSqlRelationalTableModel>::data(item, role);
}

Qt::ItemFlags TroopModel::flags(const QModelIndex &index) const
{
    if (index.column() == 6) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return SteroidsModel<QSqlRelationalTableModel>::flags(index);
}

int TroopModel::columnCount(const QModelIndex &) const
{
    return 7;
}

void TroopModel::queryChanged(QString query)
{

}
