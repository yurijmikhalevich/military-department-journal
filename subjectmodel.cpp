#include "subjectmodel.h"

SubjectModel::SubjectModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("subject");
    setHeaderData(1, Qt::Horizontal, tr("Subject"));
    setHeaderData(2, Qt::Horizontal, tr("Duration"));
//    setHeaderData(3, Qt::Horizontal, tr("Archived"));
    select();
}
