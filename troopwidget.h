#ifndef TROOPWIDGET_H
#define TROOPWIDGET_H

#include <QWidget>

class TroopWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TroopWidget(QWidget *parent = 0);
    ~TroopWidget();
    void enable();
};

#endif // TROOPWIDGET_H
