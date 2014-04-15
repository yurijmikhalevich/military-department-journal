#include "militaryprofessionmodel.h"
#include <QSqlRecord>
#include <QDebug>

MilitaryProfessionModel::MilitaryProfessionModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  setTable("military_profession");
  setHeaderData(1, Qt::Horizontal, tr("Статус"));
  setHeaderData(2, Qt::Horizontal, tr("Номер"));
  setHeaderData(3, Qt::Horizontal, tr("Название"));
  showArchived(false);
  select();
}

QVariant MilitaryProfessionModel::data(
    const QModelIndex &idx, int role) const {
  if (idx.column() == 1 && role == Qt::DisplayRole) {
    if (idx.data(Qt::EditRole).toBool()) {
      return tr("В архиве");
    } else {
      return tr("Действителен");
    }
  }
  return SteroidsModel<QSqlTableModel>::data(idx, role);
}

void MilitaryProfessionModel::showArchived(bool show) {
  if (show) {
    filters.remove("archived");
  } else {
    filters.insert("archived", "archived = 0");
  }
  compileFilters();
}

void MilitaryProfessionModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    query = query.simplified();
    filters.insert("query",
                   QString("(name LIKE '%%1%' OR code LIKE '%%1%')").arg(
                     query));
  }
  compileFilters();
}
