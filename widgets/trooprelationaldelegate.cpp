#include "trooprelationaldelegate.h"
#include "qt4table-steroids/relationalcombobox.h"

TroopRelationalDelegate::TroopRelationalDelegate(QObject *parent)
  : QStyledItemDelegate(parent) {
}

QWidget *TroopRelationalDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  return new TableSteroids::RelationalComboBox("troop", "name", "troops",
                                               parent);
}

void TroopRelationalDelegate::setEditorData(
    QWidget *editor, const QModelIndex &index) const {
  TableSteroids::RelationalComboBox *cb =
      static_cast<TableSteroids::RelationalComboBox *>(editor);
  int ind = cb->findText(index.data().toString());
  if (ind == -1) {
    return;
  }
  cb->setCurrentIndex(ind);
}

void TroopRelationalDelegate::setModelData(
    QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const {
  TableSteroids::RelationalComboBox *cb =
      static_cast<TableSteroids::RelationalComboBox *>(editor);
  model->setData(index, cb->currentId());
}
