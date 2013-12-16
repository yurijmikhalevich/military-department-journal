#include "subjectdurationwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRelationalDelegate>
#include "qt4table-steroids/tablehelper.h"
#include "models/subjectdurationmodel.h"

SubjectDurationWidget::SubjectDurationWidget(QWidget *parent)
    : BaseWidget(parent) {
  model = new SubjectDurationModel(this);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  view->setModel(model);
  view->showColumn(0); // showing default hided 0 column
  mainLayout->addWidget(view);
  QHBoxLayout *controlsLayout = new QHBoxLayout();
  subjectEdit = TableHelper::createRelationalEditor("subject", "name");
  professionEdit = TableHelper::createRelationalEditor("military_profession",
                                                       "name");
  durationEdit = new QSpinBox(this);
  addSubjectDurationButton = new QPushButton(tr("Add subject"), this);
  controlsLayout->addWidget(subjectEdit);
  controlsLayout->addWidget(professionEdit);
  controlsLayout->addWidget(durationEdit);
  controlsLayout->addWidget(addSubjectDurationButton);
  connect(addSubjectDurationButton, SIGNAL(clicked()),
          this, SLOT(addSubjectDuration()));
  mainLayout->addLayout(controlsLayout);
}

void SubjectDurationWidget::addSubjectDuration() {
  QSqlQuery query;
  query.prepare("INSERT INTO subject_duration (subject_id,"
                " military_profession_id, duration)"
                " VALUES (?, ?, ?)");
  query.addBindValue(subjectEdit->itemData(subjectEdit->currentIndex()));
  query.addBindValue(professionEdit->itemData(professionEdit->currentIndex()));
  query.addBindValue(durationEdit->value());
  if (!query.exec()) {
    throw query.lastError(); // TODO: replace with signal emitting
  } else {
    model->select();
  }
}
