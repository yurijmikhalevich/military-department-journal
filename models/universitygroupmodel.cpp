#include "universitygroupmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QDate>

UniversityGroupModel::UniversityGroupModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("university_group");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(3, QSqlRelation("university_faculty", "id", "name"));
  setHeaderData(1, Qt::Horizontal, tr("Номер"));
  setHeaderData(2, Qt::Horizontal, tr("Год выпуска"));
  setHeaderData(3, Qt::Horizontal, tr("Факультет"));
  setHeaderData(4, Qt::Horizontal, tr("Взвод"));
  setHeaderData(5, Qt::Horizontal, tr("Кол-во студентов"));
  showGraduated(false);
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
  if (item.column() == 4 && role == Qt::DisplayRole) {
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

Qt::ItemFlags UniversityGroupModel::flags(const QModelIndex &index) const {
  if (index.column() == 5) {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return SteroidsModel<QSqlRelationalTableModel>::flags(index);
}

int UniversityGroupModel::columnCount(const QModelIndex &) const {
  return 6;
}

void UniversityGroupModel::showGraduated(bool show) {
  if (show) {
    filters.remove("graduated");
  } else {
    int year = QDate::currentDate().year();
    filters.insert("graduated", "graduated_from_university_year >= " +
                   QString::number(year));
  }
  compileFilters();
}

void UniversityGroupModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    filters.insert("query", QString("name LIKE '%%1%'").arg(query));
  }
  compileFilters();
}
