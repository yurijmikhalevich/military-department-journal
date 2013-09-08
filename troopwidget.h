#ifndef TROOPWIDGET_H
#define TROOPWIDGET_H

#include "basewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

#include "qt4table-steroids/steroidsview.h"

#include "troopmodel.h"

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
    SteroidsView *view;
    TroopModel *model;

private slots:
    void addTroop();
};

#endif // TROOPWIDGET_H
