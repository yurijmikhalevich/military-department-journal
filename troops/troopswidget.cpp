#include "troopswidget.h"
#include "ui_troopswidget.h"

#include "sqlrelationaltroopmodel.h"

#include <QSqlRelationalDelegate>

TroopsWidget::TroopsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TroopsWidget)
{
    ui->setupUi(this);
}

TroopsWidget::~TroopsWidget()
{
    delete ui;
}

void TroopsWidget::enable()
{
    delete ui->tableView->model();
    ui->tableView->setModel(new SqlRelationalTroopModel(ui->tableView));
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(2);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
}
