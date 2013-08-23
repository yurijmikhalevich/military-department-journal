#include "studentmodel.h"

StudentModel::StudentModel(QObject *parent) :
    SteroidsModel<QSqlRelationalTableModel>(parent)
{
}
