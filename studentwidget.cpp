#include "studentwidget.h"

#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QDebug>

StudentWidget::StudentWidget(QWidget *parent) :
    BaseWidget(parent)
{
}

StudentWidget::~StudentWidget()
{
}

void StudentWidget::enable()
{
    model = new QSqlRelationalTableModel(this, QSqlDatabase::database());
    model->setTable("student");
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setRelation(7, QSqlRelation("university_group", "id", "name"));
//    model->setRelation(10, QSqlRelation("expulsion_reason", "id", "reason"));
//    model->setRelation(11, QSqlRelation("expulsed_from", "id", "unit"));
    model->setRelation(15, QSqlRelation("troop", "id", "name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Lastname"));
    model->setHeaderData(2, Qt::Horizontal, tr("Firstname"));
    model->setHeaderData(3, Qt::Horizontal, tr("Middlename"));
    model->setHeaderData(7, Qt::Horizontal, tr("Group"));
    model->setHeaderData(8, Qt::Horizontal, tr("Decree of enrollment"));
    model->setHeaderData(9, Qt::Horizontal, tr("Decree of expulsion"));
//    model->setHeaderData(10, Qt::Horizontal, tr("Expulsion reason"));
//    model->setHeaderData(11, Qt::Horizontal, tr("Expulsed from"));
//    model->setHeaderData(12, Qt::Horizontal, tr("YGU", "Year of graduation from university"));
//    model->setHeaderData(13, Qt::Horizontal, tr("YGM", "Year of graduation from Faculty of Military Training"));
//    model->setHeaderData(12, Qt::Horizontal, tr("Graduated"));
    model->setHeaderData(12, Qt::Horizontal, tr("Troop"));
    model->select();
//    ui->tableView->setModel(model);
//    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
//    ui->tableView->hideColumn(0);
//    ui->tableView->hideColumn(4);
//    ui->tableView->hideColumn(5);
//    ui->tableView->hideColumn(6);
//    ui->tableView->hideColumn(10);
//    ui->tableView->hideColumn(11);
//    ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
}

void StudentWidget::globalSearchQueryChanged(QString query)
{
    qDebug() << QString("firstname LIKE '%%1%' OR university_group_name_2 LIKE '%%1%'").arg(query);
    model->setFilter(QString("firstname LIKE '%%1%' OR university_group_name_2 LIKE '%%1%'").arg(query));
    model->select();
}
