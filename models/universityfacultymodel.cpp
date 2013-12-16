#include "universityfacultymodel.h"
#include <QStringList>
#include <QDebug>

UniversityFacultyModel::UniversityFacultyModel(QObject *parent)
    : SteroidsModel<QSqlTableModel>(parent) {
  this->setTable("university_faculty");
  this->setHeaderData(1, Qt::Horizontal, tr("Archived"));
  this->setHeaderData(2, Qt::Horizontal, tr("Name"));
  this->showArchived(false);
}

void UniversityFacultyModel::showArchived(bool show) {
  if (show) {
    filters.remove("archived");
  } else {
    filters.insert("archived", "archived = 0");
  }
  compileFilters();
}

void UniversityFacultyModel::queryChanged(QString query) {
  if (query.isEmpty()) {
    filters.remove("query");
  } else {
    QStringList splittedQuery = query.simplified().split(" ");
    QStringList filter;
    for (QString word : splittedQuery) {
      filter.append(
            QString("(name LIKE '% %1%'"
                    " OR name LIKE '%1%')").arg(
              word.at(0).toUpper() + word.mid(1)));
    }
    filters.insert("query", filter.join(" AND "));
  }
  compileFilters();
}
