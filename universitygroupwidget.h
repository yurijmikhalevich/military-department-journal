#ifndef UNIVERSITYGROUPWIDGET_H
#define UNIVERSITYGROUPWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "universitygroupmodel.h"
#include "qt4table-steroids/steroidsview.h"

class UniversityGroupWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit UniversityGroupWidget(QWidget *parent = 0);
    
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlsLayout;
    QLineEdit *newGroupName;
    QSpinBox *yearOfGraduation;
    QPushButton *addNewButton;
    SteroidsView *view;
    UniversityGroupModel *model;
    UniversityGroupSortModel *sortModel;

private slots:
    void invalidInputReceived(QString &input);
    void newGroupNameTextChanged(QString text);
    void createNewGroup();
};

#endif // UNIVERSITYGROUPWIDGET_H
