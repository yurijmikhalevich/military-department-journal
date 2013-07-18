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

signals:
    void queryChanged(QString query);
    
private:
    Ui::TeachersWidget *ui;

private slots:
    void addRow();
    void on_addTeacher_clicked();
};

#endif // TEACHERSWIDGET_H
