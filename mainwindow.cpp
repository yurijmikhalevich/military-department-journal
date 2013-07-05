#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "database.h"
#include "students/studentswidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    studentsWidget = new StudentsWidget(ui->tabWidget);
    connect(ui->globalSearch, SIGNAL(textChanged(QString)), studentsWidget, SLOT(globalSearchQueryChanged(QString)));
    ui->tabWidget->addTab(studentsWidget, tr("Students"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enter filename"), QDir::currentPath(),
                                                    tr("Journal (*.mdj)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile *file = new QFile(fileName);
    if (file->exists()) {
        file->remove();
    }
    qDebug() << Database::init(fileName, true);
    ui->centralWidget->setEnabled(true);
    studentsWidget->enable();
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Enter filename"), QDir::currentPath(),
                                                    tr("Journal (*.mdj)"));
    if (fileName.isEmpty()) {
        return;
    }
    qDebug() << Database::open(fileName);
    ui->centralWidget->setEnabled(true);
    studentsWidget->enable();
}
