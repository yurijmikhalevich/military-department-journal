#include "studentwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QCalendarWidget>
#include <QToolButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include "qt4table-steroids/tablehelper.h"
#include "studentmodel.h"

QNetworkAccessManager *StudentWidget::networkManager = new QNetworkAccessManager();

StudentWidget::StudentWidget(QWidget *parent) :
    BaseWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(view);
    model = new StudentModel(view);
    connect(this, SIGNAL(queryChanged(QString)), model, SLOT(queryChanged));
    view->setModel(model);
    mainLayout->addLayout(createControlsLayout());
}

StudentWidget::~StudentWidget()
{
}

QLayout *StudentWidget::createControlsLayout()
{
    lastnameEdit = new QLineEdit(this);
    firstnameEdit = new QLineEdit(this);
    middlenameEdit = new QLineEdit(this);
    lastnameDatumEdit = new QLineEdit(this);
    firstnameDatumEdit = new QLineEdit(this);
    middlenameDatumEdit = new QLineEdit(this);
    lastnameAccusativeEdit = new QLineEdit(this);
    firstnameAccusativeEdit = new QLineEdit(this);
    middlenameAccusativeEdit = new QLineEdit(this);
    QLabel *lastname = new QLabel(tr("Lastname"));
    QLabel *firstname = new QLabel(tr("Firstname"));
    QLabel *middlename = new QLabel(tr("Middlename"));
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    QFormLayout *nameLayout = new QFormLayout();
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(middlename);
    headerLayout->addWidget(firstname);
    headerLayout->addWidget(lastname);
    nameLayout->addRow(nullptr, headerLayout);
    QHBoxLayout *nominativeLayout = new QHBoxLayout();
    nominativeLayout->addWidget(lastnameEdit);
    nominativeLayout->addWidget(firstnameEdit);
    nominativeLayout->addWidget(middlenameEdit);
    nameLayout->addRow(tr("Nominative"), nominativeLayout);
    QHBoxLayout *datumLayout = new QHBoxLayout();
    datumLayout->addWidget(lastnameDatumEdit);
    datumLayout->addWidget(firstnameDatumEdit);
    datumLayout->addWidget(middlenameDatumEdit);
    nameLayout->addRow(tr("Datum"), datumLayout);
    QHBoxLayout *accusativeLayout = new QHBoxLayout();
    accusativeLayout->addWidget(lastnameAccusativeEdit);
    accusativeLayout->addWidget(firstnameAccusativeEdit);
    accusativeLayout->addWidget(middlenameAccusativeEdit);
    nameLayout->addRow(tr("Accusative"), accusativeLayout);
    controlsLayout->addItem(nameLayout);
    QFormLayout *secondRowLayout = new QFormLayout();
    decreeEnrollmentNumberEdit = new QLineEdit(this);
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
    universityGroupEdit = TableHelper::createRelationalEditor("university_group", "name");
    troopEdit = TableHelper::createRelationalEditor("troop", "name");
    thirdRowLayout->addRow(tr("University group"), universityGroupEdit);
    thirdRowLayout->addRow(tr("Troop"), troopEdit);
    controlsLayout->addLayout(thirdRowLayout);
    addStudentButton = new QPushButton(tr("Add student"));
    connect(addStudentButton, SIGNAL(clicked()), this, SLOT(addStudent()));
    controlsLayout->addWidget(addStudentButton);
    connect(middlenameEdit, SIGNAL(editingFinished()), this, SLOT(morphName()));
    return controlsLayout;
}

void StudentWidget::addStudent()
{
    QSqlQuery query;
    query.prepare("INSERT INTO student (lastname, firstname, middlename, lastname_datum, firstname_datum,"
                  "middlename_datum, lastname_accusative, firstname_accusative, middlename_accusative,"
                  "dob, university_group_id, decree_enrollment_number, troop_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                  "?, ?, ?)");
    query.addBindValue(lastnameEdit->text());
    query.addBindValue(firstnameEdit->text());
    query.addBindValue(middlenameEdit->text());
    query.addBindValue(lastnameDatumEdit->text());
    query.addBindValue(firstnameDatumEdit->text());
    query.addBindValue(middlenameDatumEdit->text());
    query.addBindValue(lastnameAccusativeEdit->text());
    query.addBindValue(firstnameAccusativeEdit->text());
    query.addBindValue(middlenameAccusativeEdit->text());
    query.addBindValue(dobEdit->date());
    query.addBindValue(universityGroupEdit->itemData(universityGroupEdit->currentIndex()));
    query.addBindValue(decreeEnrollmentNumberEdit->text());
    query.addBindValue(troopEdit->itemData(troopEdit->currentIndex()));
    if (!query.exec()) {
        qDebug() << query.lastError().databaseText();
        throw query.lastError(); // FIXME: replace with signal emitting
    }
    model->select();
}

void StudentWidget::morphName()
{
    QNetworkRequest request("http://morpher.ru/WebService.asmx/GetXml?s="
                            + QStringList({ lastnameEdit->text(), firstnameEdit->text(),
                                            middlenameEdit->text() }).join(" "));
    QNetworkReply *reply = networkManager->get(request);
    QEventLoop *loop = new QEventLoop();
    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
    loop->exec();
    QString response = QString(reply->readAll());
    QStringList accusative = response.split("<В>").at(1).split("</В>").at(0).split(" ");
    QStringList datum = response.split("<Д>").at(1).split("</Д>").at(0).split(" ");
    lastnameDatumEdit->setText(datum.at(0));
    firstnameDatumEdit->setText(datum.at(1));
    middlenameDatumEdit->setText(datum.at(2));
    lastnameAccusativeEdit->setText(accusative.at(0));
    firstnameAccusativeEdit->setText(accusative.at(1));
    middlenameAccusativeEdit->setText(accusative.at(2));
//    if (response.contains("<В>")) {
//        return response.split("<В>").at(1).split("</В>").at(0);
//    } else {
//        sleep(3);
//        qDebug() << "error wetching Accuzative, retrying in 3 secs";
//        return getAccuzative(studentName);
//    }
}
