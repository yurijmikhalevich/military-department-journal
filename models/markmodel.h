#ifndef MARKMODEL_H
#define MARKMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

class MarkModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit MarkModel(QObject *parent = 0);
};

#endif // MARKMODEL_H
