#include "markwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QDir>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include "qt4table-steroids/tablehelper.h"
#include "models/markmodel.h"

MarkWidget::MarkWidget(QWidget *parent)
    : BaseWidget(parent) {
  model = new MarkModel(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  view->setModel(model);
  view->showColumn(0);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
  mainLayout->addWidget(view);
  QHBoxLayout *controlsLayout = new QHBoxLayout();
  evaluationEdit = TableHelper::createRelationalEditor("evaluation", "date");
  studentEdit = TableHelper::createRelationalEditor("student", "lastname");
  valueEdit = new QSpinBox(this);
  teacherEdit = TableHelper::createRelationalEditor("teacher", "name");
  dateEdit = new QDateEdit(QDate::currentDate(), this);
  addMarkButton = new QPushButton(tr("Add mark"), this);
  controlsLayout->addWidget(evaluationEdit);
  controlsLayout->addWidget(studentEdit);
  controlsLayout->addWidget(valueEdit);
  controlsLayout->addWidget(teacherEdit);
  controlsLayout->addWidget(dateEdit);
  controlsLayout->addWidget(addMarkButton);
  connect(addMarkButton, SIGNAL(clicked()), this, SLOT(addMark()));
  mainLayout->addLayout(controlsLayout);
  model->select();
}

void MarkWidget::addMark() {
  QSqlQuery query;
  query.prepare("INSERT INTO mark (evaluation_id, student_id, value,"
                " teacher_id, date) VALUES (?, ?, ?, ?, ?)");
  query.addBindValue(evaluationEdit->itemData(evaluationEdit->currentIndex()));
  query.addBindValue(studentEdit->itemData(studentEdit->currentIndex()));
  query.addBindValue(valueEdit->value());
  query.addBindValue(teacherEdit->itemData(teacherEdit->currentIndex()));
  query.addBindValue(dateEdit->date().toString("yyyy-MM-dd"));
  if (!query.exec()) {
    throw query.lastError(); // TODO: replace with signal emitting
  } else {
    model->select();
  }
}
