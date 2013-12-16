#ifndef UNIVERSITYFACULTYWIDGET_H
#define UNIVERSITYFACULTYWIDGET_H

#include "basewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QSortFilterProxyModel>

class UniversityFacultyWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit UniversityFacultyWidget(QWidget *parent = 0);
    
private:
  QVBoxLayout *mainLayout;
  QHBoxLayout *controlsLayout;
  QLineEdit *newFacultyName;
  QPushButton *addNewButton;

private slots:
  void invalidInputReceived(QString &input);
  void newFacultyNameTextChanged(QString text);
  void createNewFaculty();
};

#endif // UNIVERSITYFACULTYWIDGET_H
