#include "universityfacultywidget.h"

#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "models/universityfacultymodel.h"

UniversityFacultyWidget::UniversityFacultyWidget(QWidget *parent)
    : BaseWidget(parent) {
  mainLayout = new QVBoxLayout(this);
  model = new UniversityFacultyModel(this);
  mainLayout->addWidget(view);
  SQLUniqueSteroidsValidator *facultyNameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", this);
  connect(facultyNameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidInputReceived(QString &)));
  LineEditDelegate *facultyNameDelegate =
      new LineEditDelegate(facultyNameValidator, this);
  controlsLayout = new QHBoxLayout();
  newFacultyName =
      static_cast<QLineEdit *>(facultyNameDelegate->createEditor(this));
  connect(newFacultyName, SIGNAL(textChanged(QString)),
          this, SLOT(newFacultyNameTextChanged(QString)));
  connect(newFacultyName, SIGNAL(returnPressed()),
          this, SLOT(createNewFaculty()));
  addNewButton = new QPushButton(tr("Add faculty"), this);
  connect(addNewButton, SIGNAL(clicked()), this, SLOT(createNewFaculty()));
  addNewButton->setDisabled(true);
  controlsLayout->addWidget(newFacultyName);
  controlsLayout->addWidget(addNewButton);
  mainLayout->addLayout(controlsLayout);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  view->setModel(model);
  model->select();
}

void UniversityFacultyWidget::invalidInputReceived(QString &input) {
  emit error(QString(tr("Faculty «%1» already exists")).arg(input));
}

void UniversityFacultyWidget::newFacultyNameTextChanged(QString text) {
  if (text.isEmpty()) {
    addNewButton->setDisabled(true);
  } else {
    addNewButton->setEnabled(true);
  }
}

void UniversityFacultyWidget::createNewFaculty() {
  if (newFacultyName->text().isEmpty()) {
    return;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO university_faculty (name) VALUES (?)");
  query.addBindValue(newFacultyName->text());
  if (!query.exec()) {
    emit error(QString(tr("There is an error occured while inserting"
                          " into database: «%1»")).arg(
                 query.lastError().text()));
  } else {
    newFacultyName->clear();
    model->select();
  }
}
