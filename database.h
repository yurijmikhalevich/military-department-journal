#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>

/**
 * @brief The Database class, contains all common database methods
 */
class Database : public QObject {
  Q_OBJECT
public:
  explicit Database(QObject *parent = 0);
  /**
   * @param fileName File to store new database
   * @param test If true function will populate database with test data
   * @return true if database was successfully initiated, otherwise returns
   * false
   */
  static bool init(const QString fileName, const bool test = false);
  /**
   * @brief open Opens connection to the SQLite database using embedded Qt
   * server
   * @param fileName Path to SQLite database
   * @return true if connection was successfully established, otherwise
   * returns false
   */
  static bool open(const QString fileName);

private:
  /**
   * @brief execQueryAndReturnId Executes query and returns lastInsertId.
   * If used with non-insert statementvbehaviour is undefined. It throws
   * exception if execution of query is errored.
   * @param query Pointer to a QSqlQuery object
   * @return Id of last inserted record
   */
  static QVariant execQueryAndReturnId(QSqlQuery *query);
  /**
   * @brief execQueryAndReturnId Overloaded version of
   * execQueryAndReturnId(QSqlQuery *query). Used to pass query as QString
   * @param query Pointer to a QSqlQuery object
   * @param queryString Query to execute
   * @return Id of last inserted record
   */
  static QVariant execQueryAndReturnId(QSqlQuery *query,
                                       const QString queryString);
    
};

#endif // DATABASE_H
