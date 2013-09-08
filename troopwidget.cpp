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

TroopWidget::TroopWidget(QWidget *parent) :
    BaseWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    view = new SteroidsView(this);
    mainLayout->addWidget(view);
    model = new TroopModel(view);
    view->setModel(model);
    view->setItemDelegate(new QSqlRelationalDelegate(view));
    SQLUniqueSteroidsValidator *nameValidator = new SQLUniqueSteroidsValidator("troop", "name");
    LineEditDelegate *nameDelegate = new LineEditDelegate(nameValidator, view);
    view->setItemDelegateForColumn(1, nameDelegate);
    int year = QDate::currentDate().year();
    SpinBoxDelegate *ygmDelegate = new SpinBoxDelegate(1900, year + 12, year + 2, view);
    view->setItemDelegateForColumn(3, ygmDelegate);
    controlsLayout = new QHBoxLayout();
    nameEdit = static_cast<QLineEdit *>(nameDelegate->createEditor(this));
    controlsLayout->addWidget(nameEdit);
    ygmEdit = static_cast<QSpinBox *>(ygmDelegate->createEditor(this));
    controlsLayout->addWidget(ygmEdit);
    curatorEdit = static_cast<QComboBox *>(TableHelper::createRelationalEditor("teacher", "name"));
    controlsLayout->addWidget(curatorEdit);
    addTroopButton = new QPushButton(tr("Add troop"), this);
    controlsLayout->addWidget(addTroopButton);
    connect(addTroopButton, SIGNAL(clicked()), this, SLOT(addTroop()));
    mainLayout->addLayout(controlsLayout);
}

void TroopWidget::addTroop()
{
    if (nameEdit->text().isEmpty()) {
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO troop (name, graduated_from_in, curator_id) VALUES (?, ?, ?)");
    query.addBindValue(nameEdit->text());
    query.addBindValue(ygmEdit->value());
    query.addBindValue(curatorEdit->itemData(curatorEdit->currentIndex()));
    if (!query.exec()) {
        throw query.lastError(); // TODO: replace with signal emitting
    }
    nameEdit->clear();
    model->select();
}
