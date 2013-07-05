#ifndef TROOPSWIDGET_H
#define TROOPSWIDGET_H

#include <QWidget>

namespace Ui {
class TroopsWidget;
}

class TroopsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TroopsWidget(QWidget *parent = 0);
    ~TroopsWidget();
    
private:
    Ui::TroopsWidget *ui;
};

#endif // TROOPSWIDGET_H
