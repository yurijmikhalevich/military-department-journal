#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include "basewidget.h"

#include <QLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QCalendarWidget>
#include <QPushButton>

#include "qt4table-steroids/steroidsview.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "qt4table-steroids/checkboxdelegate.h"

#include "studentmodel.h"

class StudentWidget : public BaseWidget
{
    Q_OBJECT
    
public:
    explicit StudentWidget(QWidget *parent = 0);
    ~StudentWidget();

private:
    QLayout *createControlsLayout();

    SteroidsView *view;
    StudentModel *model;

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
    QComboBox *troopEdit;

    QPushButton *addStudentButton;
};

#endif // STUDENTWIDGET_H
