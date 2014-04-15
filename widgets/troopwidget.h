#ifndef TROOPWIDGET_H
#define TROOPWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDateEdit>
#include "qt4table-steroids/relationalcombobox.h"
#include "troopnamedelegate.h"

class TroopWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit TroopWidget(QWidget *parent = 0);
private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *controlsLayout;
  TroopNameEditor *nameEdit;
  QDateEdit *enteredInEdit;
  TableSteroids::RelationalComboBox *curatorEdit;
  TableSteroids::RelationalComboBox *professionEdit;
  QPushButton *addTroopButton;
  QCheckBox *showGraduatedCheckBox;
private slots:
  void addTroop();
};

#endif // TROOPWIDGET_H
