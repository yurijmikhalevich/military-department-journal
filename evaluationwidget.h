#ifndef EVALUATIONWIDGET_H
#define EVALUATIONWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>

class EvaluationWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit EvaluationWidget(QWidget *parent = 0);
private:
    QPushButton *addEvaluationButton;
    QPushButton *generateEvaluationListButton;
    QComboBox *subjectEdit;
    QComboBox *controlTypeEdit;
    QComboBox *teacherEdit;
    QComboBox *universityGroupEdit;
    QDateEdit *dateEdit;
private slots:
    void addEvaluation();
    void generateEvaluationList();

};

#endif // EVALUATIONWIDGET_H
