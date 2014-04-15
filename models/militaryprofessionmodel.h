#ifndef MILITARYPROFESSIONMODEL_H
#define MILITARYPROFESSIONMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlTableModel>

class MilitaryProfessionModel : public SteroidsModel<QSqlTableModel> {
  Q_OBJECT
public:
  explicit MilitaryProfessionModel(QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;
public slots:
  void showArchived(bool show);
  void queryChanged(QString query);
};

#endif // MILITARYPROFESSIONMODEL_H
