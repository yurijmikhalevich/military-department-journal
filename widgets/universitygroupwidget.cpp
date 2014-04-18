#include "universitygroupwidget.h"

#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "qt4table-steroids/steroidsrelationaldelegate.h"
#include "models/universitygroupmodel.h"
#include "trooprelationaldelegate.h"

UniversityGroupWidget::UniversityGroupWidget(QWidget *parent)
    : BaseWidget(parent),
      controlsLayout(new QVBoxLayout()),
      mainLayout(new QVBoxLayout(this)),
      addNewButton(new QPushButton(tr("Добавить группу"), this)),
      showGraduatedCheckBox(
        new QCheckBox(tr("Показать выпустившиеся"), this)) {
  model = new UniversityGroupModel(this);
  connect(showGraduatedCheckBox, SIGNAL(clicked(bool)),
          model, SLOT(showGraduated(bool)));
  mainLayout->addWidget(showGraduatedCheckBox);
  mainLayout->addWidget(view);
  view->setItemDelegateForColumn(3, new SteroidsRelationalDelegate(view));
  SQLUniqueSteroidsValidator *groupNameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", true, this);
  connect(groupNameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidInputReceived(QString &)));
  LineEditDelegate *groupNameDelegate =
      new LineEditDelegate(groupNameValidator, this);
  view->setItemDelegateForColumn(1, groupNameDelegate);
  SpinBoxDelegate *yearDelegate =
      new SpinBoxDelegate(2000, 9999, QDate::currentDate().year() + 2, this);
  newGroupName =
      static_cast<QLineEdit *>(groupNameDelegate->createEditor(this));
  connect(newGroupName, SIGNAL(textChanged(QString)),
          this, SLOT(newGroupNameTextChanged(QString)));
  connect(newGroupName, SIGNAL(returnPressed()), this, SLOT(createNewGroup()));
  yearOfGraduation = static_cast<QSpinBox *>(yearDelegate->createEditor(this));
  connect(addNewButton, SIGNAL(clicked()), this, SLOT(createNewGroup()));
  addNewButton->setDisabled(true);
  facultyEditor = new TableSteroids::RelationalComboBox(
        "university_faculty", "name");
  TroopRelationalDelegate *troopDelegate = new TroopRelationalDelegate(this);
  view->setItemDelegateForColumn(4, troopDelegate);
  troopEditor =
      static_cast<TableSteroids::RelationalComboBox *>(
        troopDelegate->createEditor(this));
  QHBoxLayout *layoutOne = new QHBoxLayout();
  layoutOne->addWidget(newGroupName);
  layoutOne->addWidget(yearOfGraduation);
  QHBoxLayout *layoutTwo = new QHBoxLayout();
  layoutTwo->addWidget(facultyEditor);
  layoutTwo->addWidget(troopEditor);
  layoutTwo->addWidget(addNewButton);
  controlsLayout->addLayout(layoutOne);
  controlsLayout->addLayout(layoutTwo);
  mainLayout->addLayout(controlsLayout);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  sortModel = new UniversityGroupSortModel(this);
  sortModel->setSourceModel(model);
  view->setModel(sortModel);
  view->setItemDelegateForColumn(2, yearDelegate);
  model->select();
  view->setColumnWidth(1, 120);
  view->setColumnWidth(2, 60);
  view->setColumnWidth(3, 230);
  view->setColumnWidth(4, 100);
  view->setColumnWidth(5, 60);
}

void UniversityGroupWidget::invalidInputReceived(QString &input) {
  emit error(QString(tr("Группа «%1» уже существует")).arg(input));
}

void UniversityGroupWidget::newGroupNameTextChanged(QString text) {
  if (text.isEmpty()) {
    addNewButton->setDisabled(true);
  } else {
    addNewButton->setEnabled(true);
  }
}

void UniversityGroupWidget::createNewGroup() {
  QString name = newGroupName->text().simplified();
  if (name.isEmpty()) {
    return;
  }
  if (insertRecord({
      {"name", name},
      {"graduated_from_university_year", yearOfGraduation->value()},
      {"faculty_id", facultyEditor->currentId()},
      {"troop_id", troopEditor->currentId()}}) != -1) {
    newGroupName->clear();
  }
}
