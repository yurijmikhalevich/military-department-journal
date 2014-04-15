#ifndef TEACHERMODEL_H
#define TEACHERMODEL_H

#include <QSqlTableModel>
#include <QHash>
#include "qt4table-steroids/steroidsmodel.h"

class TeacherModel : public SteroidsModel<QSqlTableModel> {
  Q_OBJECT
public:
  explicit TeacherModel(QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;
public slots:
  void showDismissed(bool show);
  void queryChanged(QString query);
};

#endif // TEACHERMODEL_H
