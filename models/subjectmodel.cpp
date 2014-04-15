#include "subjectmodel.h"

SubjectModel::SubjectModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  setTable("subject");
  setHeaderData(1, Qt::Horizontal, tr("Статус"));
  setHeaderData(2, Qt::Horizontal, tr("Название"));
  select();
  showArchived(false);
}

QVariant SubjectModel::data(const QModelIndex &idx, int role) const {
  if (idx.column() == 1 && role == Qt::DisplayRole) {
    if (idx.data(Qt::EditRole).toBool()) {
      return tr("В архиве");
    } else {
      return tr("Действителен");
    }
  }
  return SteroidsModel<QSqlTableModel>::data(idx, role);
}

void SubjectModel::showArchived(bool show) {
  if (show) {
    filters.remove("archived");
  } else {
    filters.insert("archived", "archived = 0");
  }
  compileFilters();
}
