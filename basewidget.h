#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>

class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = 0);

signals:
    void error(QString message);
    void queryChanged(QString query);
};

#endif // BASEWIDGET_H
