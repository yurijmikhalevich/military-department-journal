#include "studentmodel.h"

StudentModel::StudentModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("student");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(11, QSqlRelation("university_group", "id", "name"));
  setRelation(14, QSqlRelation("expulsion_reason", "id", "reason"));
  setRelation(15, QSqlRelation("expulsed_from", "id", "unit"));
  setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
  setHeaderData(2, Qt::Horizontal, tr("Имя"));
  setHeaderData(3, Qt::Horizontal, tr("Отчество"));
  setHeaderData(4, Qt::Horizontal, tr("Фамилия (дат)"));
  setHeaderData(5, Qt::Horizontal, tr("Имя (дат)"));
  setHeaderData(6, Qt::Horizontal, tr("Отчество (дат)"));
  setHeaderData(7, Qt::Horizontal, tr("Фамилия (вин)"));
  setHeaderData(8, Qt::Horizontal, tr("Имя (вин)"));
  setHeaderData(9, Qt::Horizontal, tr("Отчество (вин)"));
  setHeaderData(10, Qt::Horizontal, tr("Дата рождения"));
  setHeaderData(11, Qt::Horizontal, tr("Группа"));
  setHeaderData(12, Qt::Horizontal, tr("Приказ о зачислении"));
  setHeaderData(13, Qt::Horizontal, tr("Приказ об отчислении"));
  setHeaderData(14, Qt::Horizontal, tr("Причина отчисления"));
  setHeaderData(15, Qt::Horizontal, tr("Отчислен из"));
  select();
}

void StudentModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    filters.insert("query",
                   QString("lastname LIKE '%%1%'").arg(query));
  }
  compileFilters();
}
