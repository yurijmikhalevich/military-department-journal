#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlRelationalTableModel>

/**
 * @brief The Database class, contains all common database methods
 */
class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = 0);
    static bool init(QString fileName, bool test = false);
    static bool open(QString fileName);
    
};

#endif // DATABASE_H
