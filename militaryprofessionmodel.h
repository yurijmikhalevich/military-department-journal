#ifndef MILITARYPROFESSIONMODEL_H
#define MILITARYPROFESSIONMODEL_H

#include <QSqlTableModel>

#include "qt4table-steroids/steroidsmodel.h"

class MilitaryProfessionModel : public SteroidsModel<QSqlTableModel>
{
    Q_OBJECT
public:
    explicit MilitaryProfessionModel(QObject *parent = 0);
//    QVariant data(const QModelIndex &item, int role) const;
//    Qt::ItemFlags flags(const QModelIndex &index) const;
//    int columnCount(const QModelIndex &) const;

public slots:
    void queryChanged(QString query);
    
};

#endif // MILITARYPROFESSIONMODEL_H
