#ifndef SUBJECTDURATIONWIDGET_H
#define SUBJECTDURATIONWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>

class SubjectDurationWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit SubjectDurationWidget(QWidget *parent = 0);
private:
  QPushButton *addSubjectDurationButton;
  QComboBox *subjectEdit;
  QComboBox *professionEdit;
  QSpinBox *durationEdit;
private slots:
  void addSubjectDuration();
};

#endif // SUBJECTDURATIONWIDGET_H
