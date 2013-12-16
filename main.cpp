#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setOrganizationName("39 software");
  QApplication::setOrganizationDomain("39.yt");
  QApplication::setApplicationName("Military Department Journal");
  QApplication::setApplicationVersion("0.0.1");
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
  MainWindow w;
  w.show();
  return a.exec();
}
