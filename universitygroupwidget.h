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

#include "qt4table-steroids/steroidsvalidator.h"
#include <QSqlQuery>

class UniversityGroupNameValidator : public SteroidsValidator
{
    Q_OBJECT
public:
    explicit UniversityGroupNameValidator(QObject *parent = 0) :
        SteroidsValidator(parent) {}
    State validate(QString &input, int &) const
    {
        if (input == modelData) {
            return Acceptable;
        }
        QSqlQuery query;
        query.prepare("SELECT id FROM university_group WHERE name = ? LIMIT 1");
        query.addBindValue(input);
        if (!query.exec() || query.next()) {
            emit invalidInput(input);
            return Invalid;
        }
        return Acceptable;
    }
signals:
    void invalidInput(QString &input) const;
};

#endif // UNIVERSITYGROUPWIDGET_H
