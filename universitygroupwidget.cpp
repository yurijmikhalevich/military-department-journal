#include "universitygroupwidget.h"

#include <QDate>

#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/spinboxdelegate.h"

UniversityGroupWidget::UniversityGroupWidget(QWidget *parent) :
    QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    view = new SteroidsView(this);
    mainLayout->addWidget(view);
    controlsLayout = new QHBoxLayout();
    newGroupName = new QLineEdit(this);
    yearOfGraduation = new QSpinBox(this);
    addNewButton = new QPushButton(this);
    controlsLayout->addWidget(newGroupName);
    controlsLayout->addWidget(yearOfGraduation);
    controlsLayout->addWidget(addNewButton);
    mainLayout->addLayout(controlsLayout);
    UniversityGroupModel *model = new UniversityGroupModel(this);
    TestSort *ts = new TestSort(this);
    ts->setSourceModel(model);
    view->setModel(ts);
    view->setItemDelegateForColumn(1, new LineEditDelegate(new TestValidator(this), this));
    view->setItemDelegateForColumn(2, new SpinBoxDelegate(2000, 9999, QDate::currentDate().year(), this));
    model->select();
}
