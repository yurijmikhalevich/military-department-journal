#include "universitygroupwidget.h"

#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "qt4table-steroids/tablehelper.h"
#include "models/universitygroupmodel.h"

UniversityGroupWidget::UniversityGroupWidget(QWidget *parent)
    : BaseWidget(parent) {
  mainLayout = new QVBoxLayout(this);
  model = new UniversityGroupModel(this);
  mainLayout->addWidget(view);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
  SQLUniqueSteroidsValidator *groupNameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", this);
  connect(groupNameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidInputReceived(QString &)));
  LineEditDelegate *groupNameDelegate =
      new LineEditDelegate(groupNameValidator, this);
  SpinBoxDelegate *yearDelegate =
      new SpinBoxDelegate(2000, 9999, QDate::currentDate().year() + 2, this);
  controlsLayout = new QHBoxLayout();
  newGroupName =
      static_cast<QLineEdit *>(groupNameDelegate->createEditor(this));
  connect(newGroupName, SIGNAL(textChanged(QString)),
          this, SLOT(newGroupNameTextChanged(QString)));
  connect(newGroupName, SIGNAL(returnPressed()), this, SLOT(createNewGroup()));
  yearOfGraduation = static_cast<QSpinBox *>(yearDelegate->createEditor(this));
  addNewButton = new QPushButton(tr("Add group"), this);
  connect(addNewButton, SIGNAL(clicked()), this, SLOT(createNewGroup()));
  addNewButton->setDisabled(true);
  facultyEditor =
      static_cast<QComboBox *>(TableHelper::createRelationalEditor(
                                 "university_faculty", "name"));
  troopEditor =
      static_cast<QComboBox *>(TableHelper::createRelationalEditor(
                                 "troop", "name"));
  controlsLayout->addWidget(newGroupName);
  controlsLayout->addWidget(yearOfGraduation);
  controlsLayout->addWidget(facultyEditor);
  controlsLayout->addWidget(troopEditor);
  controlsLayout->addWidget(addNewButton);
  mainLayout->addLayout(controlsLayout);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  sortModel = new UniversityGroupSortModel(this);
  sortModel->setSourceModel(model);
  view->setModel(sortModel);
//    view->setItemDelegateForColumn(1, groupNameDelegate);
  view->setItemDelegateForColumn(2, yearDelegate);
  model->select();
}

void UniversityGroupWidget::invalidInputReceived(QString &input) {
  emit error(QString(tr("Group «%1» already exists")).arg(input));
}

void UniversityGroupWidget::newGroupNameTextChanged(QString text) {
  if (text.isEmpty()) {
    addNewButton->setDisabled(true);
  } else {
    addNewButton->setEnabled(true);
  }
}

void UniversityGroupWidget::createNewGroup() {
  if (newGroupName->text().isEmpty()) {
    return;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO university_group (name,"
                " graduated_from_university_date, faculty_id, troop_id)"
                " VALUES (?, ?, ?, ?)");
  query.addBindValue(newGroupName->text());
  query.addBindValue(QString("%1-01-01").arg(yearOfGraduation->value()));
  query.addBindValue(facultyEditor->itemData(facultyEditor->currentIndex()));
  query.addBindValue(troopEditor->itemData(troopEditor->currentIndex()));
  if (!query.exec()) {
    emit error(QString(tr("There is an error occured while inserting into"
                          " database: «%1»")).arg(
                 query.lastError().text()));
  } else {
    newGroupName->clear();
    model->select();
  }
}
