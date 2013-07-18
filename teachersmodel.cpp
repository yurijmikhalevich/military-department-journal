#include "teachersmodel.h"

#include <QStringList>
#include <QDebug>

TeachersModel::TeachersModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("teacher");
    setHeaderData(1, Qt::Horizontal, tr("Name"));
    setHeaderData(2, Qt::Horizontal, tr("Dismissed"));
    showDismissed(false);
}

void TeachersModel::showDismissed(bool show)
{
    if (show) {
        filters.remove("dismissed");
    } else {
        filters.insert("dismissed", "dismissed = 0");
    }
    compileFilters();
}

void TeachersModel::queryChanged(QString query)
{
    if (query.isEmpty()) {
        filters.remove("query");
    } else {
        QStringList splittedQuery = query.simplified().split(" ");
        QStringList filter;
        for (QString word : splittedQuery) {
            filter.append(QString("(name LIKE '% %1%' OR name LIKE '%1%')").arg(word.at(0).toUpper() + word.mid(1)));
        }
        filters.insert("query", filter.join(" AND "));
    }
    compileFilters();
}
