#include "troopwidget.h"
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QAbstractItemModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/tablehelper.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "models/troopmodel.h"

TroopWidget::TroopWidget(QWidget *parent)
    : BaseWidget(parent) {
  mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(view);
  model = new TroopModel(view);
  view->setModel(model);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
  SQLUniqueSteroidsValidator *nameValidator =
      new SQLUniqueSteroidsValidator("troop", "name");
  LineEditDelegate *nameDelegate = new LineEditDelegate(nameValidator, view);
  view->setItemDelegateForColumn(1, nameDelegate);
  int year = QDate::currentDate().year();
  SpinBoxDelegate *graduatedInDelegate =
      new SpinBoxDelegate(1900, year + 12, year + 2, view);
  view->setItemDelegateForColumn(3, graduatedInDelegate);
  controlsLayout = new QHBoxLayout();
  nameEdit = static_cast<QLineEdit *>(nameDelegate->createEditor(this));
  controlsLayout->addWidget(nameEdit);
  graduatedInEdit =
      static_cast<QSpinBox *>(graduatedInDelegate->createEditor(this));
  controlsLayout->addWidget(graduatedInEdit);
  curatorEdit =
      static_cast<QComboBox *>(TableHelper::createRelationalEditor(
                                 "teacher", "name"));
  controlsLayout->addWidget(curatorEdit);
  professionEdit =
      static_cast<QComboBox *>(TableHelper::createRelationalEditor(
                                 "military_profession", "name"));
  controlsLayout->addWidget(professionEdit);
  addTroopButton = new QPushButton(tr("Add troop"), this);
  controlsLayout->addWidget(addTroopButton);
  connect(addTroopButton, SIGNAL(clicked()), this, SLOT(addTroop()));
  mainLayout->addLayout(controlsLayout);
}

void TroopWidget::addTroop() {
  if (nameEdit->text().isEmpty()) {
    return;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO troop (name,"
                " graduated_from_military_department_date, curator_id,"
                " military_profession_id)"
                " VALUES (?, ?, ?, ?)");
  query.addBindValue(nameEdit->text());
  query.addBindValue(QString("%1-01-01").arg(graduatedInEdit->value()));
  query.addBindValue(curatorEdit->itemData(curatorEdit->currentIndex()));
  query.addBindValue(professionEdit->itemData(professionEdit->currentIndex()));
  if (!query.exec()) {
    throw query.lastError(); // TODO: replace with signal emitting
  }
  nameEdit->clear();
  model->select();
}
