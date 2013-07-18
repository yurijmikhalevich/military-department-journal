#ifndef TEACHERSMODEL_H
#define TEACHERSMODEL_H

#include <QSqlTableModel>
#include <QHash>

#include "qt4table-steroids/steroidsmodel.h"

class TeachersModel : public SteroidsModel<QSqlTableModel>
{
    Q_OBJECT
public:
    explicit TeachersModel(QObject *parent = 0);

public slots:
    void showDismissed(bool show);
    void queryChanged(QString query);
    
};

#endif // TEACHERSMODEL_H
