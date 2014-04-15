#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:
  void displayError(QString message);
  void onCurrentTabChanged(int newTabIndex);
  void on_action_New_triggered();
  void on_action_Open_triggered();

  void on_action_Import_triggered();

private:
  Ui::MainWindow *ui;
  QTabWidget *tabWidget;
  void initControls();
};

#endif // MAINWINDOW_H
