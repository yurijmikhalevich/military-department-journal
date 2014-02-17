#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

//#include "csvoldformatconverter.h"
//#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setOrganizationName("39 software");
  QApplication::setOrganizationDomain("39.yt");
  QApplication::setApplicationName("Military Department Journal");
  QApplication::setApplicationVersion("0.0.1");
  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//  qDebug() << CSVOldFormatConverter::convertDatabase(
//                "/Users/y/Downloads/stuff/vboxshare/war-database-csv",
//                "/Users/y/mdj-converted.mdj");
  MainWindow w;
  w.show();
  return a.exec();
  return 0;
}
