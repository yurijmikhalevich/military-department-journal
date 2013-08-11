#include "troopmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QTimer>

TroopModel::TroopModel(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    connect(this, SIGNAL(modelReset()), this, SLOT(addCalculatedColumns()));
    this->setTable("troop");
    this->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    this->setRelation(5, QSqlRelation("teacher", "id", "name"));
    this->setHeaderData(1, Qt::Horizontal, tr("Troop"));
//    this->setHeaderData(2, Qt::Horizontal, tr("Year of training"));
    this->setHeaderData(3, Qt::Horizontal, tr("YGM", "Year of graduation from Faculty of Military Training"));
    this->setHeaderData(4, Qt::Horizontal, tr("Graduated"));
    this->setHeaderData(5, Qt::Horizontal, tr("Curator"));
    this->select();
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
    return QSqlRelationalTableModel::data(item, role);
}

void TroopModel::addCalculatedColumns()
{
    this->insertColumn(6);
    this->setHeaderData(6, Qt::Horizontal, tr("Number of students"));
}
