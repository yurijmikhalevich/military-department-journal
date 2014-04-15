#include "militaryprofessionwidget.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/booleancomboboxdelegate.h"
#include "models/militaryprofessionmodel.h"
#include <QSqlQuery>
#include <QSqlError>

MilitaryProfessionWidget::MilitaryProfessionWidget(QWidget *parent)
    : BaseWidget(parent),
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
      new SQLUniqueSteroidsValidator(model->tableName(), "code", this);
  SQLUniqueSteroidsValidator *nameValidator =
      new SQLUniqueSteroidsValidator(model->tableName(), "name", this);
  connect(codeValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidCode(QString &)));
  connect(nameValidator, SIGNAL(invalidInput(QString &)),
          this, SLOT(invalidName(QString &)));
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
  connect(codeEdit, SIGNAL(textChanged(QString)),
          this, SLOT(newInputChanged(QString)));
  connect(nameEdit, SIGNAL(textChanged(QString)),
          this, SLOT(newInputChanged(QString)));
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

void MilitaryProfessionWidget::invalidCode(QString &input) {
  emit error(
        QString("Специальность под номером «%1» уже существует").arg(input));
}

void MilitaryProfessionWidget::invalidName(QString &input) {
  emit error(QString("Специальность с именем «%1» уже существует").arg(input));
}

void MilitaryProfessionWidget::newInputChanged(QString) {
  QString code = codeEdit->text().simplified();
  QString name = codeEdit->text().simplified();
  if (!code.isEmpty() && !name.isEmpty()) {
    addNewButton->setEnabled(true);
  } else {
    addNewButton->setDisabled(true);
  }
}

void MilitaryProfessionWidget::addNewProfession() {
  QString code = codeEdit->text().simplified();
  QString name = codeEdit->text().simplified();
  if (code.isEmpty() || name.isEmpty()) {
    return;
  }
  if (insertRecord({{"code", code}, {"name", name}}) != -1) {
    codeEdit->clear();
    nameEdit->clear();
    codeEdit->setFocus();
    model->select();
  }
}
