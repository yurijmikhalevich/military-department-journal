#include "troopwidget.h"

#include <QSqlRelationalDelegate>
#include <QDebug>
#include <QAbstractItemModel>
#include "qt4table-steroids/steroidsrelationaldelegate.h"
#include "qt4table-steroids/tablehelper.h"

TroopWidget::TroopWidget(QWidget *parent) :
    BaseWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    view = new SteroidsView(this);
    mainLayout->addWidget(view);
    model = new TroopModel(view);
    view->setModel(model);
    SteroidsRelationalDelegate *delegate = new SteroidsRelationalDelegate(false, view);
    view->setItemDelegateForColumn(5, delegate);
    // TODO: troops adding
    biribiri = static_cast<QComboBox *>(TableHelper::createRelationalEditor("teacher", "name"));
    mainLayout->addWidget(biribiri);
    connect(biribiri, SIGNAL(currentIndexChanged(int)), this, SLOT(cin(int)));
//    view->setItemDelegate(new QSqlRelationalDelegate(view));
//    QSqlRelationalDelegate *delegate = new QSqlRelationalDelegate(view);
//    QWidget *ce = delegate->createEditor(view->indexWidget(model->index(0, 5)), QStyleOptionViewItem(), QModelIndex());
//    QWidget *ce = view->itemDelegateForColumn(5)->createEditor(view->indexWidget(model->index(0, 5)), QStyleOptionViewItem(), QModelIndex());
//    QComboBox *curatorEditor = static_cast<QComboBox *>(view->itemDelegateForColumn(5)->createEditor(
//                                                            view, QStyleOptionViewItem(), QModelIndex()));
            //    mainLayout->addWidget(ce);
}

void TroopWidget::cin(int n)
{
    qDebug() << n;
}
