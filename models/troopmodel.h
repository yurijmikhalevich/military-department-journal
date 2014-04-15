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
  void showGraduated(bool show);
  void queryChanged(QString query);
private:
  QString prepareName(QString troopName, QDate dateEntered,
                      QDate dateGraduated);
  void fillTroops();
  QSqlDatabase troops;
private slots:
  void addRecord(int id, QVariantMap record);
  void onDataChanged(const QModelIndex &topLeft,
                     const QModelIndex &bottomRight);
};

#include <QSortFilterProxyModel>

class TroopSortModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  explicit TroopSortModel(QObject *parent = 0)
      : QSortFilterProxyModel(parent) {}
  bool lessThan(const QModelIndex &left, const QModelIndex &right) const {
    if (left.column() == 6) {
      return left.data().toInt() < right.data().toInt();
    }
    return QSortFilterProxyModel::lessThan(left, right);
  }
};

#endif // TROOPMODEL_H
