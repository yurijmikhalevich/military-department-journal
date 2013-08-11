#include "teacherwidget.h"
#include "teachermodel.h"
#include "qt4table-steroids/checkboxdelegate.h"

TeacherWidget::TeacherWidget(QWidget *parent) :
    BaseWidget(parent)
{
//    ui->setupUi(this);
//    TeacherModel *model = new TeacherModel(ui->tableView);
//    ui->tableView->setModel(model);
//    ui->tableView->hideColumn(0);
//    ui->tableView->setColumnWidth(1, 400);
//    ui->tableView->setItemDelegateForColumn(2, new CheckBoxDelegate(ui->tableView));
//    connect(ui->showDismissed, SIGNAL(toggled(bool)), model, SLOT(showDismissed(bool)));
//    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged(QString)));
}

TeacherWidget::~TeacherWidget()
{
//    delete ui;
}


void TeacherWidget::addRow()
{
//    ui->tableView->model()->insertRow(ui->tableView->model()->rowCount());
}

void TeacherWidget::on_addTeacher_clicked()
{
//    QAbstractItemModel *model = ui->tableView->model();
//    model->insertRow(model->rowCount());
//    model->setData(model->index(model->rowCount() - 1, 1), ui->newTeacherName->text());
//    ui->newTeacherName->clear();
//    model->submit();
}
