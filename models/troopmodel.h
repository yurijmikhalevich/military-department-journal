#ifndef TROOPMODEL_H
#define TROOPMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

/**
 * @brief The TroopModel class
 */
class TroopModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit TroopModel(QObject *parent = 0);
  QVariant data(const QModelIndex &item, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  int columnCount(const QModelIndex &) const;
public slots:
  void queryChanged(QString query);
};

#endif // TROOPMODEL_H
