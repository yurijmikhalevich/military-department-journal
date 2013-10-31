#include "evaluationwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include "qt4table-steroids/tablehelper.h"
#include "evaluationmodel.h"

EvaluationWidget::EvaluationWidget(QWidget *parent) :
    BaseWidget(parent)
{
    model = new EvaluationModel(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    view->setModel(model);
    mainLayout->addWidget(view);
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    subjectEdit = TableHelper::createRelationalEditor("subject", "name");
    controlTypeEdit = TableHelper::createRelationalEditor("control_type", "name");
    teacherEdit = TableHelper::createRelationalEditor("teacher", "name");
    troopEdit = TableHelper::createRelationalEditor("troop", "name");
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    addEvaluationButton = new QPushButton(tr("Add evaluation"), this);
//    addSubjectButton = new QPushButton(tr("Add subject"), this);
//    controlsLayout->addWidget(subjectNameEdit);
//    controlsLayout->addWidget(addSubjectButton);
//    connect(addSubjectButton, SIGNAL(clicked()), this, SLOT(addEvaluation()));
//    mainLayout->addLayout(controlsLayout);
}

void EvaluationWidget::addEvaluation()
{
//    QSqlQuery query;
//    query.prepare("INSERT INTO subject (name) VALUES (?)");
//    query.addBindValue(subjectNameEdit->text());
//    subjectNameEdit->clear();
//    if (!query.exec()) {
//        throw query.lastError(); // TODO: replace with signal emitting
//    } else {
//        model->select();
//    }
}

void EvaluationWidget::generateEvaluationList()
{

}
