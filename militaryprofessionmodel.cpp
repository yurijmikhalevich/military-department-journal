#include "militaryprofessionmodel.h"

MilitaryProfessionModel::MilitaryProfessionModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("military_profession");
    setHeaderData(1, Qt::Horizontal, tr("State"));
    setHeaderData(2, Qt::Horizontal, tr("Code"));
    setHeaderData(3, Qt::Horizontal, tr("Name"));
}

//QVariant MilitaryProfessionModel::data(const QModelIndex &item, int role) const
//{

//}

//Qt::ItemFlags MilitaryProfessionModel::flags(const QModelIndex &index) const
//{

//}

//int MilitaryProfessionModel::columnCount(const QModelIndex &) const
//{

//}

void MilitaryProfessionModel::queryChanged(QString query)
{

}
