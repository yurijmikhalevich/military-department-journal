#ifndef TEACHERSWIDGET_H
#define TEACHERSWIDGET_H

#include <QWidget>

namespace Ui {
class TeachersWidget;
}

class TeachersWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit TeachersWidget(QWidget *parent = 0);
    ~TeachersWidget();
    
private:
    Ui::TeachersWidget *ui;
};

#endif // TEACHERSWIDGET_H
