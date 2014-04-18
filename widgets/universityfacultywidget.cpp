#include "universityfacultywidget.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/booleancomboboxdelegate.h"
#include "models/universityfacultymodel.h"
#include <QDate>

UniversityFacultyWidget::UniversityFacultyWidget(QWidget *parent)
    : BaseWidget(parent),
      mainLayout(new QVBoxLayout(this)),
      controlsLayout(new QHBoxLayout()),
      addNewButton(new QPushButton(tr("Добавить факультет"), this)),
      showArchivedCheckBox(
        new QCheckBox(tr("Показать отправленные в архив"), this)) {
  model = new UniversityFacultyModel(this);
  connect(showArchivedCheckBox, SIGNAL(clicked(bool)),
          model, SLOT(showArchived(bool)));
  mainLayout->addWidget(showArchivedCheckBox);
  mainLayout->addWidget(view);
  SQLUniqueSteroidsValidator *facultyNameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", true, this);
  connect(facultyNameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidInputReceived(QString &)));
  LineEditDelegate *facultyNameDelegate =
      new LineEditDelegate(facultyNameValidator, this);
  newFacultyName =
      static_cast<QLineEdit *>(facultyNameDelegate->createEditor(this));
  newFacultyName->setPlaceholderText(tr("Название нового факультета"));
  view->setItemDelegateForColumn(
        1, new BooleanComboBoxDelegate(
          tr("В архиве"), tr("Действителен"), view));
  view->setItemDelegateForColumn(2, facultyNameDelegate);
  connect(newFacultyName, SIGNAL(textChanged(QString)),
          this, SLOT(newFacultyNameTextChanged(QString)));
  connect(newFacultyName, SIGNAL(returnPressed()),
          this, SLOT(createNewFaculty()));
  connect(addNewButton, SIGNAL(clicked()), this, SLOT(createNewFaculty()));
  addNewButton->setDisabled(true);
  controlsLayout->addWidget(newFacultyName);
  controlsLayout->addWidget(addNewButton);
  mainLayout->addLayout(controlsLayout);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  view->setModel(model);
  model->select();
  view->setColumnWidth(1, 110);
  view->setColumnWidth(2, 230);
}

void UniversityFacultyWidget::invalidInputReceived(QString &input) {
  emit error(QString(tr("Факультет «%1» уже существует")).arg(input));
}

void UniversityFacultyWidget::newFacultyNameTextChanged(QString text) {
  if (text.isEmpty()) {
    addNewButton->setDisabled(true);
  } else {
    addNewButton->setEnabled(true);
  }
}

void UniversityFacultyWidget::createNewFaculty() {
  QString name = newFacultyName->text().simplified();
  if (name.isEmpty()) {
    emit error(tr("Навзание факультета не должно быть пустым"));
    return;
  }
  if (insertRecord({{"name", name}}) != -1) {
    newFacultyName->clear();
    model->select();
  }
}
