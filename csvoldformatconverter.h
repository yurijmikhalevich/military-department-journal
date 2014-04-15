#ifndef CSVOLDFORMATCONVERTER_H
#define CSVOLDFORMATCONVERTER_H

#include <QString>
#include <QSqlDatabase>
#include <QFile>
#include <QDir>
#include <QSqlQuery>
#include <QTextStream>

/**
 * CSVOldFormatConverter - fucking shame, there is much to be optimized and
 * rewritten, but, as you will need convertion procedure to be executed only
 * once (to convert the old database to the new!), it was strongly decided not
 * to waste time on this code and it has been left. Read careful.
 * CSVOldFormatConverter — ёбаный стыд, по хорошему, тут многое надо
 * оптимизировать и переписать, но, так как процедура конвертирования
 * понадобится только один раз (для конвертации старой БД в новую!), было
 * принято волевое решение не тратить время на этот код и он был оставлен так,
 * как оставлен. Читай дальше осторожно.
 */
namespace CSVOldFormatConverter {
bool convertDatabase(QString csvDirPath, QString dbFilePath);
bool convertFaculties(QString csvDirPath);
bool fillMilitaryProfessions(QString);
bool convertTeachers(QString csvDirPath);
bool convertTroops(QString csvDirPath);
bool convertOldStudents(QString csvDirPath);
bool convertNewStudents(QString csvDirPath);
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
