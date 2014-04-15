#ifndef TROOPRELATIONALDELEGATE_H
#define TROOPRELATIONALDELEGATE_H

#include <QStyledItemDelegate>

class TroopRelationalDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit TroopRelationalDelegate(QObject *parent = 0);
  QWidget *createEditor(
      QWidget *parent,
      const QStyleOptionViewItem &option = QStyleOptionViewItem(),
      const QModelIndex &index = QModelIndex()) const;
  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;
};

#endif // TROOPRELATIONALDELEGATE_H
