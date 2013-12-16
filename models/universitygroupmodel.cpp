#include "universitygroupmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>

UniversityGroupModel::UniversityGroupModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("university_group");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(3, QSqlRelation("university_faculty", "id", "name"));
  setRelation(4, QSqlRelation("troop", "id", "name"));
  setHeaderData(1, Qt::Horizontal, tr("Name"));
  setHeaderData(2, Qt::Horizontal, tr("Graduated in"));
  setHeaderData(3, Qt::Horizontal, tr("Faculty"));
  setHeaderData(4, Qt::Horizontal, tr("Troop"));
  setHeaderData(5, Qt::Horizontal, tr("Students"));
}

QVariant UniversityGroupModel::data(const QModelIndex &item, int role) const {
  if (item.column() == 5 && role == Qt::DisplayRole) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS count FROM student"
                  " WHERE university_group_id = ?");
    query.addBindValue(this->record(item.row()).value("id"));
    if (query.exec() && query.next()) {
      return query.record().value("count");
    }
    return QVariant();
  }
  return SteroidsModel<QSqlRelationalTableModel>::data(item, role);
}

Qt::ItemFlags UniversityGroupModel::flags(const QModelIndex &index) const {
  if (index.column() == 5) {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return SteroidsModel<QSqlRelationalTableModel>::flags(index);
}

int UniversityGroupModel::columnCount(const QModelIndex &) const {
  return 6;
}

void UniversityGroupModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    filters.insert("query", QString("name = '%1'").arg(query));
  }
  compileFilters();
}
