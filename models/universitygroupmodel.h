#ifndef UNIVERSITYGROUPMODEL_H
#define UNIVERSITYGROUPMODEL_H

#include "qt4table-steroids/steroidsmodel.h"
#include <QSqlRelationalTableModel>

class UniversityGroupModel : public SteroidsModel<QSqlRelationalTableModel> {
  Q_OBJECT
public:
  explicit UniversityGroupModel(QObject *parent = 0);
  QVariant data(const QModelIndex &item, int role) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  int columnCount(const QModelIndex &) const;
public slots:
  void showGraduated(bool show);
  void queryChanged(QString query);
};

#include <QSortFilterProxyModel>

class UniversityGroupSortModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  explicit UniversityGroupSortModel(QObject *parent = 0)
      : QSortFilterProxyModel(parent) {}
  bool lessThan(const QModelIndex &left, const QModelIndex &right) const {
    if (left.column() == 5) {
      return left.data().toInt() < right.data().toInt();
    }
    return QSortFilterProxyModel::lessThan(left, right);
  }
};

#endif // UNIVERSITYGROUPMODEL_H
