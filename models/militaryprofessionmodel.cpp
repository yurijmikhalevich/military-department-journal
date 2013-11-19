#include "militaryprofessionmodel.h"

MilitaryProfessionModel::MilitaryProfessionModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("military_profession");
    setHeaderData(1, Qt::Horizontal, tr("State"));
    setHeaderData(2, Qt::Horizontal, tr("Code"));
    setHeaderData(3, Qt::Horizontal, tr("Name"));
    select();
}

void MilitaryProfessionModel::queryChanged(QString query)
{

}
