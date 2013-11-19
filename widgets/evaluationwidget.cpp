#include "evaluationwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QDir>
#include <QSqlRecord>
#include "qt4table-steroids/tablehelper.h"
#include "models/evaluationmodel.h"
#include "documentgenerator.h"

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
    universityGroupEdit = TableHelper::createRelationalEditor("university_group", "name");
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    addEvaluationButton = new QPushButton(tr("Add evaluation"), this);
    generateEvaluationListButton = new QPushButton(tr("Generate list"), this);
    controlsLayout->addWidget(subjectEdit);
    controlsLayout->addWidget(controlTypeEdit);
    controlsLayout->addWidget(teacherEdit);
    controlsLayout->addWidget(universityGroupEdit);
    controlsLayout->addWidget(dateEdit);
    controlsLayout->addWidget(addEvaluationButton);
    controlsLayout->addWidget(generateEvaluationListButton);
    connect(addEvaluationButton, SIGNAL(clicked()), this, SLOT(addEvaluation()));
    connect(generateEvaluationListButton, SIGNAL(clicked()), this, SLOT(generateEvaluationList()));
    mainLayout->addLayout(controlsLayout);
}

void EvaluationWidget::addEvaluation()
{
//    QSqlQuery query;
//    query->prepare("INSERT INTO subject (name) VALUES (?)");
//    query->addBindValue(subjectNameEdit->text());
//    subjectNameEdit->clear();
//    if (!query->exec()) {
//        throw query->lastError(); // TODO: replace with signal emitting
//    } else {
//        model->select();
//    }
}

void EvaluationWidget::generateEvaluationList()
{
    QSqlQuery *query = new QSqlQuery();
    query->prepare("SELECT f.name FROM faculty AS f, university_group AS u WHERE u.faculty_id = f.id AND u.id = ?");
    query->addBindValue(universityGroupEdit->itemData(universityGroupEdit->currentIndex()));
    if (!query->exec() || !query->next()) {
        emit error(query->lastError().text());
        return;
    }
    QString faculty = query->record().value("name").toString();
    query->prepare("SELECT name FROM student WHERE university_group_id = ?");
    QVariant universityGroupId = universityGroupEdit->itemData(
                universityGroupEdit->currentIndex());
    query->addBindValue(universityGroupId);
    if (!query->exec()) {
        emit error(query->lastError().text());
        return;
    }
    QStringList students;
    while (query->next()) {
        students.append(query->record().value("name").toString());
    }
    DocumentGenerator::generateExamList(QApplication::applicationFilePath() + QDir::separator() + "vedomost.docx",
                                        QApplication::applicationFilePath() + QDir::separator() + "vedomost_"
                                        + universityGroupEdit->currentText() + "_" + subjectEdit->currentText()
                                        + ".docx", "I", "2013/2014", faculty, universityGroupEdit->currentText(), "4",
                                        "261000", subjectEdit->currentText(), teacherEdit->currentText(),
                                        dateEdit->date(), students);
}
