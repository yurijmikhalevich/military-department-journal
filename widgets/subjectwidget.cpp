#include "subjectwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QLabel>
#include "qt4table-steroids/booleancomboboxdelegate.h"
#include "qt4table-steroids/sqluniquesteroidsvalidator.h"
#include "qt4table-steroids/lineeditdelegate.h"
#include "qt4table-steroids/spinboxdelegate.h"
#include "models/subjectmodel.h"

SubjectWidget::SubjectWidget(QWidget *parent)
    : BaseWidget(parent),
      showArchivedCheckBox(
        new QCheckBox(tr("Показать отправленные в архив"), this)),
      addSubjectButton(new QPushButton(tr("Добавить предмет"), this)),
      containerLayout(new QHBoxLayout(this)),
      hoursEditorLayout(new QVBoxLayout()),
      hoursEditor(new QTableWidget(this)) {
  model = new SubjectModel(this);
  QVBoxLayout *mainLayout = new QVBoxLayout();
  view->setModel(model);
  connect(showArchivedCheckBox, SIGNAL(clicked(bool)),
          model, SLOT(showArchived(bool)));
  mainLayout->addWidget(showArchivedCheckBox);
  mainLayout->addWidget(view);
  view->setItemDelegateForColumn(1, new BooleanComboBoxDelegate(
                                   tr("В архиве"), tr("Действителен"), view));
  QHBoxLayout *controlsLayout = new QHBoxLayout();
  SQLUniqueSteroidsValidator *subjectNameValidator =
      new SQLUniqueSteroidsValidator("subject", "name", true, this);
  LineEditDelegate *subjectNameDelegate =
      new LineEditDelegate(subjectNameValidator, this);
  view->setItemDelegateForColumn(2, subjectNameDelegate);
  subjectNameEdit =
      static_cast<QLineEdit *>(subjectNameDelegate->createEditor(this));
  controlsLayout->addWidget(subjectNameEdit);
  controlsLayout->addWidget(addSubjectButton);
  connect(addSubjectButton, SIGNAL(clicked()), this, SLOT(addSubject()));
  mainLayout->addLayout(controlsLayout);
  view->setColumnWidth(1, 110);
  view->setColumnWidth(2, 300);
  connect(subjectNameEdit, SIGNAL(returnPressed()),
          addSubjectButton, SLOT(click()));
  addSubjectButton->setDisabled(true);
  connect(subjectNameEdit, SIGNAL(textChanged(QString)),
          this, SLOT(onSubjectNameEditChanged()));
  connect(view->selectionModel(),
          SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(onSubjectSelected(QModelIndex)));
  containerLayout->addLayout(mainLayout);
  hoursEditorLayout->addWidget(new QLabel(tr("Количество часов"), this));
  hoursEditor->setDisabled(true);
  hoursEditor->setMaximumWidth(300);
  hoursEditor->setColumnCount(3);
  hoursEditor->hideColumn(0);
  hoursEditor->setColumnWidth(1, 170);
  hoursEditor->setHorizontalHeaderItem(
        1, new QTableWidgetItem(tr("Специальность")));
  hoursEditor->setHorizontalHeaderItem(
        2, new QTableWidgetItem(tr("Кол-во часов")));
  hoursEditor->setSelectionBehavior(QAbstractItemView::SelectRows);
  SpinBoxDelegate *hoursEditorDelegate =
      new SpinBoxDelegate(0, 9999, 100, this);
  hoursEditor->setItemDelegateForColumn(2, hoursEditorDelegate);
  hoursEditorLayout->addWidget(hoursEditor);
  containerLayout->addLayout(hoursEditorLayout);
}

void SubjectWidget::addSubject() {
  QString name = subjectNameEdit->text().simplified();
  if (name.isEmpty()) {
    emit error("Название предмета не должно быть пустым");
    return;
  }
  int insertedId = insertRecord({{"name", name}});
  if (insertedId != -1) {
    subjectNameEdit->clear();
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT id FROM military_profession");
    if (!execQuery(
          selectQuery,
          tr("Критическая ошибка при заполнении длительности предметов"))) {
      return;
    }
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO subject_duration"
                        " (subject_id, military_profession_id, duration)"
                        " VALUES (?, ?, 0)");
    while (selectQuery.next()) {
      insertQuery.addBindValue(insertedId);
      insertQuery.addBindValue(selectQuery.record().value("id"));
      if (!execQuery(
            insertQuery,
            tr("Критическая ошибка при заполнении длительности предметов"))) {
        return;
      }
    }
  }
}

void SubjectWidget::onSubjectNameEditChanged() {
  QString name = subjectNameEdit->text().simplified();
  if (name.isEmpty()) {
    addSubjectButton->setDisabled(true);
  } else {
    addSubjectButton->setEnabled(true);
  }
}

void SubjectWidget::onSubjectSelected(QModelIndex selection) {
  disconnect(hoursEditor, SIGNAL(cellChanged(int, int)),
             this, SLOT(onSubjectDurationChanged(int)));
  hoursEditor->setEnabled(true);
  hoursEditor->setRowCount(0);
  currentSubjectId = model->record(selection.row()).value("id");
  QSqlQuery query;
  query.prepare("SELECT mp.id AS id, mp.name AS name, sd.duration AS duration"
                " FROM subject_duration AS sd, military_profession AS mp"
                " WHERE sd.subject_id = ?"
                " AND sd.military_profession_id = mp.id");
  query.addBindValue(currentSubjectId);
  if (!execQuery(query)) {
    return;
  }
  int curRow = 0;
  QSqlRecord record;
  QTableWidgetItem *item = nullptr;
  while (query.next()) {
    hoursEditor->insertRow(hoursEditor->rowCount());
    record = query.record();
    item = new QTableWidgetItem();
    item->setData(Qt::EditRole, record.value("id"));
    hoursEditor->setItem(curRow, 0, item);
    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, record.value("name"));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    hoursEditor->setItem(curRow, 1, item);
    item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole | Qt::EditRole, record.value("duration"));
    hoursEditor->setItem(curRow, 2, item);
    ++curRow;
  }
  connect(hoursEditor, SIGNAL(cellChanged(int, int)),
          this, SLOT(onSubjectDurationChanged(int)));
}

void SubjectWidget::onSubjectDurationChanged(int row) {
  QSqlQuery query;
  query.prepare("UPDATE subject_duration SET duration = ?"
                " WHERE subject_id = ? AND military_profession_id = ?");
  query.addBindValue(hoursEditor->item(row, 2)->data(Qt::EditRole));
  query.addBindValue(currentSubjectId);
  query.addBindValue(hoursEditor->item(row, 0)->data(Qt::EditRole));
  execQuery(query);
}
