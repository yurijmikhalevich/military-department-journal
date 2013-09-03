#include "studentwidget.h"

#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QDebug>

StudentWidget::StudentWidget(QWidget *parent) :
    BaseWidget(parent)
{
}

StudentWidget::~StudentWidget()
{
}
