#include "subjectmodel.h"

SubjectModel::SubjectModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  setTable("subject");
  setHeaderData(1, Qt::Horizontal, tr("Archived"));
  setHeaderData(2, Qt::Horizontal, tr("Name", "Subject name"));
  select();
}
