#ifndef UNIVERSITYFACULTYMODEL_H
#define UNIVERSITYFACULTYMODEL_H

#include <QSqlTableModel>
#include <QHash>
#include "qt4table-steroids/steroidsmodel.h"

class UniversityFacultyModel : public SteroidsModel<QSqlTableModel> {
  Q_OBJECT
public:
  explicit UniversityFacultyModel(QObject *parent = 0);
public slots:
  void showArchived(bool show);
  void queryChanged(QString query);
};

#endif // UNIVERSITYFACULTYMODEL_H
