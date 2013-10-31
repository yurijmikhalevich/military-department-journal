#include "evaluationmodel.h"

EvaluationModel::EvaluationModel(QObject *parent) :
    SteroidsModel<QSqlRelationalTableModel>(parent)
{
    setTable("evaluation");
    setJoinMode(QSqlRelationalTableModel::LeftJoin);
    setRelation(1, QSqlRelation("subject", "id", "name"));
    setRelation(2, QSqlRelation("control_type", "id", "name"));
    setRelation(3, QSqlRelation("teacher", "id", "name"));
    setRelation(4, QSqlRelation("troop", "id", "name"));
    setHeaderData(2, Qt::Horizontal, tr("Control type"));
    setHeaderData(3, Qt::Horizontal, tr("Teacher"));
//    setHeaderData(3, Qt::Horizontal, tr("Archived"));
    select();
}
