#ifndef UNIVERSITYGROUPWIDGET_H
#define UNIVERSITYGROUPWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QSortFilterProxyModel>
#include "qt4table-steroids/relationalcombobox.h"

class UniversityGroupWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit UniversityGroupWidget(QWidget *parent = 0);
private:
  QVBoxLayout *mainLayout;
  QVBoxLayout *controlsLayout;
  QLineEdit *newGroupName;
  QSpinBox *yearOfGraduation;
  TableSteroids::RelationalComboBox *facultyEditor;
  TableSteroids::RelationalComboBox *troopEditor;
  QPushButton *addNewButton;
  QSortFilterProxyModel *sortModel;
  QCheckBox *showGraduatedCheckBox;
private slots:
  void invalidInputReceived(QString &input);
  void newGroupNameTextChanged(QString text);
  void createNewGroup();
};

#endif // UNIVERSITYGROUPWIDGET_H
