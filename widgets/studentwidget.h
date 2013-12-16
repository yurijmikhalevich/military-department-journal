#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include "basewidget.h"
#include <QLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QPushButton>
#include <QNetworkAccessManager>
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "qt4table-steroids/checkboxdelegate.h"

class StudentWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit StudentWidget(QWidget *parent = 0);
  ~StudentWidget();
private:
  QLayout *createControlsLayout();
  static QNetworkAccessManager *networkManager;
  QLineEdit *firstnameEdit;
  QLineEdit *middlenameEdit;
  QLineEdit *lastnameEdit;
  QLineEdit *firstnameDatumEdit;
  QLineEdit *middlenameDatumEdit;
  QLineEdit *lastnameDatumEdit;
  QLineEdit *firstnameAccusativeEdit;
  QLineEdit *middlenameAccusativeEdit;
  QLineEdit *lastnameAccusativeEdit;
  QDateEdit *dobEdit;
//    QCalendarWidget *dobCalendar;
  QComboBox *universityGroupEdit;
  QLineEdit *decreeEnrollmentNumberEdit;
//    QLineEdit *decreeExpulsionNumberEdit;
//    QComboBox *expulsionReasonEdit;
//    QComboBox *expulsedFromEdit;
//  QComboBox *troopEdit;
  QPushButton *addStudentButton;
private slots:
  void addStudent();
  void morphName();
};

#endif // STUDENTWIDGET_H
