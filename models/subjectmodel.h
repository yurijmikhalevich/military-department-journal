#ifndef SUBJECTMODEL_H
#define SUBJECTMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlTableModel>

class SubjectModel : public SteroidsModel<QSqlTableModel> {
  Q_OBJECT
public:
  explicit SubjectModel(QObject *parent = 0);
};

#endif // SUBJECTMODEL_H
