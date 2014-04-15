#ifndef TROOPNAMEDELEGATE_H
#define TROOPNAMEDELEGATE_H

#include <QStyledItemDelegate>

class TroopNameDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit TroopNameDelegate(QObject *parent = 0);
  QWidget *createEditor(
      QWidget *parent,
      const QStyleOptionViewItem &option = QStyleOptionViewItem(),
      const QModelIndex &index = QModelIndex()) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;
};

#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QList>
#include <QToolButton>

class TroopNameEditor : public QWidget {
  Q_OBJECT
public:
  explicit TroopNameEditor(QWidget *parent = 0);
  TroopNameEditor(QString troopName, QWidget *parent = 0);
  void setTroopName(QString troopName);
  QString troopName();
private:
  QLineEdit *prefix;
  QSpinBox *yearEnteredOne;
  QSpinBox *yearEnteredTwo;
  QSpinBox *numberOne;
  QSpinBox *numberTwo;
  QLabel *dash;
  QLabel *separator;
  QToolButton *addRemoveYearButton;
  QHBoxLayout *mainLayout;
  int compactWidth;
  int fullWidth;
private slots:
  void toggleSecondPart();
};

#endif // TROOPNAMEDELEGATE_H
