#ifndef MILITARYPROFESSIONWIDGET_H
#define MILITARYPROFESSIONWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class MilitaryProfessionWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit MilitaryProfessionWidget(QWidget *parent = 0);
private:
  QHBoxLayout *controlsLayout;
  QVBoxLayout *mainLayout;
  QLineEdit *codeEdit;
  QLineEdit *nameEdit;
  QPushButton *addNewButton;
  QCheckBox *showArchivedCheckBox;
  bool isNameInvalid;
  bool isCodeInvalid;
private slots:
  void invalidCode(QString &input);
  void invalidName(QString &input);
  void validCode(QString &input);
  void validName(QString &input);
  void checkButtonState();
  void addNewProfession();
};

#endif // MILITARYPROFESSIONWIDGET_H
