#ifndef UNIVERSITYGROUPWIDGET_H
#define UNIVERSITYGROUPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "universitygroupmodel.h"
#include "qt4table-steroids/steroidsview.h"

class UniversityGroupWidget : public QWidget
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
};

#include "qt4table-steroids/steroidsvalidator.h"
#include <QSqlQuery>

class TestValidator : public SteroidsValidator
{
    Q_OBJECT
public:
    explicit TestValidator(QObject *parent = 0) :
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
            return Invalid;
        }
        return Acceptable;
    }
};

#endif // UNIVERSITYGROUPWIDGET_H
