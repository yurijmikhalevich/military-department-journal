#ifndef DOCUMENTGENERATOR_H
#define DOCUMENTGENERATOR_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QStringList>

class DocumentGenerator : public QObject {
  Q_OBJECT
public:
  static bool generateExamList(
      QString examListBlankPath, QString resultFilePath, QString semestr,
      QString academicYear, QString faculty, QString troop, QString grade,
      QString prof, QString subject, QString teacher, QDate date,
      QStringList students);
private:
  static const QStringList months;
  static const QString studentLine;
};

#endif // DOCUMENTGENERATOR_H
