#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include "qt4table-steroids/steroidsmodel.h"

class StudentModel : public SteroidsModel<QSqlRelationalTableModel>
{
    Q_OBJECT
public:
    explicit StudentModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // STUDENTMODEL_H
