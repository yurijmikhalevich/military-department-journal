#ifndef STUDENTSWIDGET_H
#define STUDENTSWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QSqlRelationalTableModel>

namespace Ui {
class StudentsWidget;
}

class StudentsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StudentsWidget(QWidget *parent = 0);
    ~StudentsWidget();

public slots:
    void enable();
    void globalSearchQueryChanged(QString query);
    
private slots:
    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::StudentsWidget *ui;
    QSqlRelationalTableModel *model;
};

#endif // STUDENTSWIDGET_H
