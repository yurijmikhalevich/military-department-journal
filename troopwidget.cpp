#include "troopwidget.h"

#include "troopmodel.h"

#include <QSqlRelationalDelegate>

TroopWidget::TroopWidget(QWidget *parent) :
    QWidget(parent)
{
}

TroopWidget::~TroopWidget()
{
}

void TroopWidget::enable()
{
//    delete ui->tableView->model();
//    ui->tableView->setModel(new SqlRelationalTroopModel(ui->tableView));
//    ui->tableView->hideColumn(0);
//    ui->tableView->hideColumn(2);
//    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}
