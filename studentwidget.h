#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include "basewidget.h"

#include <QLineEdit>
#include <QComboBox>

#include "studentmodel.h"

class StudentWidget : public BaseWidget
{
    Q_OBJECT
    
public:
    explicit StudentWidget(QWidget *parent = 0);
    ~StudentWidget();

public slots:
    void enable();
    void globalSearchQueryChanged(QString query);

private:
    StudentModel *model;
};

#endif // STUDENTWIDGET_H
