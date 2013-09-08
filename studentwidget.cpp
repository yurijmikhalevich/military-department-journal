#include "studentwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QToolButton>

#include "qt4table-steroids/tablehelper.h"

StudentWidget::StudentWidget(QWidget *parent) :
    BaseWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    view = new SteroidsView(this);
    mainLayout->addWidget(view);
    model = new StudentModel(view);
    view->setModel(model);
    mainLayout->addLayout(createControlsLayout());
}

StudentWidget::~StudentWidget()
{
}

QLayout *StudentWidget::createControlsLayout()
{
    firstnameEdit = new QLineEdit(this);
    firstnameDatumEdit = new QLineEdit(this);
    firstnameAccusativeEdit = new QLineEdit(this);
    middlenameEdit = new QLineEdit(this);
    middlenameDatumEdit = new QLineEdit(this);
    middlenameAccusativeEdit = new QLineEdit(this);
    lastnameEdit = new QLineEdit(this);
    lastnameDatumEdit = new QLineEdit(this);
    lastnameAccusativeEdit = new QLineEdit(this);
    QLabel *nominative = new QLabel(tr("Nominative"));
    QLabel *datum = new QLabel(tr("Datum"));
    QLabel *accusative = new QLabel(tr("Accusative"));
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    QFormLayout *nameLayout = new QFormLayout();
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(nominative);
    headerLayout->addWidget(datum);
    headerLayout->addWidget(accusative);
    nameLayout->addRow(nullptr, headerLayout);
    QHBoxLayout *firstnameLayout = new QHBoxLayout();
    firstnameLayout->addWidget(firstnameEdit);
    firstnameLayout->addWidget(firstnameDatumEdit);
    firstnameLayout->addWidget(firstnameAccusativeEdit);
    nameLayout->addRow(tr("Firstname"), firstnameLayout);
    QHBoxLayout *middlenameLayout = new QHBoxLayout();
    middlenameLayout->addWidget(middlenameEdit);
    middlenameLayout->addWidget(middlenameDatumEdit);
    middlenameLayout->addWidget(middlenameAccusativeEdit);
    nameLayout->addRow(tr("Middlename"), middlenameLayout);
    QHBoxLayout *lastnameLayout = new QHBoxLayout();
    lastnameLayout->addWidget(lastnameEdit);
    lastnameLayout->addWidget(lastnameDatumEdit);
    lastnameLayout->addWidget(lastnameAccusativeEdit);
    nameLayout->addRow(tr("Lastname"), lastnameLayout);
    controlsLayout->addItem(nameLayout);
    QFormLayout *secondRowLayout = new QFormLayout();
    QLineEdit *decreeEnrollmentNumberEdit = new QLineEdit(this);
    QHBoxLayout *dobLayout = new QHBoxLayout();
    dobEdit = new QDateEdit(this);
    QToolButton *dobButton = new QToolButton(this);
    QCalendarWidget *calendar = new QCalendarWidget();
    calendar->hide();
    connect(calendar, SIGNAL(activated(QDate)), dobEdit, SLOT(setDate(QDate)));
    connect(dobButton, SIGNAL(clicked()), calendar, SLOT(show()));
    dobLayout->addWidget(dobEdit);
    dobLayout->addWidget(dobButton);
    secondRowLayout->addRow(tr("Enrollment number"), decreeEnrollmentNumberEdit);
    secondRowLayout->addRow(tr("Date of birth"), dobLayout);
    controlsLayout->addLayout(secondRowLayout);
    QFormLayout *thirdRowLayout = new QFormLayout();
    universityGroupEdit = new QComboBox(this);
    troopEdit = new QComboBox(this);
    thirdRowLayout->addRow(tr("University group"), universityGroupEdit);
    thirdRowLayout->addRow(tr("Troop"), troopEdit);
    controlsLayout->addLayout(thirdRowLayout);
    addStudentButton = new QPushButton(tr("Add student"));
    controlsLayout->addWidget(addStudentButton);
    return controlsLayout;
}
