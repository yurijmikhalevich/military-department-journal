#include "evaluationmodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

EvaluationModel::EvaluationModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("evaluation");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(2, QSqlRelation("subject", "id", "name"));
  setRelation(4, QSqlRelation("control_type", "id", "type"));
  setRelation(5, QSqlRelation("teacher", "id", "name"));
  setHeaderData(1, Qt::Horizontal, tr("Дата"));
  setHeaderData(2, Qt::Horizontal, tr("Предмет"));
  setHeaderData(3, Qt::Horizontal, tr("Взвод"));
  setHeaderData(4, Qt::Horizontal, tr("Тип контроля"));
  setHeaderData(5, Qt::Horizontal, tr("Преподаватель"));
  setSort(1, Qt::DescendingOrder);
  select();
}

QVariant EvaluationModel::data(const QModelIndex &item, int role) const {
  if (item.column() == 3 && role == Qt::DisplayRole) {
    QSqlQuery query = QSqlQuery(QSqlDatabase::database("troops"));
    query.prepare("SELECT name FROM troop WHERE id = ?");
    query.addBindValue(item.data(Qt::EditRole));
    if (!query.exec() || !query.next()) {
      if (query.lastError().isValid()) {
        qCritical() << query.lastError().text();
      }
      return QVariant();
    }
    return query.record().value("name");
  }
  return SteroidsModel<QSqlRelationalTableModel>::data(item, role);
}
