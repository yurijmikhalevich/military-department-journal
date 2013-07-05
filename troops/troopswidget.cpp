#include "troopswidget.h"
#include "ui_troopswidget.h"

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
