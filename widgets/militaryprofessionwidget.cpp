#include "militaryprofessionwidget.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/booleancomboboxdelegate.h"
#include "models/militaryprofessionmodel.h"

MilitaryProfessionWidget::MilitaryProfessionWidget(QWidget *parent)
    : BaseWidget(parent),
      isNameInvalid(true),
      isCodeInvalid(true),
      controlsLayout(new QHBoxLayout()),
      mainLayout(new QVBoxLayout(this)),
      showArchivedCheckBox(
        new QCheckBox(tr("Показать отправленные в архив"), this)) {
  model = new MilitaryProfessionModel(this);
  view->setModel(model);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  connect(showArchivedCheckBox, SIGNAL(clicked(bool)),
          model, SLOT(showArchived(bool)));
  SQLUniqueSteroidsValidator *codeValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "code", true, this);
  SQLUniqueSteroidsValidator *nameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", true, this);
  LineEditDelegate *codeDelegate = new LineEditDelegate(codeValidator, this);
  LineEditDelegate *nameDelegate = new LineEditDelegate(nameValidator, this);
  view->setItemDelegateForColumn(
        1, new BooleanComboBoxDelegate(
          tr("В архиве"), tr("Действителен"), view));
  view->setItemDelegateForColumn(2, codeDelegate);
  view->setItemDelegateForColumn(3, nameDelegate);
  codeEdit = static_cast<QLineEdit *>(codeDelegate->createEditor(this));
  nameEdit = static_cast<QLineEdit *>(nameDelegate->createEditor(this));
  codeEdit->setPlaceholderText(tr("Номер новой специальности"));
  nameEdit->setPlaceholderText(tr("Название новой специальности"));
  addNewButton = new QPushButton(tr("Добавить специальность"), this);
  addNewButton->setDisabled(true);
  connect(codeEdit, SIGNAL(returnPressed()), nameEdit, SLOT(setFocus()));
  connect(nameEdit, SIGNAL(returnPressed()), this, SLOT(addNewProfession()));
  connect(addNewButton, SIGNAL(clicked()), this, SLOT(addNewProfession()));
  connect(codeValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidCode(QString &)));
  connect(nameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidName(QString &)));
  connect(codeValidator, SIGNAL(validInput(QString &)),
          this, SLOT(validCode(QString &)));
  connect(nameValidator, SIGNAL(validInput(QString &)),
          this, SLOT(validName(QString &)));
  controlsLayout->addWidget(codeEdit);
  controlsLayout->addWidget(nameEdit);
  controlsLayout->addWidget(addNewButton);
  mainLayout->addWidget(showArchivedCheckBox);
  mainLayout->addWidget(view);
  mainLayout->addLayout(controlsLayout);
  view->setColumnWidth(1, 110);
  view->setColumnWidth(2, 70);
  view->setColumnWidth(3, 270);
}

void MilitaryProfessionWidget::invalidCode(QString &) {
  emit error(tr("Введён неверный или уже существующий номер специальности"));
  if (codeEdit->hasFocus()) {
    isCodeInvalid = true;
    checkButtonState();
  }
}

void MilitaryProfessionWidget::invalidName(QString &) {
  emit error(tr("Введено неверное или уже существующее название"
                " специальности"));
  if (nameEdit->hasFocus()) {
    isNameInvalid = true;
    checkButtonState();
  }
}

void MilitaryProfessionWidget::validCode(QString &) {
  if (codeEdit->hasFocus()) {
    isCodeInvalid = false;
    checkButtonState();
  }
}

void MilitaryProfessionWidget::validName(QString &) {
  if (nameEdit->hasFocus()) {
    isNameInvalid = false;
    checkButtonState();
  }
}

void MilitaryProfessionWidget::checkButtonState() {
  addNewButton->setDisabled(isCodeInvalid || isNameInvalid);
}

void MilitaryProfessionWidget::addNewProfession() {
  QString code = codeEdit->text().simplified();
  QString name = nameEdit->text().simplified();
  int newProfessionId = insertRecord({{"code", code}, {"name", name}});
  if (newProfessionId != -1) {
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT id FROM subject");
    if (!execQuery(selectQuery)) {
      return;
    }
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO subject_duration (subject_id,"
                        " military_profession_id, duration) VALUES (?, ?, 0)");
    while (selectQuery.next()) {
      insertQuery.addBindValue(selectQuery.record().value("id"));
      insertQuery.addBindValue(newProfessionId);
      if (!execQuery(insertQuery)) {
        return;
      }
    }
    codeEdit->clear();
    nameEdit->clear();
    codeEdit->setFocus();
    model->select();
  }
}
