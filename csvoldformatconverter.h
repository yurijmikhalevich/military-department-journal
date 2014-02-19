#ifndef CSVOLDFORMATCONVERTER_H
#define CSVOLDFORMATCONVERTER_H

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
const QString VAT = "Восстановление автомобильной техники";
const QString UPVMV = "Управление подразделениями в мирное время";
const QString PDD = "Правила дорожного движения";
const QString TSP = "Тактико-специальная подготовка";
const QString TP = "Тактическая подготовка";
const QString UAT = "Устройство автомобильной техники";
const QString EAT = "Эксплуатация автомобильной техники";
const QString OGP = "Общегосударственная подготовка";
}

#endif // CSVOLDFORMATCONVERTER_H
