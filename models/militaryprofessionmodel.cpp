#include "militaryprofessionmodel.h"

#include <QDebug>

MilitaryProfessionModel::MilitaryProfessionModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  setTable("military_profession");
  setHeaderData(1, Qt::Horizontal, tr("Archived"));
  setHeaderData(2, Qt::Horizontal, tr("Code"));
  setHeaderData(3, Qt::Horizontal, tr("Name"));
  select();
}

void MilitaryProfessionModel::queryChanged(QString query) {
  qDebug() << "MilitaryProfessionModel" <<
              "queryChanged should be implemented" <<
              query;
}
