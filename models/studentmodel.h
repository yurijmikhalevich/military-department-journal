#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

class StudentModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit StudentModel(QObject *parent = 0);
public slots:
  void queryChanged(QString query);
};

#endif // STUDENTMODEL_H
