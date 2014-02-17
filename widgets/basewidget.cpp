#include "basewidget.h"

#include <QSqlDriver>

QSqlQuery *BaseWidget::query = 0;

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent) {
  view = new SteroidsView(this);
  if (!query) {
    // initialize our common QSqlQuery object, if it not yet initialized
    query = new QSqlQuery();
  }
}

BaseWidget::~BaseWidget() {
  if (query) {
    delete query;
    query = 0;
  }
}

bool BaseWidget::insertRecord(const QVariantMap record) {
  if (!record.size()) {
    emit error(tr("There is should be at least one field in inserted record"));
    return false;
  }
  QString tableName = model->tableName();
  QString columnNames;
  QString placeholdersPlace;
  for (QString key : record.keys()) {
    if (columnNames.isEmpty()) { // && placeholdersPlace.isEmpty()
      columnNames = "(" + key;
      placeholdersPlace = "(?";
    } else {
      columnNames += ", " + key;
      placeholdersPlace += ", ?";
    }
  }
  columnNames += ")";
  placeholdersPlace += ")";
  if (!query->prepare(QString("INSERT INTO %1 %2 VALUES %3").arg(
                        tableName, columnNames, placeholdersPlace))) {
    emit error(query->lastError().text());
    return false;
  }
  for (QVariant value : record.values()) {
    query->addBindValue(value);
  }
  if (!query->exec()) {
    emit error(query->lastError().text());
    return false;
  } else {
    model->select();
    return true;
  }
}
