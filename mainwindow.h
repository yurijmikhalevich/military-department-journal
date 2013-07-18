#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "studentswidget.h"
#include "troopswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_action_New_triggered();
    void on_action_Open_triggered();

private:
    Ui::MainWindow *ui;
    StudentsWidget *studentsWidget;
    TroopsWidget *troopsWidget;
};

#endif // MAINWINDOW_H
