#include "subjectmodel.h"

SubjectModel::SubjectModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("subject");
    setHeaderData(1, Qt::Horizontal, tr("Предмет"));
    select();
}
