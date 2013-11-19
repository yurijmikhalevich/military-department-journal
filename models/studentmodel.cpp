#include "studentmodel.h"

StudentModel::StudentModel(QObject *parent) :
    SteroidsModel<QSqlRelationalTableModel>(parent)
{
    setTable("student");
    setJoinMode(QSqlRelationalTableModel::LeftJoin);
    setRelation(11, QSqlRelation("university_group", "id", "name"));
    setRelation(14, QSqlRelation("expulsion_reason", "id", "reason"));
    setRelation(15, QSqlRelation("expulsed_from", "id", "unit"));
    setRelation(16, QSqlRelation("troop", "id", "name"));
    setHeaderData(1, Qt::Horizontal, tr("Lastname"));
    setHeaderData(2, Qt::Horizontal, tr("Firstname"));
    setHeaderData(3, Qt::Horizontal, tr("Middlename"));
    setHeaderData(4, Qt::Horizontal, tr("Lastname datum"));
    setHeaderData(5, Qt::Horizontal, tr("Firstname datum"));
    setHeaderData(6, Qt::Horizontal, tr("Middlename datum"));
    setHeaderData(7, Qt::Horizontal, tr("Lastname accusative"));
    setHeaderData(8, Qt::Horizontal, tr("Firstname accusative"));
    setHeaderData(9, Qt::Horizontal, tr("Middlename accusative"));
    setHeaderData(10, Qt::Horizontal, tr("DOB"));
    setHeaderData(11, Qt::Horizontal, tr("Group"));
    setHeaderData(12, Qt::Horizontal, tr("Decree of enrollment"));
    setHeaderData(13, Qt::Horizontal, tr("Decree of expulsion"));
    setHeaderData(14, Qt::Horizontal, tr("Expulsion reason"));
    setHeaderData(15, Qt::Horizontal, tr("Expulsed from"));
    setHeaderData(16, Qt::Horizontal, tr("Troop"));
    select();
}

void StudentModel::queryChanged(QString query)
{
    if (query.isEmpty()) {
        filters.remove("query");
    } else {
        filters.insert("query", QString("university_group_id IN "
                                        "(SELECT id FROM university_group WHERE name LIKE '%%1%')").arg(query));
    }
    compileFilters();
}
