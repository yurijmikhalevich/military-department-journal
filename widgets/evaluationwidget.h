#ifndef EVALUATIONWIDGET_H
#define EVALUATIONWIDGET_H

#include "basewidget.h"
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QSplitter>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QStyledItemDelegate>
#include "qt4table-steroids/relationalcombobox.h"

class EvaluationWidget : public BaseWidget {
  Q_OBJECT
public:
  explicit EvaluationWidget(QWidget *parent = 0);
private:
  QPushButton *addEvaluationButton;
  QPushButton *generateEvaluationListButton;
  TableSteroids::RelationalComboBox *subjectEdit;
  TableSteroids::RelationalComboBox *controlTypeEdit;
  TableSteroids::RelationalComboBox *teacherEdit;
  TableSteroids::RelationalComboBox *troopEdit;
  QDateEdit *dateEdit;
  QSplitter *containerLayout;
  QVBoxLayout *marksEditorLayout;
  QTableWidget *marksEditor;
  QVariant currentEvaluationId;
private slots:
  void addEvaluation();
  void generateEvaluationList();
  void onEvaluationSelected(QModelIndex selection);
  void onMarkChanged(int row, int column);
};

class ValueDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit ValueDelegate(QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex & index) const;
};

#endif // EVALUATIONWIDGET_H
