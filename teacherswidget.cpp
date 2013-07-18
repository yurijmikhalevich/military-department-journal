#include "teacherswidget.h"
#include "ui_teacherswidget.h"
#include "teachersmodel.h"
#include "qt4table-steroids/checkboxdelegate.h"

TeachersWidget::TeachersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeachersWidget)
{
    ui->setupUi(this);
    TeachersModel *model = new TeachersModel(ui->tableView);
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setItemDelegateForColumn(2, new CheckBoxDelegate(ui->tableView));
    connect(ui->showDismissed, SIGNAL(toggled(bool)), model, SLOT(showDismissed(bool)));
    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged(QString)));
}

TeachersWidget::~TeachersWidget()
{
    delete ui;
}


void TeachersWidget::addRow()
{
    ui->tableView->model()->insertRow(ui->tableView->model()->rowCount());
}

void TeachersWidget::on_addTeacher_clicked()
{
    QAbstractItemModel *model = ui->tableView->model();
    model->insertRow(model->rowCount());
    model->setData(model->index(model->rowCount() - 1, 1), ui->newTeacherName->text());
    ui->newTeacherName->clear();
    model->submit();
}
