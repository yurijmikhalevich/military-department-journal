#include "database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

Database::Database(QObject *parent) :
    QObject(parent)
{
}

/**
 * @param fileName File to store new database
 * @param test If true function will populate database with test data
 * @return true if database was successfully initiated, otherwise returns false
 */
bool Database::init(QString fileName, bool test)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if (!db.open()) {
        return false;
    }
    QString initScript =
            "CREATE TABLE university_group ("
            "  id INTEGER PRIMARY KEY,"
            "  name TEXT NOT NULL UNIQUE,"
            "  graduated_from_university_in INTEGER"
            ");"
            "CREATE TABLE expulsion_reason ("
            "  id INTEGER PRIMARY KEY,"
            "  reason TEXT NOT NULL"
            ");"
            "CREATE TABLE expulsed_from ("
            "  id INTEGER PRIMARY KEY,"
            "  archived BOOLEAN DEFAULT 0 NOT NULL,"
            "  unit TEXT NOT NULL"
            ");"
            "CREATE TABLE military_profession ("
            "  id INTEGER PRIMARY KEY,"
            "  archived BOOLEAN DEFAULT 0 NOT NULL,"
            "  code TEXT UNIQUE,"
            "  name TEXT UNIQUE"
            ");"
            "CREATE TABLE teacher ("
            "  id INTEGER PRIMARY KEY,"
            "  name TEXT NOT NULL,"
            "  dismissed BOOLEAN DEFAULT 0"
            ");"
            "CREATE INDEX teacher_dismissed ON teacher (dismissed);"
            "CREATE TABLE troop ("
            "  id INTEGER PRIMARY KEY,"
            "  name TEXT NOT NULL UNIQUE,"
            "  year_of_training INTEGER DEFAULT 1,"
            "  graduated_from_in INTEGER,"
            "  graduated BOOLEAN DEFAULT 0,"
            "  curator_id INTEGER REFERENCES teacher (id)"
            ");"
            "CREATE TABLE student ("
            "  id INTEGER PRIMARY KEY,"
            "  lastname TEXT NOT NULL,"
            "  firstname TEXT NOT NULL,"
            "  middlename TEXT NOT NULL,"
            "  lastname_datum TEXT,"
            "  firstname_datum TEXT,"
            "  middlename_datum TEXT,"
            "  lastname_accusative TEXT,"
            "  firstname_accusative TEXT,"
            "  middlename_accusative TEXT,"
            "  dob DATE,"
            "  university_group_id INTEGER REFERENCES university_group (id),"
            "  decree_enrollment_number TEXT,"
            "  decree_expulsion_number TEXT,"
            "  expulsion_reason_id INTEGER REFERENCES expulsion_reason (id),"
            "  expulsed_from_id INTEGER REFERENCES expulsed_from (id),"
            "  troop_id INTEGER REFERENCES troop (id)"
            ");"
            "CREATE TABLE subject ("
            "  id INTEGER PRIMARY KEY,"
            "  duration INTEGER NOT NULL,"
            "  archived BOOLEAN DEFAULT 0 NOT NULL,"
            "  name TEXT NOT NULL UNIQUE"
            ");"
            "CREATE TABLE control_type (" // that table is preconfigured, used as ENUM
            "  id INTEGER PRIMARY KEY,"
            "  name TEXT NOT NULL"
            ");"
            "CREATE TABLE evaluation ("
            "  id INTEGER PRIMARY KEY,"
            "  subject_id INTEGER REFERENCES subject (id) NOT NULL,"
            "  control_type_id INTEGER REFERENCES control_type (id) NOT NULL,"
            "  teacher_id INTEGER REFERENCES teacher (id) NOT NULL,"
            "  troop_id INTEGER REFERENCES troop (id) NOT NULL,"
            "  date DATE NOT NULL"
            ");"
            "CREATE TABLE mark ("
            "  evaluation_id INTEGER REFERENCES evaluation (id) NOT NULL,"
            "  student_id INTEGER REFERENCES student (id) NOT NULL,"
            "  value INTEGER NOT NULL,"
            "  teacher_id INTEGER REFERENCES teacher (id)," // filled only if (mark.teacher_id != evaluation.teacher_id)
            "  date DATE" // filled only if (marked.date != evaluation.date)
            ");";
    for (QString query : initScript.split(';')) {
        if (db.exec(query).lastError().type() != QSqlError::NoError) {
            return false;
        }
    }
    if (test) {
        QSqlQuery *query = new QSqlQuery(db);
        if (!query->exec("INSERT INTO control_type (name) VALUES ('exam'), ('credit'), ('validation')")) {
            return false;
        }
        QVariant id;
        query->prepare("INSERT INTO university_group (name) VALUES ('AI-0904')");
        if (!query->exec()) {
            return false;
        }
        id = query->lastInsertId();
        query->prepare("INSERT INTO student (lastname, firstname, middlename, lastname_datum, firstname_datum, "
                       "middlename_datum, university_group_id) VALUES "
                       "(:lastname, :firstname, :middlename, :lastname_d, :firstname_d, :middlename_d, :id)");
        query->bindValue(":id", id);
        QVariantList studentIds;
        for (short i = 0; i < 3; ++i) {
            query->bindValue(":lastname", QString::number(i) + "Lastname");
            query->bindValue(":firstname", QString::number(i) + "Firstname");
            query->bindValue(":middlename", QString::number(i) + "Middlename");
            query->bindValue(":lastname_d", QString::number(i) + "LastnameD");
            query->bindValue(":firstname_d", QString::number(i) + "FirstnameD");
            query->bindValue(":middlename_d", QString::number(i) + "MiddlenameD");
            if (!query->exec()) {
                return false;
            }
            studentIds.append(query->lastInsertId());
        }
        query->prepare("INSERT INTO subject (name, duration) VALUES (?, ?)");
        QVariantList subjectIds;
        for (QString subjectName : { "Wizard trainging", "Sword training", "Jump training" }) {
            query->addBindValue(subjectName);
            query->addBindValue(140);
            if (!query->exec()) {
                return false;
            }
            subjectIds.append(query->lastInsertId());
        }
        query->prepare("INSERT INTO control_type (name) VALUES (?)");
        QVariantList controlTypeIds;
        for (QString controlTypeName : { "exam", "pass" }) {
            query->addBindValue(controlTypeName);
            if (!query->exec()) {
                return false;
            }
            controlTypeIds.append(query->lastInsertId());
        }
//        query->prepare("INSERT INTO mark (subject_id, control_type_id, student_id, value) VALUES (?, ?, ?, ?)");
//        for (QVariantList row :
//             QList<QVariantList>({ { subjectIds.at(0), controlTypeIds.at(0), studentIds.at(0), "fine" },
//                                   { subjectIds.at(0), controlTypeIds.at(0), studentIds.at(1), "good" },
//                                   { subjectIds.at(1), controlTypeIds.at(0), studentIds.at(0), "bad"  },
//                                   { subjectIds.at(0), controlTypeIds.at(1), studentIds.at(0), "pass" },
//                                   { subjectIds.at(0), controlTypeIds.at(0), studentIds.at(1), "fine" } })) {
//            for (short i = 0; i < 4; ++i) {
//                query->addBindValue(row.at(i));
//            }
//            if (!query->exec()) {
//                return false;
//            }
//        }
    }
    return true;
}

/**
 * @param fileName File with application database
 * @return true if operation completes successfully, otherwise returns false
 */
bool Database::open(QString fileName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if (!db.open()) {
        return false;
    }
    return true;
}
