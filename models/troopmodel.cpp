#include "troopmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QTimer>

TroopModel::TroopModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("troop");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(4, QSqlRelation("teacher", "id", "name"));
  setRelation(5, QSqlRelation("military_profession", "id", "name"));
  setHeaderData(1, Qt::Horizontal, tr("Name"));
  setHeaderData(2, Qt::Horizontal, tr("Entered in"));
  setHeaderData(3, Qt::Horizontal,
                tr("Graduated in",
                   "Year of graduation from Faculty of Military Training"));
  setHeaderData(4, Qt::Horizontal, tr("Curator"));
  setHeaderData(5, Qt::Horizontal, tr("Profession"));
  setHeaderData(6, Qt::Horizontal, tr("Students"));
  select();
}

QVariant TroopModel::data(const QModelIndex &item, int role) const {
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

Qt::ItemFlags TroopModel::flags(const QModelIndex &index) const {
  if (index.column() == 6) {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return SteroidsModel<QSqlRelationalTableModel>::flags(index);
}

int TroopModel::columnCount(const QModelIndex &) const {
  return 6;
}

void TroopModel::queryChanged(QString query) {
  qDebug() << "TroopModel" <<
              "queryChanged should be implemented" <<
              query;
}
