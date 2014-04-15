#ifndef SUBJECTWIDGET_H
#define SUBJECTWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>

class SubjectWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit SubjectWidget(QWidget *parent = 0);
private:
  QPushButton *addSubjectButton;
  QLineEdit *subjectNameEdit;
  QCheckBox *showArchivedCheckBox;
  QHBoxLayout *containerLayout;
  QVBoxLayout *hoursEditorLayout;
  QTableWidget *hoursEditor;
  QVariant currentSubjectId;
private slots:
  void addSubject();
  void onSubjectNameEditChanged();
  void onSubjectSelected(QModelIndex selection);
  void onSubjectDurationChanged(int row);
};

#endif // SUBJECTWIDGET_H
