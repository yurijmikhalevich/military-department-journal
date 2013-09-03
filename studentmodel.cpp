#include "studentmodel.h"

StudentModel::StudentModel(QObject *parent) :
    SteroidsModel<QSqlRelationalTableModel>(parent)
{
    setTable("student");
    setJoinMode(QSqlRelationalTableModel::LeftJoin);
    setRelation(7, QSqlRelation("university_group", "id", "name"));
    setRelation(10, QSqlRelation("expulsion_reason", "id", "reason"));
    setRelation(11, QSqlRelation("expulsed_from", "id", "unit"));
    setRelation(15, QSqlRelation("troop", "id", "name"));
    setHeaderData(1, Qt::Horizontal, tr("Lastname"));
    setHeaderData(2, Qt::Horizontal, tr("Firstname"));
    setHeaderData(3, Qt::Horizontal, tr("Middlename"));
    setHeaderData(7, Qt::Horizontal, tr("Group"));
    setHeaderData(8, Qt::Horizontal, tr("Decree of enrollment"));
    setHeaderData(9, Qt::Horizontal, tr("Decree of expulsion"));
    setHeaderData(10, Qt::Horizontal, tr("Expulsion reason"));
    setHeaderData(11, Qt::Horizontal, tr("Expulsed from"));
    setHeaderData(12, Qt::Horizontal, tr("YGU", "Year of graduation from university"));
    setHeaderData(13, Qt::Horizontal, tr("YGM", "Year of graduation from Faculty of Military Training"));
    select();
}
