#include "subjectdurationmodel.h"

SubjectDurationModel::SubjectDurationModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("subject_duration");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(0, QSqlRelation("subject", "id", "name"));
  setRelation(1, QSqlRelation("military_profession", "id", "name"));
  setHeaderData(0, Qt::Horizontal, tr("Subject"));
  setHeaderData(1, Qt::Horizontal, tr("Profession"));
  setHeaderData(2, Qt::Horizontal, tr("Duration", "Subject duration in hours"));
  select();
}
