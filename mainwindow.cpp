#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QTabWidget>
#include <QSettings>
#include <QDebug>

#include "database.h"
#include "widgets/basewidget.h"
#include "widgets/universitygroupwidget.h"
#include "widgets/militaryprofessionwidget.h"
#include "widgets/teacherwidget.h"
#include "widgets/troopwidget.h"
#include "widgets/studentwidget.h"
#include "widgets/subjectwidget.h"
#include "widgets/evaluationwidget.h"
#include "widgets/universityfacultywidget.h"

//#include <QDate>
//#include "documentgenerator.h"
#include "csvoldformatconverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
  ui->setupUi(this);
  tabWidget = new QTabWidget(ui->centralWidget);
  connect(tabWidget, SIGNAL(currentChanged(int)),
          this, SLOT(onCurrentTabChanged(int)));
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

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::displayError(QString message) {
  ui->statusBar->showMessage(message, 2000);
}

void MainWindow::onCurrentTabChanged(int newTabIndex) {
  if (newTabIndex == -1) {
      return;
  }
  BaseWidget *widget =
      static_cast<BaseWidget *>(tabWidget->widget(newTabIndex));
  ui->globalSearch->disconnect();
  connect(ui->globalSearch, SIGNAL(textChanged(QString)),
          widget, SIGNAL(queryChanged(QString)));
}

void MainWindow::on_action_New_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
        this, tr("Введите имя файла журнала"), QDir::currentPath(),
        tr("Журнал (*.mdj)"));
  if (fileName.isEmpty()) {
    return;
  }
  if (!Database::init(fileName, true)) {
    displayError(tr("Невозможно инициализировать журнал"));
  } else {
    initControls();
  }
}

void MainWindow::on_action_Open_triggered() {
  QString fileName = QFileDialog::getOpenFileName(
        this, tr("Выберите файл журнала"), QDir::currentPath(),
        tr("Журнал (*.mdj)"));
  if (fileName.isEmpty()) {
    return;
  }
  if (!Database::open(fileName)) {
    displayError(tr("Невозможно открыть журнал"));
  } else {
    initControls();
  }
}

void MainWindow::initControls() {
  while (tabWidget->count()) {
    delete tabWidget->widget(0);
    tabWidget->removeTab(0);
  }
  TroopWidget *troopWidget = new TroopWidget(tabWidget);
  // it is needed to created troopWidget before UniversityGroupWidget
  ui->centralWidget->setEnabled(true);
  ui->emblem->hide();
  tabWidget->tabBar()->setExpanding(false);
  tabWidget->tabBar()->setUsesScrollButtons(true);
  tabWidget->addTab(new StudentWidget(tabWidget), tr("Студенты"));
  tabWidget->addTab(new EvaluationWidget(tabWidget),
                    tr("Проверочные испытания"));
  tabWidget->addTab(new SubjectWidget(tabWidget), tr("Предметы"));
  tabWidget->addTab(new UniversityGroupWidget(tabWidget), tr("Группы"));
  tabWidget->addTab(troopWidget, tr("Взвода"));
  tabWidget->addTab(new TeacherWidget(tabWidget), tr("Преподаватели"));
  tabWidget->addTab(new UniversityFacultyWidget(tabWidget), tr("Факультеты"));
  tabWidget->addTab(new MilitaryProfessionWidget(tabWidget),
                    tr("Специальности"));
  for (int i = 0; i < tabWidget->count(); ++i) {
    connect(static_cast<BaseWidget *>(tabWidget->widget(i)),
            SIGNAL(error(QString)), this, SLOT(displayError(QString)));
  }
  tabWidget->show();
}

void MainWindow::on_action_Import_triggered() {
  QString dirPath = QFileDialog::getExistingDirectory(
        this, tr("Выберите директорию, содержащую журнал в старом формате"),
        QDir::currentPath());
  if (dirPath.isEmpty()) {
    return;
  }
  QString fileName = QFileDialog::getSaveFileName(
        this, tr("Введите имя файла журнала"), QDir::currentPath(),
        tr("Журнал (*.mdj)"));
  if (fileName.isEmpty()) {
    return;
  }
  if (!CSVOldFormatConverter::convertDatabase(dirPath, fileName)) {
    displayError(tr("Произошла ошибка при импорте журнала"));
  } else {
    initControls();
  }
}
