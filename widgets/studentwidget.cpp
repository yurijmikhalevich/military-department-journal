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
#include <QSqlRelationalDelegate>
#include "models/studentmodel.h"
#include "qt4table-steroids/datedelegate.h"

StudentWidget::StudentWidget(QWidget *parent)
    : BaseWidget(parent) {
  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  view->setItemDelegate(new QSqlRelationalDelegate(view));
  mainLayout->addWidget(view);
  model = new StudentModel(view);
  connect(this, SIGNAL(queryChanged(QString)),
          model, SLOT(queryChanged(QString)));
  view->setModel(model);
  mainLayout->addLayout(createControlsLayout());
  nameMorpher = new NameMorpher(this);
}

StudentWidget::~StudentWidget() {
}

QLayout *StudentWidget::createControlsLayout() {
  lastnameEdit = new QLineEdit(this);
  firstnameEdit = new QLineEdit(this);
  middlenameEdit = new QLineEdit(this);
  lastnameDatumEdit = new QLineEdit(this);
  firstnameDatumEdit = new QLineEdit(this);
  middlenameDatumEdit = new QLineEdit(this);
  lastnameAccusativeEdit = new QLineEdit(this);
  firstnameAccusativeEdit = new QLineEdit(this);
  middlenameAccusativeEdit = new QLineEdit(this);
  for (QLineEdit *le : {lastnameEdit, firstnameEdit, middlenameEdit,
       lastnameDatumEdit, firstnameDatumEdit, middlenameDatumEdit,
       lastnameAccusativeEdit, firstnameAccusativeEdit,
       middlenameAccusativeEdit}) {
    le->setMinimumWidth(80);
  }
  QLabel *lastname = new QLabel(tr("Фамилия"));
  QLabel *firstname = new QLabel(tr("Имя"));
  QLabel *middlename = new QLabel(tr("Отчество"));
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
  nameLayout->addRow(tr("Именительный"), nominativeLayout);
  QHBoxLayout *datumLayout = new QHBoxLayout();
  datumLayout->addWidget(lastnameDatumEdit);
  datumLayout->addWidget(firstnameDatumEdit);
  datumLayout->addWidget(middlenameDatumEdit);
  nameLayout->addRow(tr("Дательный"), datumLayout);
  QHBoxLayout *accusativeLayout = new QHBoxLayout();
  accusativeLayout->addWidget(lastnameAccusativeEdit);
  accusativeLayout->addWidget(firstnameAccusativeEdit);
  accusativeLayout->addWidget(middlenameAccusativeEdit);
  nameLayout->addRow(tr("Винительный"), accusativeLayout);
  controlsLayout->addItem(nameLayout);
  QFormLayout *secondRowLayout = new QFormLayout();
  decreeEnrollmentNumberEdit = new QLineEdit(this);
  QHBoxLayout *dobLayout = new QHBoxLayout();
  QDate defaultDate = QDate(QDate::currentDate().year() - 19, 1, 1);
  DateDelegate *dobDelegate = new DateDelegate(
        defaultDate, this, QDate(1900, 1, 1), QDate::currentDate());
  view->setItemDelegateForColumn(10, dobDelegate);
  dobEdit = static_cast<QDateEdit *>(dobDelegate->createEditor(this));
  dobLayout->addWidget(dobEdit);
  secondRowLayout->addRow(tr("Приказ о зачислении"),
                          decreeEnrollmentNumberEdit);
  secondRowLayout->addRow(tr("Дата рождения"), dobLayout);
  controlsLayout->addLayout(secondRowLayout);
  QFormLayout *thirdRowLayout = new QFormLayout();
  universityGroupEdit =
      new TableSteroids::RelationalComboBox("university_group", "name");
  thirdRowLayout->addRow(tr("Группа"), universityGroupEdit);
  controlsLayout->addLayout(thirdRowLayout);
  addStudentButton = new QPushButton(tr("Добавить студента"));
  connect(addStudentButton, SIGNAL(clicked()), this, SLOT(addStudent()));
  controlsLayout->addWidget(addStudentButton);
  connect(middlenameEdit, SIGNAL(editingFinished()), this, SLOT(morphName()));
  return controlsLayout;
}

void StudentWidget::addStudent() {
  QSqlQuery query;
  query.prepare("INSERT INTO student (lastname, firstname, middlename,"
                " lastname_datum, firstname_datum, middlename_datum,"
                " lastname_accusative, firstname_accusative,"
                " middlename_accusative, dob, university_group_id,"
                " decree_enrollment_number)"
                " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
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
  query.addBindValue(universityGroupEdit->currentId());
  query.addBindValue(decreeEnrollmentNumberEdit->text());
//    query.addBindValue(troopEdit->itemData(troopEdit->currentIndex()));
  if (!query.exec()) {
    qDebug() << query.lastError().databaseText();
    throw query.lastError(); // FIXME: replace with signal emitting
  }
  model->select();
}

void StudentWidget::morphName() {
  NameMorpher::MorphedName morphedName = nameMorpher->getMorphedName(
        lastnameEdit->text(), firstnameEdit->text(), middlenameEdit->text());
  lastnameDatumEdit->setText(morphedName.lastnameDatum);
  firstnameDatumEdit->setText(morphedName.firstnameDatum);
  middlenameDatumEdit->setText(morphedName.middlenameDatum);
  lastnameAccusativeEdit->setText(morphedName.lastnameAccusative);
  firstnameAccusativeEdit->setText(morphedName.firstnameAccusative);
  middlenameAccusativeEdit->setText(morphedName.middlenameAccusative);
}
