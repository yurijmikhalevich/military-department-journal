#include "universityfacultymodel.h"
#include <QStringList>
#include <QDebug>
#include <QSqlRecord>

UniversityFacultyModel::UniversityFacultyModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  this->setTable("university_faculty");
  this->setHeaderData(1, Qt::Horizontal, tr("Статус"));
  this->setHeaderData(2, Qt::Horizontal, tr("Название"));
  this->showArchived(false);
}

QVariant UniversityFacultyModel::data(const QModelIndex &idx, int role) const {
  if (idx.column() == 1 && role == Qt::DisplayRole) {
    if (idx.data(Qt::EditRole).toBool()) {
      return tr("В архиве");
    } else {
      return tr("Действителен");
    }
  }
  return SteroidsModel<QSqlTableModel>::data(idx, role);
}

void UniversityFacultyModel::showArchived(bool show) {
  if (show) {
    filters.remove("archived");
  } else {
    filters.insert("archived", "archived = 0");
  }
  compileFilters();
}

void UniversityFacultyModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    query = query.simplified();
    filters.insert("query",
                   QString("(name LIKE '%%1%' OR name LIKE '%%2%')").arg(
                     query.at(0).toUpper() + query.mid(1),
                     query));
  }
  compileFilters();
}
