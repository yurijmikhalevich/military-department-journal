#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include "qt4table-steroids/steroidsview.h"

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);
protected:
    QSqlTableModel *model;
    SteroidsView *view;
signals:
    void error(QString message);
    void queryChanged(QString query);
};

#endif // BASEWIDGET_H
