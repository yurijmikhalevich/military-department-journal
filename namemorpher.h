#ifndef NAMEMORPHER_H
#define NAMEMORPHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QHash>

/**
 * @brief The NameMorpher class
 */
class NameMorpher : public QObject {
  Q_OBJECT
public:
  struct MorphedName {
    QString lastnameAccusative;
    QString firstnameAccusative;
    QString middlenameAccusative;
    QString lastnameDatum;
    QString firstnameDatum;
    QString middlenameDatum;
  };
  explicit NameMorpher(QObject *parent = 0);
  MorphedName getMorphedName(QString lastname, QString firstname,
                             QString middlename, bool fake = false);
private:
  QNetworkAccessManager *networkManager;
};

#endif // NAMEMORPHER_H
