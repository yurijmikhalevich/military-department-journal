#include "teacherwidget.h"
#include "qt4table-steroids/checkboxdelegate.h"
#include "models/teachermodel.h"

TeacherWidget::TeacherWidget(QWidget *parent) :
    BaseWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    controlsLayout = new QHBoxLayout();
    model = new TeacherModel(view);
    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged(QString)));
    view->setModel(model);
    view->setItemDelegateForColumn(1, new CheckBoxDelegate(view));
    showDismissedCheckBox = new QCheckBox(tr("Show dismissed"), this);
    connect(showDismissedCheckBox, SIGNAL(toggled(bool)), model, SLOT(showDismissed(bool)));
    teacherName = new QLineEdit(this);
    teacherName->setPlaceholderText(tr("Name"));
    addTeacherButton = new QPushButton(tr("Add teacher"), this);
    addTeacherButton->setEnabled(false);
    connect(teacherName, SIGNAL(returnPressed()), this, SLOT(addTeacher()));
    connect(addTeacherButton, SIGNAL(clicked()), this, SLOT(addTeacher()));
    connect(teacherName, SIGNAL(textChanged(QString)), this, SLOT(teacherNameChanged(QString)));
    controlsLayout->addWidget(teacherName);
    controlsLayout->addWidget(addTeacherButton);
    mainLayout->addWidget(showDismissedCheckBox);
    mainLayout->addWidget(view);
    mainLayout->addLayout(controlsLayout);
}

void TeacherWidget::teacherNameChanged(QString name)
{
    if (name.isEmpty()) {
        addTeacherButton->setDisabled(true);
    } else {
        addTeacherButton->setEnabled(true);
    }
}

void TeacherWidget::addTeacher()
{
    QString name = teacherName->text().simplified();
    if (name.isEmpty()) {
        teacherName->setFocus();
        emit error(tr("Teacher name shouldn't be empty"));
        return;
    }
    QVariantMap newTeacher;
    newTeacher.insert("name", name);
    if (insertRecord(newTeacher)) {
        teacherName->clear();
    }
}
