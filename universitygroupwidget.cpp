#include "universitygroupwidget.h"

#include <QDate>
#include <QSqlError>

#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/spinboxdelegate.h"

UniversityGroupWidget::UniversityGroupWidget(QWidget *parent) :
    BaseWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    view = new SteroidsView(this);
    mainLayout->addWidget(view);
    UniversityGroupNameValidator *groupNameValidator = new UniversityGroupNameValidator(this);
    connect(groupNameValidator, SIGNAL(invalidInput(QString&)), this, SLOT(invalidInputReceived(QString&)));
    LineEditDelegate *groupNameDelegate = new LineEditDelegate(groupNameValidator, this);
    SpinBoxDelegate *yearDelegate = new SpinBoxDelegate(2000, 9999, QDate::currentDate().year() + 2, this);
    controlsLayout = new QHBoxLayout();
    newGroupName = static_cast<QLineEdit *>(groupNameDelegate->createEditor(this));
    connect(newGroupName, SIGNAL(textChanged(QString)), this, SLOT(newGroupNameTextChanged(QString)));
    connect(newGroupName, SIGNAL(returnPressed()), this, SLOT(createNewGroup()));
    yearOfGraduation = static_cast<QSpinBox *>(yearDelegate->createEditor(this));
    addNewButton = new QPushButton(tr("Add group"), this);
    connect(addNewButton, SIGNAL(clicked()), this, SLOT(createNewGroup()));
    addNewButton->setDisabled(true);
    controlsLayout->addWidget(newGroupName);
    controlsLayout->addWidget(yearOfGraduation);
    controlsLayout->addWidget(addNewButton);
    mainLayout->addLayout(controlsLayout);
    model = new UniversityGroupModel(this);
    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged(QString)));
    sortModel = new UniversityGroupSortModel(this);
    sortModel->setSourceModel(model);
    view->setModel(sortModel);
    view->setItemDelegateForColumn(1, groupNameDelegate);
    view->setItemDelegateForColumn(2, yearDelegate);
    model->select();
}

void UniversityGroupWidget::invalidInputReceived(QString &input)
{
    emit error(QString(tr("Group «%1» already exists")).arg(input));
}

void UniversityGroupWidget::newGroupNameTextChanged(QString text)
{
    if (text.isEmpty()) {
        addNewButton->setDisabled(true);
    } else {
        addNewButton->setEnabled(true);
    }
}

void UniversityGroupWidget::createNewGroup()
{
    QSqlQuery query;
    query.prepare("INSERT INTO university_group (name, graduated_from_university_in) VALUES (?, ?)");
    query.addBindValue(newGroupName->text());
    query.addBindValue(yearOfGraduation->value());
    if (!query.exec()) {
        emit error(QString(tr("There is an error occured while inserting into database: «%1»")).arg(
                       query.lastError().text()));
    } else {
        newGroupName->clear();
        model->select();
    }
}
