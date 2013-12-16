#ifndef SUBJECTDURATIONMODEL_H
#define SUBJECTDURATIONMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

class SubjectDurationModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit SubjectDurationModel(QObject *parent = 0);
};

#endif // SUBJECTDURATIONMODEL_H
