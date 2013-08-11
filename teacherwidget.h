#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include "basewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>

#include "qt4table-steroids/steroidsview.h"

#include "teachermodel.h"

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
    SteroidsView *view;
    TeacherModel *model;

signals:
    void queryChanged(QString query);

private slots:
    void teacherNameChanged(QString name);
    void addTeacher();
};

#endif // TEACHERWIDGET_H
