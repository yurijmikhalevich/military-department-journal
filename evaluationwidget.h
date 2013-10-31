#ifndef EVALUATIONWIDGET_H
#define EVALUATIONWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QLineEdit>

class EvaluationWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit EvaluationWidget(QWidget *parent = 0);
private:
    QPushButton *addSubjectButton;
    QLineEdit *subjectNameEdit;
private slots:
    void addSubject();

};

#endif // EVALUATIONWIDGET_H
