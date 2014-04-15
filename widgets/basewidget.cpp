#include "basewidget.h"

#include <QSqlDriver>
#include <QDebug>

QSqlQuery *BaseWidget::query = 0;

BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent) {
  view = new SteroidsView(this);
  view->setSelectionBehavior(QAbstractItemView::SelectRows);
  view->setSelectionMode(QAbstractItemView::SingleSelection);
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

int BaseWidget::insertRecord(const QVariantMap record) {
  if (!record.size()) {
    emit error(tr("Новая запись должна содержать хотя бы одно поле"));
    return -1;
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
    if (query->lastError().isValid()) {
      qCritical() << query->lastError().text();
      emit error(query->lastError().text());
    }
    return -1;
  }
  for (QVariant value : record.values()) {
    query->addBindValue(value);
  }
  if (!execQuery(*query)) {
    return -1;
  } else {
    int insertedId = query->lastInsertId().toInt();
    emit recordInserted(insertedId, record);
    model->select();
    return insertedId;
  }
}

bool BaseWidget::execQuery(QSqlQuery &query, QString errorMessage) {
  if (!query.exec()) {
    if (query.lastError().isValid()) {
      qCritical() << query.lastError().text();
      emit error(query.lastError().text());
    }
    if (!errorMessage.isEmpty()) {
      emit error(errorMessage);
    }
    return false;
  }
  return true;
}

bool BaseWidget::execAndNextQuery(QSqlQuery &query, QString errorMessage) {
  if (!query.exec() || !query.next()) {
    if (query.lastError().isValid()) {
      qCritical() << query.lastError().text();
      emit error(query.lastError().text());
    }
    if (!errorMessage.isEmpty()) {
      emit error(errorMessage);
    }
    return false;
  }
  return true;
}
