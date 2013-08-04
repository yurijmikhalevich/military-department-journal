#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

#include "basewidget.h"

class TeacherWidget : public BaseWidget
{
    Q_OBJECT
    
public:
    explicit TeacherWidget(QWidget *parent = 0);
    ~TeacherWidget();

signals:
    void queryChanged(QString query);

private slots:
    void addRow();
    void on_addTeacher_clicked();
};

#endif // TEACHERWIDGET_H
