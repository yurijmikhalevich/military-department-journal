#include "namemorpher.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

NameMorpher::NameMorpher(QObject *parent)
    : QObject(parent) {
  networkManager = new QNetworkAccessManager(this);
}

NameMorpher::MorphedName NameMorpher::getMorphedName(
    QString lastname, QString firstname, QString middlename, bool fake) {
  MorphedName morphedName;
//  if (fake) { // used for testing purposes not to load web service
    morphedName.lastnameAccusative = lastname;
    morphedName.lastnameDatum = lastname;
    morphedName.firstnameAccusative = firstname;
    morphedName.firstnameDatum = firstname;
    morphedName.middlenameAccusative = middlename;
    morphedName.middlenameDatum = middlename;
    // TODO: fix #9 https://github.com/39dotyt/military-department-journal/issues/9
//  } else {
//    QNetworkRequest request(
//          "http://morpher.ru/WebService.asmx/GetXml?s="
//          + QStringList({lastname, firstname, middlename}).join(" "));
//    QString response;
//    QStringList splittedString;
//    QNetworkReply *reply = networkManager->get(request);
//    QEventLoop *loop = new QEventLoop();
//    connect(reply, SIGNAL(finished()), loop, SLOT(quit()));
//    loop->exec();
//    response = QString(reply->readAll());
//    splittedString = response.split("<В>").at(1).split("</В>").at(0).split(" ");
//    morphedName.lastnameAccusative = splittedString.at(0);
//    morphedName.firstnameAccusative = splittedString.at(1);
//    morphedName.middlenameAccusative = splittedString.at(2);
//    splittedString = response.split("<Д>").at(1).split("</Д>").at(0).split(" ");
//    morphedName.lastnameDatum = splittedString.at(0);
//    morphedName.firstnameDatum = splittedString.at(1);
//    morphedName.middlenameDatum = splittedString.at(2);
//  }
  return morphedName;
}
