#include "universitygroupmodel.h"

#include <QSqlQuery>
#include <QSqlRecord>

UniversityGroupModel::UniversityGroupModel(QObject *parent) :
    SteroidsModel<QSqlTableModel>(parent)
{
    setTable("university_group");
    setHeaderData(1, Qt::Horizontal, tr("Name"));
    setHeaderData(2, Qt::Horizontal, tr("Graduated from in"));
    setHeaderData(3, Qt::Horizontal, tr("Number of students"));
}

QVariant UniversityGroupModel::data(const QModelIndex &item, int role) const
{
    if (item.column() == 3 && role == Qt::DisplayRole) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) AS count FROM student WHERE university_group_id = ?");
        query.addBindValue(this->record(item.row()).value("id"));
        if (query.exec() && query.next()) {
            return query.record().value("count");
        }
        return QVariant();
    }
    return SteroidsModel<QSqlTableModel>::data(item, role);
}

Qt::ItemFlags UniversityGroupModel::flags(const QModelIndex &index) const
{
    if (index.column() == 3) {
        return Qt::ItemIsEnabled;
    }
    return SteroidsModel<QSqlTableModel>::flags(index);
}

int UniversityGroupModel::columnCount(const QModelIndex &) const
{
    return 4;
}

void UniversityGroupModel::queryChanged(QString query)
{
    if (query.isEmpty()) {
        filters.remove("query");
    } else {
        filters.insert("query", QString("name = '%1'").arg(query));
    }
    compileFilters();
}
