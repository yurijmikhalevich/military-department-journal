#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

class TeacherWidget : public BaseWidget
{
    Q_OBJECT
    
public:
    explicit TeacherWidget(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlsLayout;
    QCheckBox *showDismissedCheckBox;
    QPushButton *addTeacherButton;
    QLineEdit *teacherName;
signals:
    void queryChanged(QString query);
private slots:
    void teacherNameChanged(QString name);
    void addTeacher();
};

#endif // TEACHERWIDGET_H
