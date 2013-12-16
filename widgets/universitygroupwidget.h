#ifndef UNIVERSITYGROUPWIDGET_H
#define UNIVERSITYGROUPWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QSortFilterProxyModel>

class UniversityGroupWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit UniversityGroupWidget(QWidget *parent = 0);
private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *controlsLayout;
  QLineEdit *newGroupName;
  QSpinBox *yearOfGraduation;
  QComboBox *facultyEditor;
  QComboBox *troopEditor;
  QPushButton *addNewButton;
  QSortFilterProxyModel *sortModel;
private slots:
  void invalidInputReceived(QString &input);
  void newGroupNameTextChanged(QString text);
  void createNewGroup();
};

#endif // UNIVERSITYGROUPWIDGET_H
