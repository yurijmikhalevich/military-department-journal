#include "teacherswidget.h"
#include "ui_teacherswidget.h"

TeachersWidget::TeachersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeachersWidget)
{
    ui->setupUi(this);
}

TeachersWidget::~TeachersWidget()
{
    delete ui;
}
