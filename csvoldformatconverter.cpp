#include "csvoldformatconverter.h"
#include <QSqlRecord>
#include <QDebug>
#include <QDate>
#include "database.h"

bool CSVOldFormatConverter::convertDatabase(QString csvDirPath,
                                            QString dbFilePath) {
  if (!Database::init(dbFilePath)) {
    return false;
  }
  for (auto func : {convertFaculties, fillMilitaryProfessions,
       convertTeachers, fillSubjects}) {
    if (!func(csvDirPath)) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertFaculties(QString csvDirPath) {
  QFile facultiesCsv(csvDirPath + QDir::separator() + "Факультет.csv");
  QTextStream facultiesStream;
  facultiesStream.setDevice(&facultiesCsv);
  facultiesStream.setCodec("UTF-8");
  if (!facultiesCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO university_faculty (name) VALUES (?)");
  while (!facultiesStream.atEnd()) {
    query.addBindValue(facultiesStream.readLine().split(';').at(1));
    if (!query.exec()) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::fillMilitaryProfessions(QString) {
  QSqlQuery query;
  if (!query.exec("INSERT INTO military_profession (archived, code, name)"
                  " VALUES (1, '261001', ''), (0, '261000', 'as'),"
                  " (0, '560100', 'qw')")) {
    return false;
  }
  return true;
}

bool CSVOldFormatConverter::convertTeachers(QString csvDirPath) {
  QFile teachersCsv(csvDirPath + QDir::separator() + "Преподаватели.csv");
  QTextStream teachersStream;
  teachersStream.setDevice(&teachersCsv);
  teachersStream.setCodec("UTF-8");
  if (!teachersCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO teacher (name) VALUES (?)");
  while (!teachersStream.atEnd()) {
    query.addBindValue(teachersStream.readLine().split(';').at(0));
    if (!query.exec()) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertTroops(QString csvDirPath) {
  QFile facultiesCsv(csvDirPath + QDir::separator() + "Факультет.csv");
  QTextStream facultiesStream;
  facultiesStream.setDevice(&facultiesCsv);
  facultiesStream.setCodec("UTF-8");
  if (!facultiesCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO university_faculty (name) VALUES (?)");
  while (!facultiesStream.atEnd()) {
    query.addBindValue(
          facultiesStream.readLine().split(';').at(1).simplified());
    if (!query.exec()) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertOldStudents(QString csvDirPath) {
  QFile studentsCsv(csvDirPath + QDir::separator() + "Студенты_выпуск.csv");
  QTextStream studentsStream;
  QSqlQuery query;
  studentsStream.setDevice(&studentsCsv);
  studentsStream.setCodec("UTF-8");
  if (!studentsCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  QString insertStudentQueryString = "INSERT INTO student"
      " (lastname, firstname, middlename,"
      "  lastname_datum, firstname_datum, middlename_datum,"
      "  lastname_accusative, firstname_accusative, middlename_accusative,"
      "  dob, university_group_id, decree_enrollment_number,"
      "  decree_expulsion_number, expulsion_reason_id,"
      "  expulsed_from_id)"
      " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
  while (!studentsStream.atEnd()) {
    query.addBindValue(studentsStream.readLine().split(';').at(1));
    if (!query.exec()) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertStudents(QString csvDirPath) {
  return true;
}


bool CSVOldFormatConverter::fillSubjects(QString) {
  QSqlQuery query;
  QString queryString = "INSERT INTO subject (name) VALUES (" + VAT + "), (" +
      UPVMV + "), (" + PDD + "), (" + TSP + "), (" + TP + "), (" + UAT +
      "), (" + EAT + "), (" + OGP + ")";
  if (!query.exec(queryString)) {
    return false;
  }
  return true;
}


int CSVOldFormatConverter::getGroupId(
    QString groupName,QString graduatedFromUniverisityInYear, QString troopName,
    QString graduatedFromMilitaryDepartmentDate, QString degreeEnrollmentNumber,
    QString graduatedFromMilitaryDepartmentInYear) {
  QHash<QString, QString> groupNamesPrefixSynonims =
      {
       {"ПИЭ", "ПИЭ"},
       {"ЮФ", "ЮФ"},
       {"ПИЮ", "ПИЮ"},
       {"СТ", "СТ"},
       {"АИ", "АИ"},
       {"ЭО", "ЭО"},
       {"ВХ", "ВХ"},
       {"ЗК", "ЗК"},
       {"ЗШ", "ЗШ"},
       {"ИЗ", "ИЗ"},
       {"РЗ", "РЗ"},
       {"ХП", "ХП"},
       {"ФЭ", "ФЭ"},
       {"ЭК", "ЭК"},
       {"ПВ", "ПВ"},
       {"МХ", "МХ"},
       {"ТХП", "ТХП"},
       {"АШ", "АШ"},
       {"АТ", "АТ"},
       {"ГУ", "ГУ"},
       {"ФК", "ФК"},
       {"УФ", "УФ"},
       {"НН", "НН"},
       {"ВВ", "ВВ"},
       {"ГМУ", "ГМУ"},
       {"ТПП", "ТПП"},
       {"СГ", "СГ"},
       {"Э", "Э"},
       {"ИСиТ", "ИТ"},
       {"ПЭ", "ПЭ"},
       {"ФЗМ", "ФЗМ"},
       {"Э0", "ЭО"},
       {"МЭ", "МЭ"},
       {"ЗМ", "ЗМ"},
       {"ИТ", "ИТ"},
       {"ПЮ", "ПЮ"},
       {"ПТ", "ПТ"},
       {"УП", "УП"},
       {"ВМ", "ВМ"},
       {"ВС", "ВС"},
       {"МО", "МО"},
       {"ПИ", "ПИ"},
       {"АХ", "АХ"},
       {"ПМ", "ПМ"}
      };
  QSqlQuery query;
  QString queryString = "SELECT id FROM university_group WHERE name = ?";
  QString groupNamePrefix, groupNameNumber;
  int separatorPosition;
  int facultyId;
  int troopId;
  QDate graduatedFromUniversityDate;
  groupName = groupName.toUpper().simplified();
  separatorPosition = groupName.indexOf('-');
  groupNamePrefix =
      groupNamesPrefixSynonims.value(groupName.left(separatorPosition));
  if (groupNamePrefix.isEmpty()) {
    qDebug() << groupName;
    throw;
  }
  groupNameNumber = groupName.mid(separatorPosition + 1);
  groupName = groupNamePrefix + "-" + groupNameNumber;
  if (groupNameNumber.length() != 4) {
    groupName += "(" + graduatedFromUniverisityInYear + ")";
  }
  query.prepare(queryString);
  query.addBindValue(groupName);
  if (!query.exec()) {
    return 0;
  }
  if (query.next()) {
    return query.record().value("id").toInt();
  }
  facultyId = getFacultyId(groupNamePrefix);
  troopId = getTroopId(
        troopName, graduatedFromMilitaryDepartmentDate, degreeEnrollmentNumber,
        graduatedFromMilitaryDepartmentInYear);
  if (!facultyId || !troopId) {
    return 0;
  }
  queryString = "INSERT INTO university_group (name,"
      " graduated_from_university_date, faculty_id, troop_id)"
      " VALUES (?, ?, ?, ?) RETURNING id";
  query.prepare(queryString);
  query.addBindValue(groupName);
  graduatedFromUniversityDate.setDate(
        graduatedFromUniverisityInYear.toInt(), 7, 1);
  query.addBindValue(graduatedFromUniversityDate);
  query.addBindValue(facultyId);
  query.addBindValue(troopId);
  if (!query.exec() || !query.next()) {
    return 0;
  }
  return query.record().value("id").toInt();
}


int CSVOldFormatConverter::getTroopId(
    QString troopName, QString graduatedFromMilitaryDepartmentDate,
    QString degreeEnrollmentNumber,
    QString graduatedFromMilitaryDepartmentInYear) {
  QString troopNamePrefix;
  QString troopNameNumber;
  QString troopNameStartYear;
  int separatorPosition;
  troopName = troopName.toUpper().simplified();
  if (troopName == "АШ32") {
    troopName = "АШ-32";
  } else if (troopName.isEmpty()) {
    qDebug() << graduatedFromMilitaryDepartmentDate << degreeEnrollmentNumber <<
                graduatedFromMilitaryDepartmentInYear;
    return 0;
  }
  separatorPosition = troopName.indexOf('-');
  troopNamePrefix = troopName.left(separatorPosition);
  troopNameNumber = troopName.mid(separatorPosition + 1);
}


int CSVOldFormatConverter::getFacultyId(QString groupNamePrefix) {
  QHash<QString, QString> groupPrefixToUniversityFacultyName =
      {
       {"ПИЭ", "Прикладной информатики"},
       {"ПИЮ", "Прикладной информатики"},
       {"ПИ", "Прикладной информатики"},
       {"ЮФ", "Юридический"},
       {"СТ", "Строительный"},
       {"АИ", "Агрохимии и почвоведения"},
       {"ЭО", "Экономический"},
       {"ВХ", "Водного хозяйства"},
       {"ЗК", "Земельного кадастра"},
       {"ЗШ", "Земельного кадастра"},
       {"ИЗ", "Инженерно-землеустроительный"},
       {"РЗ", "Защиты растений"},
       {"ХП", "Агрохимии и почвоведения"},
       {"ФЭ", "Электрификации"},
       {"ЭК", "Экономический"},
       {"ПВ", "Плодоовощеводства и вноградорства"},
       {"МХ", "Механизации"},
       {"ТХП", "Перерабатывающих технологий"},
       {"АШ", "Агрономический"},
       {"АТ", "Агротехнологический"},
       {"ГУ", "Управления"},
       {"ФК", "Финансы и кредит"},
       {"УФ", "Учётно-финансовый"},
       {"НН", "Налоги и налогооблажение"},
       {"ВВ", "Водного хозяйства"},
       {"ГМУ", "Управления"},
       {"ТПП", "Перерабатывающих технологий"},
       {"СГ", "Агрономический"},
       {"Э", "Экономический"},
       {"ИТ", "Прикладной информатики"},
       {"ФЗМ", "Зооинженерный"},
       {"МЭ", "Экономический"},
       {"ЗМ", "Земельного кадастра"},
       {"ПЮ", "Прикладной информатики"},
       {"ПЭ", "Прикладной информатики"},
       {"ПТ", "Перерабатывающих технологий"},
       {"УП", "Управления"},
       {"ВМ", "Ветеринарной медицины"},
       {"ВС", "Водного хозяйства"},
       {"МО", "Механизации"},
       {"АХ", "Агрохимии и почвоведения"},
       {"ПМ", "Механизации"},
       {"УВ", "Электрификации"}
      };
  QSqlQuery query;
  QString queryString("SELECT id FROM university_faculty WHERE name = ?");
  QString facultyName =
      groupPrefixToUniversityFacultyName.value(groupNamePrefix);
  if (facultyName.isEmpty()) {
    qDebug() << facultyName << groupNamePrefix;
    return 0;
  }
  query.prepare(queryString);
  query.addBindValue(facultyName);
  if (!query.exec() || !query.next()) {
    qDebug() << facultyName << groupNamePrefix;
    return 0;
  }
  return query.record().value("id").toInt();
}
