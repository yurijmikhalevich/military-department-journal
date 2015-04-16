#include "troopnamedelegate.h"
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <functional>

TroopNameDelegate::TroopNameDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

QWidget *TroopNameDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  TroopNameEditor *editor = new TroopNameEditor(parent);
  QPalette palette = editor->palette();
  palette.setBrush(QPalette::Window, option.backgroundBrush);
  editor->setPalette(palette);
  editor->setAutoFillBackground(true);
  return editor;
}

void TroopNameDelegate::setEditorData(
    QWidget *editor, const QModelIndex &index) const {
  static_cast<TroopNameEditor *>(editor)->setTroopName(
        index.data(Qt::EditRole).toString());
}

void TroopNameDelegate::setModelData(
    QWidget *editor,
    QAbstractItemModel *model, const QModelIndex &index) const {
  QString troopName = static_cast<TroopNameEditor *>(editor)->troopName();
  model->setData(index, troopName);
}


TroopNameEditor::TroopNameEditor(QWidget *parent)
    : QWidget(parent),
      prefix(new QLineEdit(this)),
      yearEnteredOne(new QSpinBox(this)),
      yearEnteredTwo(new QSpinBox(this)),
      numberOne(new QSpinBox(this)),
      numberTwo(new QSpinBox(this)),
      dash(new QLabel("—", this)),
      separator(new QLabel("/", this)),
      addRemoveYearButton(new QToolButton(this)),
      mainLayout(new QHBoxLayout(this)) {
  mainLayout->addWidget(prefix);
  mainLayout->addWidget(dash);
  mainLayout->addWidget(yearEnteredOne);
  mainLayout->addWidget(numberOne);
  mainLayout->addWidget(separator);
  mainLayout->addWidget(yearEnteredTwo);
  mainLayout->addWidget(numberTwo);
  mainLayout->addWidget(addRemoveYearButton);
  connect(addRemoveYearButton, SIGNAL(clicked()),
          this, SLOT(toggleSecondPart()));
  connect(numberOne, SIGNAL(valueChanged(int)), numberTwo, SLOT(setValue(int)));
  connect(numberTwo, SIGNAL(valueChanged(int)), numberOne, SLOT(setValue(int)));
  for (QSpinBox *sb : {yearEnteredOne, yearEnteredTwo, numberOne, numberTwo}) {
    sb->setMinimum(1);
    sb->setMinimumWidth(35);
    sb->setMaximumWidth(35);
  }
  for (QSpinBox *sb : {yearEnteredOne, yearEnteredTwo}) {
    sb->setMaximum(5);
  }
  for (QSpinBox *sb : {numberOne, numberTwo}) {
    sb->setMaximum(9);
  }
  for (QLabel *l : {dash, separator}) {
    l->setMinimumWidth(3);
    l->setMaximumWidth(3);
  }
  prefix->setMinimumWidth(25);
  prefix->setMaximumWidth(25);
  prefix->setPlaceholderText(tr("ПИ"));
  std::vector<QWidget *> widgets = {yearEnteredOne, yearEnteredTwo,
                                     numberOne, numberTwo, prefix, separator,
                                     dash, addRemoveYearButton};
  for (QWidget *w : widgets) {
    w->setContentsMargins(0, 0, 0, 0);
  }
  dash->setMinimumWidth(6);
  dash->setMaximumWidth(6);
  separator->setMinimumWidth(7);
  separator->setMaximumWidth(7);
  compactWidth = 25 + 6 + 35 + 35 + 50;
  fullWidth = compactWidth + 7 + 35 + 35;
  toggleSecondPart();
  this->setLayout(mainLayout);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  this->setContentsMargins(0, 0, 0, 0);
  setTroopName("-<N:2>1");
}

TroopNameEditor::TroopNameEditor(QString troopName, QWidget *parent)
    : TroopNameEditor(parent) {
  setTroopName(troopName);
}

void TroopNameEditor::setTroopName(QString troopName) {
  QStringList splittedTroopName = troopName.split("-");
  if (splittedTroopName.length() != 2) {
    qDebug() << "void TroopNameEditor::setTroopName(QString troopName)" <<
                "invalid troop name" << troopName;
    return;
  }
  prefix->setText(splittedTroopName.at(0));
  splittedTroopName = splittedTroopName.at(1).split("/");
  if (splittedTroopName.length() > 2) {
    qDebug() << "void TroopNameEditor::setTroopName(QString troopName)" <<
                "invalid troop name, unsopported years amount" << troopName;
    return;
  }
  if ((splittedTroopName.length() == 2 &&
       addRemoveYearButton->text() == "+") ||
      (splittedTroopName.length() == 1 &&
       addRemoveYearButton->text() == "-")) {
    toggleSecondPart();
  }
  bool ok;
  std::vector<std::function<void(void)>> funcs = {
      [&splittedTroopName, &ok, this]() {
        this->yearEnteredOne->setValue(
          splittedTroopName.at(0).mid(3, 1).toInt(&ok));
      },
      [&splittedTroopName, &ok, this]() {
        this->numberOne->setValue(
          splittedTroopName.at(0).mid(5, 1).toInt(&ok));
      },
      [&splittedTroopName, &ok, this]() {
        if (this->addRemoveYearButton->text() == "-") {
          this->yearEnteredTwo->setValue(
            splittedTroopName.at(1).mid(3, 1).toInt(&ok));
        }
      }
     };
  for (auto func : funcs) {
    func();
    if (!ok) {
      qDebug() << "void TroopNameEditor::setTroopName(QString troopName)" <<
                  "invalid troop name, unsopported years" << troopName;
      return;
    }
  }
}

QString TroopNameEditor::troopName() {
  QString troopName = QString("%1-<N:%2>%3").arg(prefix->text())
      .arg(yearEnteredOne->value()).arg(numberOne->value());
  if (!yearEnteredTwo->isHidden()) {
    troopName += QString("/<N:%1>%2").arg(yearEnteredTwo->value())
        .arg(numberTwo->value());
  }
  return troopName;
}

void TroopNameEditor::toggleSecondPart() {
  if (addRemoveYearButton->text() != "+") {
    separator->hide();
    yearEnteredTwo->hide();
    numberTwo->hide();
    addRemoveYearButton->setText("+");
    this->setMinimumWidth(compactWidth);
    this->setMaximumWidth(compactWidth);
  } else {
    separator->show();
    yearEnteredTwo->show();
    numberTwo->show();
    addRemoveYearButton->setText("-");
    this->setMinimumWidth(fullWidth);
    this->setMaximumWidth(fullWidth);
  }
}
