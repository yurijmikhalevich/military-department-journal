#ifndef MILITARYPROFESSIONMODEL_H
#define MILITARYPROFESSIONMODEL_H

#include <QSqlTableModel>

#include "qt4table-steroids/steroidsmodel.h"

class MilitaryProfessionModel : public SteroidsModel<QSqlTableModel>
{
    Q_OBJECT
public:
    explicit MilitaryProfessionModel(QObject *parent = 0);

public slots:
    void queryChanged(QString query);
    
};

#endif // MILITARYPROFESSIONMODEL_H
