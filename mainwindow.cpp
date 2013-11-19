#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QTabWidget>
#include <QSettings>

#include "database.h"
#include "widgets/basewidget.h"
#include "widgets/universitygroupwidget.h"
#include "widgets/militaryprofessionwidget.h"
#include "widgets/teacherwidget.h"
#include "widgets/troopwidget.h"
#include "widgets/studentwidget.h"
#include "widgets/subjectwidget.h"
#include "widgets/evaluationwidget.h"

//#include <QDate>
//#include "documentgenerator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tabWidget = new QTabWidget(ui->centralWidget);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onCurrentTabChanged(int)));
    tabWidget->hide();
    ui->centralWidget->layout()->addWidget(tabWidget);
//    DocumentGenerator::generateExamList("/home/39/stuff/vboxshare/vedomost.docx",
//                                        "/home/39/stuff/vboxshare/vedomost_patched.docx", "II", "2012/2013",
//                                        "Механизации", "МХ-41", "4", "560100",
//                                        "Управление подразделениями в мирное время", "п-п/к запаса Стешенко А.Ф.",
//                                        QDate::currentDate(),
//    { "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович", "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович",
//                                        "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович", "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович",
//                                        "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович", "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович",
//                                        "Василий Пупкин", "Иван Михайлович", "Ефистафий Арнольдович", "Вау вауфович" });
//    QSettings settings(QApplication::applicationDirPath() + QDir::separator() + "settings.ini", QSettings::IniFormat);
//    if (settings.contains("base")) {
//        if (!Database::open(settings.value("base").toString())) {
//            displayError(tr("Cannot open database"));
//        } else {
//            initControls();
//        }
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayError(QString message)
{
    ui->statusBar->showMessage(message, 2000);
}

void MainWindow::onCurrentTabChanged(int newTabIndex)
{
    if (newTabIndex == -1) {
        return;
    }
    BaseWidget *widget = static_cast<BaseWidget *>(tabWidget->widget(newTabIndex));
    ui->globalSearch->disconnect();
    connect(ui->globalSearch, SIGNAL(textChanged(QString)), widget, SIGNAL(queryChanged(QString)));
}

void MainWindow::on_action_New_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enter filename"), QDir::currentPath(),
                                                    tr("Journal (*.mdj)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (file.exists()) {
        file.remove();
    }
    if (!Database::init(fileName, true)) {
        displayError(tr("Cannot init database"));
    } else {
        initControls();
    }
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Enter filename"), QDir::currentPath(),
                                                    tr("Journal (*.mdj)"));
    if (fileName.isEmpty()) {
        return;
    }
    if (!Database::open(fileName)) {
        displayError(tr("Cannot open database"));
    } else {
        initControls();
    }
}

void MainWindow::initControls()
{
    ui->centralWidget->setEnabled(true);
    ui->emblem->hide();
    tabWidget->addTab(new EvaluationWidget(tabWidget), tr("Evaluation"));
    tabWidget->addTab(new StudentWidget(tabWidget), tr("Students"));
    tabWidget->addTab(new TroopWidget(tabWidget), tr("Troops"));
    tabWidget->addTab(new TeacherWidget(tabWidget), tr("Teachers"));
    tabWidget->addTab(new UniversityGroupWidget(tabWidget), tr("University Groups"));
    tabWidget->addTab(new MilitaryProfessionWidget(tabWidget), tr("Military Professions"));
    tabWidget->addTab(new SubjectWidget(tabWidget), tr("Subjects"));
//    for (int i = 0; i < tabWidget->count(); ++i) {
//        connect(static_cast<BaseWidget *>(tabWidget->widget(i)), SIGNAL(error(QString)),
//                this, SLOT(displayError(QString)));
//    }
    tabWidget->show();
}
