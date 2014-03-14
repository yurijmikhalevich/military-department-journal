#include "csvoldformatconverter.h"
#include <QSqlRecord>
#include <QDebug>
#include <QDate>
#include <QSqlError>
#include <QRegExp>
#include "database.h"
#include "namemorpher.h"

static inline bool execQuery(QSqlQuery &query) {
  if (!query.exec()) {
    if (query.lastError().isValid()) {
      qDebug() << "last SQL error" << query.lastError().text();
    }
    return false;
  }
  return true;
}

static bool execAndNextQuery(QSqlQuery &query) {
  if (!query.exec() || !query.next()) {
    if (query.lastError().isValid()) {
      qDebug() << "last SQL error" << query.lastError().text();
    }
    return false;
  }
  return true;
}

bool CSVOldFormatConverter::convertDatabase(QString csvDirPath,
                                            QString dbFilePath) {
  if (!Database::init(dbFilePath)) {
    return false;
  }
  for (auto func : {convertFaculties, fillMilitaryProfessions,
       convertTeachers, fillSubjects, convertOldStudents, convertNewStudents}) {
    if (!func(csvDirPath)) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertFaculties(QString csvDirPath) {
  QFile facultiesCsv(csvDirPath + "/Факультет.csv");
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
  QFile teachersCsv(csvDirPath + "/Преподаватели.csv");
  QTextStream teachersStream;
  teachersStream.setDevice(&teachersCsv);
  teachersStream.setCodec("UTF-8");
  if (!teachersCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  QSqlQuery query;
  query.prepare("INSERT INTO teacher (name) VALUES (?)");
  while (!teachersStream.atEnd()) {
    query.addBindValue(teachersStream.readLine().split(';').at(0).simplified());
    if (!query.exec()) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertTroops(QString csvDirPath) {
  QFile facultiesCsv(csvDirPath + "/Факультет.csv");
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

static bool fillMarks(QStringList splittedStudent, int studentId, int groupId,
                      int offset = 0);

/*
0|Код|INTEGER|1||1
1|выпуск|TEXT|0||0
2|Фамилия|TEXT|1||0
3|Имя|TEXT|1||0
4|Отчество|TEXT|1||0
5|гр_уни|TEXT|0||0
6|пр_зач|TEXT|0||0
7|пр_отч|TEXT|0||0
8|пр_отч_прич|TEXT|0||0
9|пр_отч_с|TEXT|0||0
10|ГОУ|INTEGER|0||0
11|ГОК|INTEGER|0||0
12|вз|TEXT|0||0
13|флаг|INTEGER|0||0

14|Такт_подготовка_атт1|TEXT|0||0
15|Такт_подготовка_атт2|TEXT|0||0
16|Такт_подготовка_зач|TEXT|0||0
17|Такт_подготовка_вп|TEXT|0||0
18|Такт_подготовка_д|TEXT|0||0
19|Такт_подготовка_пер|INTEGER|0||0
20|Такт_подготовка_дат|TEXT|0||0
21|Такт_подготовка_преп|TEXT|0||0

22|Общгос_подготовка_атт1|TEXT|0||0
23|Общгос_подготовка_атт2|TEXT|0||0
24|Общгос_подготовка_зач|TEXT|0||0
25|Общгос_подготовка_вп|TEXT|0||0
26|Общгос_подготовка_д|TEXT|0||0
27|Общгос_подготовка_пер|INTEGER|0||0
28|Общгос_подготовка_дат|TEXT|0||0
29|Общгос_подготовка_преп|TEXT|0||0

30|Тактспец_подготовка_атт1|TEXT|0||0
31|Тактспец_подготовка_атт2|TEXT|0||0
32|Тактспец_подготовка_зачэкз|TEXT|0||0
33|Тактспец_подготовка_вп|TEXT|0||0
34|Тактспец_подготовка_д|TEXT|0||0
35|Тактспец_подготовка_пер|INTEGER|0||0
36|Тактспец_подготовка_дат|TEXT|0||0
37|Тактспец_подготовка_преп|TEXT|0||0

38|Устройство_АТ_атт1|TEXT|0||0
39|Устройство_АТ_атт2|TEXT|0||0
40|Устройство_АТ_зач|TEXT|0||0
41|Устройство_АТ_вп|TEXT|0||0
42|Устройство_АТ_д|TEXT|0||0
43|Устройство_АТ_пер|INTEGER|0||0
44|Устройство_АТ_дат|TEXT|0||0
45|Устройство_АТ_преп|TEXT|0||0

46|Эксплуатац_АТ_атт1|TEXT|0||0
47|Эксплуатац_АТ_атт2|TEXT|0||0
48|Эксплуатац_АТ_экз|TEXT|0||0
49|Эксплуатац_АТ_вп|TEXT|0||0
50|Эксплуатац_АТ_д|TEXT|0||0
51|Эксплуатац_АТ_пер|INTEGER|0||0
52|Эксплуатац_АТ_дат|TEXT|0||0
53|Эксплуатац_АТ_преп|TEXT|0||0

54|Восстановление_АТ_атт1|TEXT|0||0
55|Восстановление_АТ_атт2|TEXT|0||0
56|Восстановление_АТ_зачэкз|TEXT|0||0
57|Восстановление_АТ_вп|TEXT|0||0
58|Восстановление_АТ_д|TEXT|0||0
59|Восстановление_АТ_пер|INTEGER|0||0
60|Восстановление_АТ_дат|TEXT|0||0
61|Восстановление_АТ_преп|TEXT|0||0

62|ПДД_атт1|TEXT|0||0
63|ПДД_атт2|TEXT|0||0
64|ПДД_зач|TEXT|0||0
65|ПДД_вп|TEXT|0||0
66|ПДД_д|TEXT|0||0
67|ПДД_пер|INTEGER|0||0
68|ПДД_дат|TEXT|0||0
69|ПДД_преп|TEXT|0||0
*/

static bool convertStudents(QString csvFilePath, int offset = 0) {
  QFile studentsCsv(csvFilePath);
  QTextStream studentsStream;
  QString insertStudentQueryString;
  QSqlQuery query;
  QString student;
  QStringList splittedStudent;
  NameMorpher nameMorpher;
  NameMorpher::MorphedName morphedName;
  studentsStream.setDevice(&studentsCsv);
  studentsStream.setCodec("UTF-8");
  if (!studentsCsv.open(QIODevice::ReadOnly)) {
    return false;
  }
  insertStudentQueryString = "INSERT INTO student"
      " (lastname, firstname, middlename,"
      "  lastname_datum, firstname_datum, middlename_datum,"
      "  lastname_accusative, firstname_accusative, middlename_accusative,"
      "  dob, university_group_id, decree_enrollment_number,"
      "  decree_expulsion_number, expulsion_reason_id,"
      "  expulsed_from_id)"
      " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
  query.prepare(insertStudentQueryString);
  while (!studentsStream.atEnd()) {
    student = studentsStream.readLine()
        .replace("не сданы зачеты ТП, УАТ; 17 пропусков занятий",
                 "не сданы зачеты ТП, УАТ. 17 пропусков занятий")
        .replace("не сдан зачет по УАТ; 45 пропусков занятий",
                 "не сдан зачет по УАТ. 45 пропусков занятий")
        .replace("Не сдал зачеты по УАТ, ТП; пропустил 102 ч занятий",
                 "Не сдал зачеты по УАТ, ТП. пропустил 102 ч занятий")
        .replace("Не сдал зачеты УАТ, ТП; пропустил 52 ч занятий",
                 "Не сдал зачеты УАТ, ТП. пропустил 52 ч занятий")
        .replace("Не сдал зачеты ТП, УАТ; пропущено 96 ч. Занятий",
                 "Не сдал зачеты ТП, УАТ. пропущено 96 ч. Занятий")
        .replace("Не сдал зачеты УАТ,ТП; пропустил 98 часов занятий",
                 "Не сдал зачеты УАТ,ТП. пропустил 98 часов занятий");
    if (student.isEmpty()) {
      continue;
    }
    splittedStudent = student.split(';');
    query.addBindValue(splittedStudent.at(offset + 2));
    query.addBindValue(splittedStudent.at(offset + 3));
    query.addBindValue(splittedStudent.at(offset + 4));
    morphedName = nameMorpher.getMorphedName(
          splittedStudent.at(offset + 2), splittedStudent.at(offset + 3),
          splittedStudent.at(offset + 4),
          true); // TODO: remove "true" in production
    query.addBindValue(morphedName.lastnameDatum);
    query.addBindValue(morphedName.firstnameDatum);
    query.addBindValue(morphedName.middlenameDatum);
    query.addBindValue(morphedName.lastnameAccusative);
    query.addBindValue(morphedName.firstnameAccusative);
    query.addBindValue(morphedName.middlenameAccusative);
    query.addBindValue(QVariant());
    if (splittedStudent.at(offset + 12) == "2007") {
      qDebug() << "WOWOWOW, I'VE CATCHED HIM!";
      return false;
    }
    int groupId = CSVOldFormatConverter::getGroupId(
          splittedStudent.at(offset + 5), splittedStudent.at(offset + 10),
          splittedStudent.at(offset + 12),
          offset == 0 ? splittedStudent.at(1) : QString(),
          splittedStudent.at(offset + 6), splittedStudent.at(offset + 11));
    query.addBindValue(groupId);
    query.addBindValue(splittedStudent.at(offset + 6));
    query.addBindValue(QVariant());
    query.addBindValue(QVariant());
    query.addBindValue(QVariant());
    if (!query.exec()) {
      qDebug() << query.lastError().text();
      return false;
    }
    int studentId = query.lastInsertId().toInt();
    if (!fillMarks(splittedStudent, studentId, groupId, offset)) {
      return false;
    }
  }
  return true;
}

bool CSVOldFormatConverter::convertOldStudents(QString csvDirPath) {
  return convertStudents(csvDirPath + "/Студент_выпуск.csv");
}

bool CSVOldFormatConverter::convertNewStudents(QString csvDirPath) {
  return convertStudents(csvDirPath + "/Студент.csv", -1);
}

static bool fillSubject(QStringList splittedStudent, int studentId, int groupId,
                        int offset, QString subject);

static bool fillMarks(QStringList splittedStudent, int studentId, int groupId,
                      int offset) {
//  qDebug() << "filling student" << studentId;
  bool ok = true;
  ok = fillSubject(splittedStudent, studentId, groupId, offset + 14,
                   "Тактическая подготовка");
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 22,
                     "Общегосударственная подготовка");
  }
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 30,
                     "Тактико-специальная подготовка");
  }
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 38,
                     "Устройство автомобильной техники");
  }
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 46,
                     "Эксплуатация автомобильной техники");
  }
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 54,
                     "Восстановление автомобильной техники");
  }
  if (ok) {
    ok = fillSubject(splittedStudent, studentId, groupId, offset + 62,
                     "Правила дорожного движения");
  }
  return ok;
}

//14|Такт_подготовка_атт1|TEXT|0||0 + 0
//15|Такт_подготовка_атт2|TEXT|0||0 + 1
//16|Такт_подготовка_зач|TEXT|0||0 + 2
//17|Такт_подготовка_вп|TEXT|0||0 + 3
//18|Такт_подготовка_д|TEXT|0||0 + 4
//19|Такт_подготовка_пер|INTEGER|0||0 + 5
//20|Такт_подготовка_дат|TEXT|0||0 + 6
//21|Такт_подготовка_преп|TEXT|0||0 + 7

static int getEvaluationId(QString subject, QString controlType,
                           QString teacher, int groupId,
                           QString date);

static bool fillMark(int evaluationId, int studentId, int value,
                     int teacherId, QString date);

static int getMark(QString mark, QString studentId = "unknown student") {
  if (mark == "Отлично") {
    return 5;
  } else if (mark == "Хорошо") {
    return 4;
  } else if (mark == "Удовлетворительно") {
    return 3;
  } else if (mark == "Неудовлетворительно") {
    return 2;
  } else if (mark == "Зачтено" || mark == "Аттестован") {
    return 1;
  } else if (mark == "Не зачтено") {
    return 0;
  } else if (mark == "Не явился") {
    return -1;
  } else if (mark == "Не допущен") {
    return -2;
  } else {
    qDebug() << "unknown mark" << mark;
    qDebug() << "student" << studentId;
    return -3;
  }
}

static bool fillSubject(QStringList splittedStudent, int studentId, int groupId,
                        int offset, QString subject) {
  bool ok = true;
  if (!splittedStudent.at(offset).simplified().isEmpty()) {
    // fill first attestation
    int evaluationId = getEvaluationId(subject, "Аттестация", QString(),
                                       groupId, QString());
    ok = fillMark(evaluationId, studentId,
                  getMark(splittedStudent.at(offset).simplified(),
                          splittedStudent.at(0) + "FA"),
                  0, QString());
  }
  if (ok && !splittedStudent.at(offset + 1).simplified().isEmpty()) {
    // fill second attestation
    // custom date to differ it from first attestation
    int evaluationId = getEvaluationId(subject, "Аттестация", QString(),
                                       groupId, "02.01.1970");
    ok = fillMark(evaluationId, studentId,
                  getMark(splittedStudent.at(offset + 1).simplified(),
                          splittedStudent.at(0) + "SA"),
                  0, QString());
  }
  if (ok && !splittedStudent.at(offset + 2).simplified().isEmpty()) {
    // fill exam
    // or main attestation
    int evaluationId = getEvaluationId(subject, "Экзамен",
                                       splittedStudent.at(offset + 3),
                                       groupId, splittedStudent.at(offset + 4));
    ok = fillMark(evaluationId, studentId,
                  getMark(splittedStudent.at(offset + 2).simplified(),
                          splittedStudent.at(0) + "MA"),
                  0, QString());
  }
  if (ok && (splittedStudent.at(offset + 5).simplified() == "True" ||
             splittedStudent.at(offset + 5).simplified() == "1") &&
      !splittedStudent.at(offset + 2).simplified().isEmpty()) {
    // fill exam retaking
    int evaluationId = getEvaluationId(subject, "Экзамен",
                                       splittedStudent.at(offset + 7),
                                       groupId,
                                       splittedStudent.at(offset + 6));
    ok = fillMark(evaluationId, studentId,
                  getMark(splittedStudent.at(offset + 2).simplified(),
                          splittedStudent.at(0) + "ER"),
                  0, QString());
  }
  return ok;
}

static bool fillMark(int evaluationId, int studentId, int value, int teacherId,
                     QString date) {
  QSqlQuery query;
  query.prepare("INSERT INTO mark (evaluation_id, student_id, value,"
                " teacher_id, date) VALUES (?, ?, ?, ?, ?)");
  query.addBindValue(evaluationId);
  query.addBindValue(studentId);
  query.addBindValue(value);
  query.addBindValue(teacherId ? teacherId : QVariant());
  if (date.isEmpty()) {
    query.addBindValue(QVariant());
  } else {
    query.addBindValue(QDate::fromString(date.split(" ").at(0), "dd.MM.yyyy"));
  }
  return execQuery(query);
}

static int getEvaluationId(QString subject, QString controlType,
                           QString teacher, int groupId, QString date) {
  QSqlQuery query;
  query.prepare("SELECT id FROM control_type WHERE type = ?");
  query.addBindValue(controlType);
  if (!execAndNextQuery(query)) {
    qDebug() << "unknown control type" << controlType;
    return 0;
  }
  int controlTypeId = query.record().value("id").toInt();
  query.prepare("SELECT troop_id FROM university_group WHERE id = ?");
  query.addBindValue(groupId);
  if (!execAndNextQuery(query)) {
    return 0;
  }
  int troopId = query.record().value("id").toInt();
  query.prepare("SELECT id FROM subject WHERE name = ?");
  query.addBindValue(subject);
  if (!execAndNextQuery(query)) {
    qDebug() << "unknown subject" << subject;
    return 0;
  }
  int subjectId = query.record().value("id").toInt();
  teacher = teacher.simplified();
  int teacherId = 0;
  if (!teacher.isEmpty()) {
    query.prepare("SELECT id FROM teacher WHERE name = ?");
    query.addBindValue(teacher);
    if (!execAndNextQuery(query)) {
      QStringList splittedTeacher = teacher.split(" ");
      query.prepare("SELECT id FROM teacher WHERE name LIKE '%" +
                    splittedTeacher.at(splittedTeacher.length() - 2) + " " +
                    splittedTeacher.last() + "'");
      if (!execAndNextQuery(query)) {
        query.prepare("INSERT INTO teacher (name) VALUES (?)");
        query.addBindValue(teacher);
        if (!execQuery(query)) {
          qDebug() << "teacher insertion error";
          return 0;
        } else {
          teacherId = query.lastInsertId().toInt();
        }
      }
    }
    if (!teacherId) {
      teacherId = query.record().value("id").toInt();
    }
  }
  date = date.simplified();
  QDate oDate = QDate(1970, 1, 1);
  if (!date.isEmpty()) {
    oDate = QDate::fromString(date.split(" ").at(0), "dd.MM.yyyy");
  }
  query.prepare("SELECT id FROM evaluation WHERE subject_id = ? AND"
                " control_type_id = ? AND troop_id = ? AND date = ?");
  query.addBindValue(subjectId);
  query.addBindValue(controlTypeId);
  query.addBindValue(troopId);
  query.addBindValue(oDate);
  if (!execQuery(query)) {
    qDebug() << "ALARMEEEE";
    return 0;
  }
  if (query.next()) {
    return query.record().value("id").toInt();
  }
  query.prepare("INSERT INTO evaluation (subject_id, control_type_id,"
                " teacher_id, troop_id, date) VALUES (?, ?, ?, ?, ?)");
  query.addBindValue(subjectId);
  query.addBindValue(controlTypeId);
  query.addBindValue(teacherId ? teacherId : QVariant());
  query.addBindValue(troopId);
  query.addBindValue(oDate);
  if (!execQuery(query)) {
    qDebug() << "OPA ZHOPA STYLE";
    return 0;
  }
  return query.lastInsertId().toInt();
}

bool CSVOldFormatConverter::fillSubjects(QString) {
  QSqlQuery query;
  QString queryString = "INSERT INTO subject (name) VALUES ('" + VAT +
      "'), ('" + UPVMV + "'), ('" + PDD + "'), ('" + TSP + "'), ('" + TP +
      "'), ('" + UAT + "'), ('" + EAT + "'), ('" + OGP + "')";
  if (!query.exec(queryString)) {
    return false;
  }
  return true;
}


int CSVOldFormatConverter::getGroupId(
    QString groupName, QString graduatedFromUniverisityInYear,
    QString troopName, QString graduatedFromMilitaryDepartmentDate,
    QString degreeEnrollmentNumber,
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
       {"ЭС", "ЭС"},
       {"ИСИТ", "ИТ"},
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
       {"ПМ", "ПМ"},
       {"ЗР", "ЗР"}
      };
  QSqlQuery query;
  QString queryString = "SELECT id FROM university_group WHERE name = ?";
  QString groupNamePrefix, groupNameNumber;
  int separatorPosition;
  int facultyId;
  int troopId;
  QDate graduatedFromUniversityDate;
  groupName = groupName.toUpper().simplified();
  if (groupName.isEmpty()) {
    if (troopName == "ЭО-41") {
      groupName = troopName;
    } else {
      qDebug() << "empty group name" << troopName;
      throw;
    }
  }
  separatorPosition = groupName.indexOf('-');
  groupNamePrefix =
      groupNamesPrefixSynonims.value(
        groupName.left(separatorPosition).simplified());
  if (groupNamePrefix.isEmpty()) {
    qDebug() << "unknown group prefix" << groupName;
    throw;
  }
  groupNameNumber = groupName.mid(separatorPosition + 1);
  groupName = groupNamePrefix + "-" + groupNameNumber;
  if (groupNameNumber.length() != 4) {
    groupName += " (" + graduatedFromUniverisityInYear + ")";
  }
  query.prepare(queryString);
  query.addBindValue(groupName);
  if (!query.exec()) {
    qDebug() << query.lastError().text();
    throw;
  }
  if (query.next()) {
    return query.record().value("id").toInt();
  }
  facultyId = getFacultyId(groupNamePrefix);
  troopId = getTroopId(
        troopName, graduatedFromMilitaryDepartmentDate, degreeEnrollmentNumber,
        graduatedFromMilitaryDepartmentInYear);
  if (!facultyId || !troopId) {
    throw;
  }
  queryString = "INSERT INTO university_group (name,"
      " graduated_from_university_date, faculty_id, troop_id)"
      " VALUES (?, ?, ?, ?)";
  query.prepare(queryString);
  query.addBindValue(groupName);
  graduatedFromUniversityDate.setDate(
        graduatedFromUniverisityInYear.toInt(), 7, 1);
  query.addBindValue(graduatedFromUniversityDate);
  query.addBindValue(facultyId);
  query.addBindValue(troopId);
  if (!query.exec()) {
    qDebug() << query.lastError().text();
    return 0;
  }
  return query.lastInsertId().toInt();
}


QString getTroopNameStartYear(QString troopNamePrefix, QString troopNameNumber,
                              QString graduatedFromMilitaryDepartmentInYear) {
  return "2";
}


int CSVOldFormatConverter::getTroopId(
    QString troopName, QString graduatedFromMilitaryDepartmentDate,
    QString degreeEnrollmentNumber,
    QString graduatedFromMilitaryDepartmentInYear) {
  // TODO: refactor this stuff
  QString enteredAtMilitaryDepartmentDate;
  QString troopNamePrefix;
  QString troopNamePostfix;
  QRegExp shortPostfix = QRegExp("\\d\\d");
  QRegExp longPostfix = QRegExp("\\d\\d/\\d\\d");
  QRegExp degreeSplitter = QRegExp("№ ?\\d{1,4} ?(от)? ?");
  QDate dateEnteredAt;
  QDate dateGraduatedFrom;
  QString queryString;
  QSqlQuery query;
  QString formattedTroopName;
  int separatorPosition;
  int difference;
  troopName = troopName.toUpper().simplified();
  if (troopName == "АШ32") {
    troopName = "АШ-32";
  } else if (troopName.isEmpty()) {
    qDebug() << graduatedFromMilitaryDepartmentDate << degreeEnrollmentNumber <<
                graduatedFromMilitaryDepartmentInYear;
    return 0;
  }
  if (!graduatedFromMilitaryDepartmentDate.simplified().isEmpty()) {
    graduatedFromMilitaryDepartmentDate =
        graduatedFromMilitaryDepartmentDate.split(" ").at(0);
    dateGraduatedFrom = QDate::fromString(graduatedFromMilitaryDepartmentDate,
                                          "dd.MM.yyyy");
  } else if (!graduatedFromMilitaryDepartmentInYear.isEmpty()) {
    if (graduatedFromMilitaryDepartmentInYear != "0") {
      dateGraduatedFrom.setDate(
            graduatedFromMilitaryDepartmentInYear.toInt(), 9, 17);
    }
  }
  if (!degreeEnrollmentNumber.isEmpty()) {
    enteredAtMilitaryDepartmentDate = degreeEnrollmentNumber
        .split(degreeSplitter).last().replace("ю", ".").replace(" ", ".");
    if (enteredAtMilitaryDepartmentDate.endsWith("г.")) {
      enteredAtMilitaryDepartmentDate.chop(2);
    } else if (enteredAtMilitaryDepartmentDate.endsWith("г")) {
      enteredAtMilitaryDepartmentDate.chop(1);
    } else if (enteredAtMilitaryDepartmentDate.endsWith(".")) {
      enteredAtMilitaryDepartmentDate.chop(1);
    }
    if (enteredAtMilitaryDepartmentDate.split(".").last().length() == 2) {
      enteredAtMilitaryDepartmentDate = enteredAtMilitaryDepartmentDate.insert(
            enteredAtMilitaryDepartmentDate.length() - 2, "20");
    }
    dateEnteredAt = QDate::fromString(enteredAtMilitaryDepartmentDate,
                                      "d.MM.yyyy");
  }
  if (!dateGraduatedFrom.isValid() && !dateEnteredAt.isValid()) {
    qDebug() << "invalid dates" << dateEnteredAt << dateGraduatedFrom;
    return 0;
  } else if (dateGraduatedFrom.isValid()) {
    // guessing about entered date
    dateEnteredAt.setDate(dateGraduatedFrom.year() - 3, 6, 29);
  } else { // if (dateEnteredAt.isValid())
    dateGraduatedFrom.setDate(dateEnteredAt.year() + 3, 9, 17);
//    qDebug() << "invalid graduation date";
//    return 0;
  }
  int cyear = QDate::currentDate().year();
  if (cyear > dateGraduatedFrom.year()) {
    cyear = dateGraduatedFrom.year();
  }
  difference = cyear - dateEnteredAt.year() - 1;
  separatorPosition = troopName.indexOf('-');
  troopNamePrefix = troopName.left(separatorPosition);
  troopNamePostfix = troopName.mid(separatorPosition + 1);
  formattedTroopName = troopNamePrefix + "-";
  if (shortPostfix.exactMatch(troopNamePostfix)) {
    // TODO: make that more cleaner and optimized
    formattedTroopName +=
        "<N:" +
        QString::number(QString(troopNamePostfix.at(0)).toInt() - difference) +
        ">" + troopNamePostfix.at(1);
  } else if (longPostfix.exactMatch(troopNamePostfix)) {
    formattedTroopName +=
        "<N:" +
        QString::number(QString(troopNamePostfix.at(0)).toInt() - difference) +
        ">" + troopNamePostfix.at(1) + "/" + "<N:" +
        QString::number(QString(troopNamePostfix.at(3)).toInt() - difference) +
        ">" + troopNamePostfix.at(4);
  } else {
    qDebug() << "asshole" << troopNamePostfix << troopName;
    return 0;
  }
  troopName = formattedTroopName;
  queryString = "SELECT id FROM troop WHERE name = ? AND"
      " entered_at_military_department_date = ?";
  query.prepare(queryString);
  query.addBindValue(troopName);
  query.addBindValue(dateEnteredAt);
  if (!query.exec()) {
    qDebug() << query.lastError().text();
    return 0;
  }
  if (!query.next()) {
    queryString = "INSERT INTO troop (name,"
        " entered_at_military_department_date,"
        " graduated_from_military_department_date, military_profession_id)"
        " VALUES (?, ?, ?, ?)";
    query.prepare(queryString);
    query.addBindValue(troopName);
    query.addBindValue(dateEnteredAt);
    query.addBindValue(dateGraduatedFrom);
    query.addBindValue(1);
    if (!query.exec()) {
      qDebug() << query.lastError().text();
      return 0;
    }
    return query.lastInsertId().toInt();
  } else {
    return query.record().value("id").toInt();
  }
}


int CSVOldFormatConverter::getFacultyId(QString groupNamePrefix) {
  QHash<QString, QString> groupPrefixToUniversityFacultyName =
      {
       {"ПИЭ", "Прикладной информатики"},
       {"ПИЮ", "Прикладной информатики"},
       {"ПИ", "Прикладной информатики"},
       {"ЮФ", "Юридический"},
       {"СТ", "Инженерно-строительный"},
       {"АИ", "Агрохимии и почвоведения"},
       {"ЭО", "Экономический"},
       {"ВХ", "Водного хозяйства"},
       {"ЗК", "Земельного кадастра"},
       {"ЗШ", "Земельного кадастра"},
       {"ИЗ", "Инженерно-землеустроительный"},
       {"РЗ", "Защиты растений"},
       {"ЗР", "Защиты растений"},
       {"ХП", "Агрохимии и почвоведения"},
       {"ФЭ", "Энергетики и электрификации"},
       {"ЭК", "Экономический"},
       {"ПВ", "Плодоовощеводства и виноградарства"},
       {"МХ", "Механизации"},
       {"ТХП", "Перерабатывающих технологий"},
       {"АШ", "Агрономический"},
       {"АТ", "Агротехнологический"},
       {"ГУ", "Управления"},
       {"ФК", "Финансы и кредит"},
       {"УФ", "Учетно-финансовый"},
       {"НН", "Налоги и налогооблажение"},
       {"ВВ", "Водного хозяйства"},
       {"ГМУ", "Управления"},
       {"ТПП", "Перерабатывающих технологий"},
       {"СГ", "Агрономический"},
       {"Э", "Экономический"},
       {"ЭС", "Энергетики и электрификации"},
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
       {"УВ", "Энергетики и электрификации"}
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
    if (query.lastError().isValid()) {
      qDebug() << query.lastError().text();
    }
    qDebug() << facultyName << groupNamePrefix;
    return 0;
  }
  return query.record().value("id").toInt();
}
