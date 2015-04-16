#include "database.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>
#include <QSqlRecord>
#include <QVariant>
#include <QFile>
#include <QDebug>

Database::Database(QObject *parent)
    : QObject(parent) {
}

bool Database::init(const QString fileName, const bool test) {
  QFile file(fileName);
  if (file.exists()) {
    file.remove();
  }
  if (!open(fileName)) {
    return false;
  }
  QString initScript =
      "CREATE TABLE university_faculty ("
      "  id INTEGER PRIMARY KEY,"
      "  archived BOOLEAN DEFAULT 0 NOT NULL,"
      "  name TEXT NOT NULL UNIQUE"
      ");"
      "CREATE INDEX university_faculty_archived"
      " ON university_faculty (archived);"
      "CREATE TABLE military_profession ("
      "  id INTEGER PRIMARY KEY,"
      "  archived BOOLEAN DEFAULT 0 NOT NULL,"
      "  code TEXT NOT NULL UNIQUE,"
      "  name TEXT NOT NULL UNIQUE"
      ");"
      "CREATE INDEX military_profession_archived"
      " ON military_profession (archived);"
      "CREATE TABLE teacher ("
      "  id INTEGER PRIMARY KEY,"
      "  dismissed BOOLEAN DEFAULT 0 NOT NULL,"
      "  name TEXT NOT NULL"
      ");"
      "CREATE INDEX teacher_dismissed ON teacher (dismissed);"
      "CREATE TABLE troop ("
      "  id INTEGER PRIMARY KEY,"
      "  name TEXT NOT NULL,"
      // pattern-based name, like "ПИЭ-<N:2>1/<N:3>1" or "ПИ-<N:2>1"
      // we will increase pattern placeholder every next year after the year
      // of entrance until the year of graduation
      "  entered_at_military_department_date DATE NOT NULL,"
      "  graduated_from_military_department_date DATE,"
      "  curator_id INTEGER REFERENCES teacher (id),"
      "  military_profession_id INTEGER REFERENCES military_profession (id)"
      "   NOT NULL"
      ");"
      "CREATE UNIQUE INDEX troop_name_unique ON"
      "  troop (name, entered_at_military_department_date);"
      "CREATE TABLE university_group ("
      "  id INTEGER PRIMARY KEY,"
      "  name TEXT NOT NULL UNIQUE,"
      "  graduated_from_university_year INT,"
      "  faculty_id INTEGER REFERENCES university_faculty (id) NOT NULL,"
      "  troop_id INTEGER REFERENCES troop (id) NOT NULL"
      ");"
      "CREATE INDEX university_group_troop_id ON university_group (troop_id);"
      // every univeristy group is linked with troop. If troop contains multiple
      // groups, when we generate exam lists for troop, we shoul generate
      // separate list for every group
      // we should create next table because SQLite does not support ENUMs
      "CREATE TABLE expulsion_reason ("
      "  id INTEGER PRIMARY KEY,"
      "  reason TEXT NOT NULL UNIQUE"
      ");"
      // we should create next table because SQLite does not support ENUMs
      "CREATE TABLE expulsed_from ("
      "  id INTEGER PRIMARY KEY,"
      "  unit TEXT NOT NULL UNIQUE"
      ");"
      "CREATE TABLE student ("
      "  id INTEGER PRIMARY KEY," // 0
      "  lastname TEXT NOT NULL," // 1
      "  firstname TEXT NOT NULL," // 2
      "  middlename TEXT NOT NULL," // 3
      "  lastname_datum TEXT," // 4
      "  firstname_datum TEXT," // 5
      "  middlename_datum TEXT," // 6
      "  lastname_accusative TEXT," // 7
      "  firstname_accusative TEXT," // 8
      "  middlename_accusative TEXT," // 9
      "  dob DATE," // 10
      "  university_group_id INTEGER REFERENCES university_group (id) NOT NULL,"
      "  decree_enrollment_number TEXT," // TODO: discucss about // 12
      "  decree_expulsion_number TEXT," // TODO: discuss about // 13
      "  expulsion_reason_id INTEGER REFERENCES expulsion_reason (id)," // 14
      "  expulsed_from_id INTEGER REFERENCES expulsed_from (id)" // 15
      ");"
      "CREATE TABLE subject ("
      "  id INTEGER PRIMARY KEY,"
      "  archived BOOLEAN DEFAULT 0 NOT NULL,"
      "  name TEXT NOT NULL UNIQUE"
      ");"
      "CREATE INDEX subject_archived ON subject (archived);"
      "CREATE TABLE subject_duration ("
      "  subject_id INTEGER REFERENCES subject (id) NOT NULL,"
      "  military_profession_id INTEGER REFERENCES military_profession (id)"
      "   NOT NULL,"
      "  duration INTEGER NOT NULL"
      ");"
      "CREATE UNIQUE INDEX subject_duration_unique"
      " ON subject_duration (subject_id, military_profession_id);"
      // we should create next table because SQLite does not support ENUMs
      "CREATE TABLE control_type ("
      "  id INTEGER PRIMARY KEY,"
      "  type TEXT NOT NULL UNIQUE"
      ");"
      "CREATE TABLE evaluation ("
      "  id INTEGER PRIMARY KEY,"
      "  date DATE NOT NULL,"
      "  subject_id INTEGER REFERENCES subject (id) NOT NULL,"
      "  troop_id INTEGER REFERENCES troop (id) NOT NULL,"
      "  control_type_id INTEGER REFERENCES control_type (id) NOT NULL,"
      "  teacher_id INTEGER REFERENCES teacher (id)"
      ");"
      "CREATE UNIQUE INDEX evaluation_unique"
      " ON evaluation (subject_id, control_type_id, troop_id, date);"
      // CONVERSION PROCEDURE RELATED NOTICE: if date is unknown it will
      // be filled with unixtime start date: 1970-01-01
      "CREATE TABLE mark_value ("
      "  id INTEGER PRIMARY KEY,"
      "  name TEXT UNIQUE NOT NULL"
      ");"
      "CREATE TABLE mark ("
      "  evaluation_id INTEGER REFERENCES evaluation (id) NOT NULL,"
      "  student_id INTEGER REFERENCES student (id) NOT NULL,"
      "  value INTEGER REFERENCES mark_value (id) NOT NULL,"
      "  teacher_id INTEGER REFERENCES teacher (id),"
      // teacher_id filled only if (mark.teacher_id != evaluation.teacher_id)
      "  date DATE" // filled only if (marked.date != evaluation.date)
      ");";
  QSqlQuery query;
  for (QString queryString : initScript.split(';')) {
    if (!queryString.isEmpty()) {
      execQueryAndReturnId(&query, queryString);
    }
  }
  QStringList baseQueries = {
    "INSERT INTO control_type (type) VALUES ('Экзамен'), ('Зачёт'),"
    " ('Аттестация')",
    "INSERT INTO expulsion_reason (reason) VALUES ('Плохая успеваемость'),"
    " ('Непосещаемость'), ('Нарушение устава')",
    "INSERT INTO expulsed_from (unit) VALUES ('Университет'),"
    " ('Военная кафедра')",
    "INSERT INTO mark_value (id, name) VALUES (5, 'Отлично'), (4, 'Хорошо'),"
    " (3, 'Удовлетворительно'), (2, 'Неудовлетворительно'), (1, 'Сдал'),"
    " (0, 'Не сдал'), (-1, 'Не явился'), (-2, 'Не допущен')"
  };
  for (QString queryString : baseQueries) {
    execQueryAndReturnId(&query, queryString);
  }
  if (test) {
    QVariant universityFacultyId;
    QVariant militaryProfessionId;
    QVariant troopId;
    QVariant universityGroupId;
    QVariantList studentIds;
    QVariantList subjectIds;
    universityFacultyId = execQueryAndReturnId(
          &query, "INSERT INTO university_faculty (name) VALUES ('AI')");
    militaryProfessionId = execQueryAndReturnId(
          &query, "INSERT INTO military_profession (code, name)"
          " VALUES ('VUS-260100', 'Units management')");
    query.prepare("INSERT INTO troop (name, military_profession_id)"
                  " VALUES ('AI41', ?)");
    query.addBindValue(militaryProfessionId);
    troopId = execQueryAndReturnId(&query);
    query.prepare("INSERT INTO university_group (name, faculty_id, troop_id)"
                  " VALUES ('AI-0904', ?, ?)");
    query.addBindValue(universityFacultyId);
    query.addBindValue(troopId);
    universityGroupId = execQueryAndReturnId(&query);
    query.prepare(
          "INSERT INTO student (lastname, firstname, middlename,"
          " lastname_datum, firstname_datum, middlename_datum,"
          " university_group_id) VALUES (:lastname, :firstname, :middlename,"
          " :lastname_d, :firstname_d, :middlename_d, :university_group_id)");
    query.bindValue(":university_group_id", universityGroupId);
    for (short i = 0; i < 3; ++i) {
      query.bindValue(":lastname", QString::number(i) + "Lastname");
      query.bindValue(":firstname", QString::number(i) + "Firstname");
      query.bindValue(":middlename", QString::number(i) + "Middlename");
      query.bindValue(":lastname_d", QString::number(i) + "LastnameD");
      query.bindValue(":firstname_d", QString::number(i) + "FirstnameD");
      query.bindValue(":middlename_d", QString::number(i) + "MiddlenameD");
      studentIds.append(execQueryAndReturnId(&query));
    }
    query.prepare("INSERT INTO subject (name) VALUES (?)");
    for (QString subjectName : {"Wizard training", "Sword training",
         "Bebop training"}) {
      query.addBindValue(subjectName);
      subjectIds.append(execQueryAndReturnId(&query));
    }
  }
  return true;
}
#include <QSqlDriver>
//#include <sqlite3.h>
#include <QRegularExpression>

//static void likeFunc(
//  sqlite3_context *context,
//  int argc,
//  sqlite3_value **argv
//){
//  const unsigned char *zA = sqlite3_value_text(argv[0]);
//  const unsigned char *zB = sqlite3_value_text(argv[1]);
//  int escape = 0;
//  if( argc==3 ){
//    /* The escape character string must consist of a single UTF-8 character.
//    ** Otherwise, return an error.
//    */
//    const unsigned char *zEsc = sqlite3_value_text(argv[2]);
////    if( sqlite3utf8CharLen(zEsc, -1)!=1 ){
////      sqlite3_result_error(context,
////          "ESCAPE expression must be a single character", -1);
////      return;
////    }
////    escape = sqlite3ReadUtf8(zEsc);
//  }
//  if( zA && zB ){
//    struct compareInfo *pInfo = sqlite3_user_data(context);
//#ifdef SQLITE_TEST
//    sqlite3_like_count++;
//#endif
//    sqlite3_result_int(context, patternCompare(zA, zB, pInfo, escape));
//  }
//}

bool Database::open(const QString fileName) {
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(fileName);
  if (!db.open()) {
    return false;
  }
  QSqlQuery query;
  for (auto queryString : {"PRAGMA page_size = 4096",
       "PRAGMA cache_size = -16384", "PRAGMA temp_store = MEMORY",
       "PRAGMA journal_mode = OFF", "PRAGMA locking_mode = EXCLUSIVE",
       "PRAGMA synchronous = OFF", "PRAGMA case_sensitive_like = OFF"}) {
    if (!query.exec(queryString)) {
      return false;
    }
  }

  QVariant v = db.driver()->handle();
  if (!v.isValid() || qstrcmp(v.typeName(), "sqlite3*") != 0) {
  qWarning() << "Cannot get a sqlite3 handle to the driver.";
  return false;
  }

  // Create a handler and attach functions.
  //sqlite3* handler = *static_cast<sqlite3**>(v.data());
  //if (!handler) {
  //qWarning() << "Cannot get a sqlite3 handler.";
  //return false;
  //}

  // Check validity of the state.
//  if (!db.isValid()) {
//  qCritical() << "Cannot create SQLite custom functions: db object is not valid.";
//  return false;
//  }

//  if (!db.isOpen()) {
//  qCritical() << "Cannot create SQLite custom functions: db object is not open.";
//  return false;
//  }

//  if (sqlite3_create_function(handler, "like", 1, SQLITE_ANY, 0, likeFunc, 0, 0))
//  qCritical() <<"Cannot create SQLite functions: sqlite3_create_function failed.";

  return true;
}

QVariant Database::execQueryAndReturnId(QSqlQuery *query) {
  if (!query->exec()) {
    throw query->lastError();
  }
  return query->lastInsertId();
}

QVariant Database::execQueryAndReturnId(QSqlQuery *query,
                                        const QString queryString) {
  if (!query->exec(queryString)) {
    throw query->lastError();
  }
  return query->lastInsertId();
}
