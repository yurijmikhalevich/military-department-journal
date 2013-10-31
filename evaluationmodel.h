#ifndef EVALUATIONMODEL_H
#define EVALUATIONMODEL_H

#include <QSqlRelationalTableModel>

class EvaluationModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit EvaluationModel(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // EVALUATIONMODEL_H
