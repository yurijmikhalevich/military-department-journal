#ifndef SUBJECTWIDGET_H
#define SUBJECTWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QLineEdit>

class SubjectWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit SubjectWidget(QWidget *parent = 0);
private:
    QPushButton *addSubjectButton;
    QLineEdit *subjectNameEdit;
private slots:
    void addSubject();
    
};

#endif // SUBJECTWIDGET_H
