#include "teachermodel.h"
#include <QStringList>
#include <QSqlRecord>
#include <QDebug>

TeacherModel::TeacherModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  this->setTable("teacher");
  this->setHeaderData(1, Qt::Horizontal, tr("Статус"));
  this->setHeaderData(2, Qt::Horizontal, tr("Имя"));
  this->showDismissed(false);
}

QVariant TeacherModel::data(const QModelIndex &idx, int role) const {
  if (idx.column() == 1 && role == Qt::DisplayRole) {
    if (idx.data(Qt::EditRole).toBool()) {
      return tr("Уволен");
    } else {
      return tr("Работает");
    }
  }
  return SteroidsModel<QSqlTableModel>::data(idx, role);
}

void TeacherModel::showDismissed(bool show) {
  if (show) {
    filters.remove("dismissed");
  } else {
    filters.insert("dismissed", "dismissed = 0");
  }
  compileFilters();
}

void TeacherModel::queryChanged(QString query) {
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
