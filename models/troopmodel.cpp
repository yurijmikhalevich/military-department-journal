#include "troopmodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QTimer>
#include <QDate>
#include <QRegExp>
#include <QSqlError>

TroopModel::TroopModel(QObject *parent)
    : SteroidsModel<QSqlRelationalTableModel>(parent) {
  setTable("troop");
  setJoinMode(QSqlRelationalTableModel::LeftJoin);
  setRelation(4, QSqlRelation("teacher", "id", "name"));
  setRelation(5, QSqlRelation("military_profession", "id", "name"));
  setHeaderData(1, Qt::Horizontal, tr("Номер"));
  setHeaderData(2, Qt::Horizontal, tr("Дата поступления"));
  setHeaderData(3, Qt::Horizontal, tr("Дата выпуска"));
  setHeaderData(4, Qt::Horizontal, tr("Куратор"));
  setHeaderData(5, Qt::Horizontal, tr("Специальность"));
  setHeaderData(6, Qt::Horizontal, tr("Кол-во студентов"));
  showGraduated(false);
  select();
  troops = QSqlDatabase::addDatabase("QSQLITE", "troops");
  troops.setDatabaseName(":memory:");
  if (troops.open()) {
    fillTroops();
  }
  connect(parent, SIGNAL(recordInserted(int, QVariantMap)),
          this, SLOT(addRecord(int, QVariantMap)));
  connect(this, SIGNAL(dataChanged(QModelIndex, QModelIndex)),
          this, SLOT(onDataChanged(QModelIndex, QModelIndex)));
}

QVariant TroopModel::data(const QModelIndex &item, int role) const {
  if (item.column() == 6 && role == Qt::DisplayRole) {
    QSqlQuery query;
    query.prepare("SELECT ug.id AS id FROM university_group AS ug, troop AS t"
                  " WHERE ug.troop_id = t.id AND t.id = ?");
    query.addBindValue(this->record(item.row()).value("id"));
    if (!query.exec()) {
      return QVariant();
    }
    QStringList ids;
    while (query.next()) {
      ids.append(query.record().value("id").toString());
    }
    if (ids.isEmpty()) {
      return 0;
    }
    query.prepare(QString("SELECT COUNT(id) AS count FROM student"
                          " WHERE university_group_id IN (%1)").arg(
                    ids.join(", ")));
    if (query.exec() && query.next()) {
      return query.record().value("count");
    }
    return QVariant();
  } else if (item.column() == 1 && role == Qt::DisplayRole) {
    QSqlRecord row = this->record(item.row());
    QSqlQuery tQuery = QSqlQuery(troops);
    tQuery.prepare("SELECT name FROM troop WHERE id = ?");
    tQuery.addBindValue(row.value("id"));
    if (tQuery.exec() && tQuery.next()) {
      return tQuery.record().value("name");
    }
    return "#ОШИБКА";
  }
  return SteroidsModel<QSqlRelationalTableModel>::data(item, role);
}

Qt::ItemFlags TroopModel::flags(const QModelIndex &index) const {
  if (index.column() == 6) {
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return SteroidsModel<QSqlRelationalTableModel>::flags(index);
}

int TroopModel::columnCount(const QModelIndex &) const {
  return 7;
}

void TroopModel::showGraduated(bool show) {
  if (show) {
    filters.remove("graduated");
  } else {
    QDate date = QDate::currentDate();
    filters.insert("graduated",
                   "graduated_from_military_department_date > '" +
                   date.toString("yyyy-MM-dd") + "'");
  }
  compileFilters();
}

void TroopModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    query = query.simplified().toUpper();
    QSqlQuery tQuery = QSqlQuery(troops);
    tQuery.prepare(
          QString("SELECT id FROM troop WHERE name LIKE '%%1%'").arg(query));
    if (!tQuery.exec()) {
      throw tQuery.lastError();
    }
    QStringList ids;
    while (tQuery.next()) {
      ids.append(tQuery.record().value("id").toString());
    }
    QString filter = "entered_at_military_department_date LIKE '%%1%' OR"
        " graduated_from_military_department_date LIKE '%%1%'";
    if (!ids.isEmpty()) {
      filter += " OR troop.id IN (" + ids.join(", ") + ")";
    }
    filters.insert("query", QString("(" + filter + ")").arg(query));
  }
  compileFilters();
}

void TroopModel::onDataChanged(
    const QModelIndex &topLeft,const QModelIndex &bottomRight) {
  if (topLeft == bottomRight && topLeft.column() == 1) {
    QSqlQuery query;
    query.prepare("SELECT id, entered_at_military_department_date,"
                  " graduated_from_military_department_date FROM troop"
                  " WHERE id = ?");
    query.addBindValue(this->record(topLeft.row()).value("id"));
    if (!query.exec() || !query.next()) {
      if (query.lastError().isValid()) {
        qDebug() << query.lastError().text();
      }
      return;
    }
    QVariantMap record;
    record.insert("name", topLeft.data(Qt::EditRole));
    record.insert("entered_at_military_department_date",
                  query.record().value("entered_at_military_department_date"));
    record.insert("graduated_from_military_department_date",
                  query.record().value(
                    "graduated_from_military_department_date"));
    addRecord(query.record().value("id").toInt(), record);
  }
}

QString TroopModel::prepareName(QString troopName, QDate dateEntered,
                                QDate dateGraduated) {
  QString preparedName = "";
  QRegExp regexp("<N:[1-4]>");
  QStringList splittedName = troopName.split(regexp);
  QString addition = "";
  if (splittedName.length() == 1) {
    return troopName;
  }
  if (!dateGraduated.isValid() || dateGraduated > QDate::currentDate()) {
    dateGraduated = QDate::currentDate();
  } else {
    addition = " (" + QString::number(dateGraduated.year()) + ")";
  }
  int position = 0;
  int number;
  for (QString namePart : splittedName) {
    preparedName += namePart;
    position += namePart.length();
    if (position == troopName.length()) {
      break;
    }
    number = troopName.mid(position + 3, 1).toInt();
    number += dateGraduated.year() - dateEntered.year();
    if (dateGraduated.month() < 12) {
      number -= 1;
    }
    if (dateEntered.month() < 5) {
      number += 1;
    }
    preparedName += QString::number(number);
    position += 5;
  }
  preparedName += addition;
  return preparedName;
}

void TroopModel::fillTroops() {
  QSqlQuery query = QSqlQuery(troops);
  if (!query.exec("CREATE TABLE troop (id INTEGER PRIMARY KEY,"
                  " name TEXT NOT NULL)") ||
      !query.exec("CREATE INDEX troop_index ON troop (name)")) {
    throw query.lastError();
  }
  QSqlQuery defaultQuery;
  if (!defaultQuery.exec("SELECT id, name,"
                         " entered_at_military_department_date,"
                         " graduated_from_military_department_date"
                         " FROM troop")) {
    throw query.lastError();
  }
  query.prepare("INSERT INTO troop (id, name) VALUES (?, ?)");
  QSqlRecord row;
  while (defaultQuery.next()) {
    row = defaultQuery.record();
    addRecord(row.value("id").toInt(),
    {{"name", row.value("name")},
     {"entered_at_military_department_date",
      row.value("entered_at_military_department_date")},
     {"graduated_from_military_department_date",
      row.value("graduated_from_military_department_date")}});
  }
}

void TroopModel::addRecord(int id, QVariantMap record) {
  QSqlQuery query = QSqlQuery(troops);
  query.prepare("INSERT OR REPLACE INTO troop (id, name) VALUES (?, ?)");
  query.addBindValue(id);
  query.addBindValue(
        prepareName(
          record.value("name").toString(),
          record.value("entered_at_military_department_date").toDate(),
          record.value("graduated_from_military_department_date").toDate()));
  if (!query.exec()) {
    throw query.lastError();
  }
}
