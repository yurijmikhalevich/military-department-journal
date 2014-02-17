#ifndef MARKWIDGET_H
#define MARKWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>

class MarkWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit MarkWidget(QWidget *parent = 0);
private:
  QPushButton *addMarkButton;
  QComboBox *evaluationEdit;
  QComboBox *studentEdit;
  QSpinBox *valueEdit;
  QComboBox *teacherEdit;
  QDateEdit *dateEdit;
private slots:
  void addMark();
};

#endif // MARKWIDGET_H
