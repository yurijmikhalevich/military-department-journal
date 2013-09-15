#include "militaryprofessionwidget.h"

#include <QSqlQuery>
#include <QSqlError>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "militaryprofessionmodel.h"

MilitaryProfessionWidget::MilitaryProfessionWidget(QWidget *parent) :
    BaseWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    model = new MilitaryProfessionModel(this);
    view->setModel(model);
    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged(QString)));
    controlsLayout = new QHBoxLayout();
    SQLUniqueSteroidsValidator *codeValidator = new SQLUniqueSteroidsValidator(model->tableName(), "code", this);
    SQLUniqueSteroidsValidator *nameValidator = new SQLUniqueSteroidsValidator(model->tableName(), "name", this);
    connect(codeValidator, SIGNAL(invalidInput(QString&)), this, SLOT(invalidCode(QString&)));
    connect(nameValidator, SIGNAL(invalidInput(QString&)), this, SLOT(invalidName(QString&)));
    LineEditDelegate *codeDelegate = new LineEditDelegate(codeValidator, this);
    LineEditDelegate *nameDelegate = new LineEditDelegate(nameValidator, this);
    codeEdit = static_cast<QLineEdit *>(codeDelegate->createEditor(this));
    nameEdit = static_cast<QLineEdit *>(nameDelegate->createEditor(this));
    codeEdit->setPlaceholderText(tr("Profession code"));
    nameEdit->setPlaceholderText(tr("Profession name"));
    addNewButton = new QPushButton(tr("Add profession"), this);
    addNewButton->setDisabled(true);
    connect(codeEdit, SIGNAL(returnPressed()), nameEdit, SLOT(setFocus()));
    connect(nameEdit, SIGNAL(returnPressed()), this, SLOT(addNewProfession()));
    connect(addNewButton, SIGNAL(clicked()), this, SLOT(addNewProfession()));
    connect(codeEdit, SIGNAL(textChanged(QString)), this, SLOT(newInputChanged(QString)));
    connect(nameEdit, SIGNAL(textChanged(QString)), this, SLOT(newInputChanged(QString)));
    controlsLayout->addWidget(codeEdit);
    controlsLayout->addWidget(nameEdit);
    controlsLayout->addWidget(addNewButton);
    mainLayout->addWidget(view);
    mainLayout->addLayout(controlsLayout);
}

void MilitaryProfessionWidget::invalidCode(QString &input)
{
    emit error(QString("Profession with code «%1» already exists").arg(input));
}

void MilitaryProfessionWidget::invalidName(QString &input)
{
    emit error(QString("Profession with name «%1» already exists").arg(input));
}

void MilitaryProfessionWidget::newInputChanged(QString)
{
    if (!codeEdit->text().isEmpty() && !nameEdit->text().isEmpty()) {
        addNewButton->setEnabled(true);
    } else {
        addNewButton->setDisabled(true);
    }
}

void MilitaryProfessionWidget::addNewProfession()
{
    if (codeEdit->text().isEmpty() || nameEdit->text().isEmpty()) {
        return;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO military_profession (code, name) VALUES (?, ?)");
    query.addBindValue(codeEdit->text());
    query.addBindValue(nameEdit->text());
    if (!query.exec()) {
        emit error(QString(tr("There is an error occured while inserting into database: «%1»")).arg(
                       query.lastError().text()));
    } else {
        codeEdit->clear();
        nameEdit->clear();
        codeEdit->setFocus();
        model->select();
    }
}
