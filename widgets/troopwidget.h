#ifndef TROOPWIDGET_H
#define TROOPWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

class TroopWidget : public BaseWidget
{
    Q_OBJECT
public:
    explicit TroopWidget(QWidget *parent = 0);
private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlsLayout;
    QLineEdit *nameEdit;
    QSpinBox *ygmEdit;
    QComboBox *curatorEdit;
    QPushButton *addTroopButton;
private slots:
    void addTroop();
};

#endif // TROOPWIDGET_H
