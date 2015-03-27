#include "troopwidget.h"
#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QAbstractItemModel>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/datedelegate.h"
#include "qt4table-steroids/steroidsrelationaldelegate.h"
#include "models/troopmodel.h"

TroopWidget::TroopWidget(QWidget *parent)
    : BaseWidget(parent),
      mainLayout(new QVBoxLayout(this)),
      controlsLayout(new QHBoxLayout()),
      addTroopButton(new QPushButton(tr("Добавить взвод"), this)),
      showGraduatedCheckBox(
        new QCheckBox(tr("Показать выпустившиеся взвода"), this)),
      professionEdit(
        new TableSteroids::RelationalComboBox("military_profession", "name")),
      curatorEdit(new TableSteroids::RelationalComboBox("teacher", "name")) {
  mainLayout->addWidget(showGraduatedCheckBox);
  mainLayout->addWidget(view);
  model = new TroopModel(this);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  connect(showGraduatedCheckBox, SIGNAL(clicked(bool)),
          model, SLOT(showGraduated(bool)));
  TroopSortModel *sortModel = new TroopSortModel(this);
  sortModel->setSourceModel(model);
  view->setModel(sortModel);
  view->setItemDelegateForColumn(4, new SteroidsRelationalDelegate(view));
  view->setItemDelegateForColumn(5, new SteroidsRelationalDelegate(view));
  TroopNameDelegate *nameDelegate = new TroopNameDelegate(view);
  view->setItemDelegateForColumn(1, nameDelegate);
  QDate date = QDate::currentDate();
  date.setDate(date.year() + 2, 9, 17);
  DateDelegate *graduatedInDelegate = new DateDelegate(date, view);
  view->setItemDelegateForColumn(3, graduatedInDelegate);
  date.setDate(date.year() - 2, 5, 1);
  DateDelegate *enteredInDelegate = new DateDelegate(date, view);
  view->setItemDelegateForColumn(2, enteredInDelegate);
  nameEdit = static_cast<TroopNameEditor *>(nameDelegate->createEditor(this));
  controlsLayout->addWidget(nameEdit);
  enteredInEdit =
      static_cast<QDateEdit *>(enteredInDelegate->createEditor(this));
  controlsLayout->addWidget(enteredInEdit);
  controlsLayout->addWidget(curatorEdit);
  controlsLayout->addWidget(professionEdit);
  controlsLayout->addWidget(addTroopButton);
  connect(addTroopButton, SIGNAL(clicked()), this, SLOT(addTroop()));
  mainLayout->addLayout(controlsLayout);
}

void TroopWidget::addTroop() {
  QString name = nameEdit->troopName();
  if (name.isEmpty()) {
    return;
  }
  if (insertRecord({{"name", name}, {"entered_at_military_department_date",
                   enteredInEdit->date()},
  {"curator_id", curatorEdit->currentIndex()},
  {"military_profession_id", professionEdit->currentIndex()}})
      != -1)
  {
    nameEdit->setTroopName("-<N:2>1");
    model->select();
  }
}
