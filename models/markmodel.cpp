#include "markmodel.h"

MarkModel::MarkModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("mark");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(0, QSqlRelation("evaluation", "id", "name"));
  setRelation(1, QSqlRelation("student", "id", "lastname"));
  setRelation(3, QSqlRelation("teacher", "id", "name"));
  setHeaderData(0, Qt::Horizontal, tr("Evaluation"));
  setHeaderData(1, Qt::Horizontal, tr("Student"));
  setHeaderData(2, Qt::Horizontal, tr("Value"));
  setHeaderData(3, Qt::Horizontal, tr("Teacher"));
  setHeaderData(4, Qt::Horizontal, tr("Date"));
  select();
}
