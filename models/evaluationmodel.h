#ifndef EVALUATIONMODEL_H
#define EVALUATIONMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

class EvaluationModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit EvaluationModel(QObject *parent = 0);
  QVariant data(const QModelIndex &item, int role) const;
};

#endif // EVALUATIONMODEL_H
