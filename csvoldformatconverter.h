#ifndef CSVOLDFORMATCONVERTER_H
#define CSVOLDFORMATCONVERTER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>
#include <QSqlQuery>
#include <QTextStream>

namespace CSVOldFormatConverter {
bool convertDatabase(QString csvDirPath, QString dbFilePath);
bool convertFaculties(QString csvDirPath);
bool fillMilitaryProfessions(QString);
bool convertTeachers(QString csvDirPath);
bool convertTroops(QString csvDirPath);
bool convertOldStudents(QString csvDirPath);
bool convertStudents(QString csvDirPath);
bool fillSubjects(QString);
int getGroupId(QString groupName, QString graduatedFromUniverisityInYear,
               QString troopName, QString graduatedFromMilitaryDepartmentDate,
               QString degreeEnrollmentNumber,
               QString graduatedFromMilitaryDepartmentInYear);
int getTroopId(QString troopName, QString graduatedFromMilitaryDepartmentDate,
               QString degreeEnrollmentNumber,
               QString graduatedFromMilitaryDepartmentInYear);
int getFacultyId(QString groupNamePrefix);
QString VAT = "Восстановление автомобильной техники";
QString UPVMV = "Управление подразделениями в мирное время";
QString PDD = "Правила дорожного движения";
QString TSP = "Тактико-специальная подготовка";
QString TP = "Тактическая подготовка";
QString UAT = "Устройство автомобильной техники";
QString EAT = "Эксплуатация автомобильной техники";
QString OGP = "Общегосударственная подготовка";
}

#endif // CSVOLDFORMATCONVERTER_H
