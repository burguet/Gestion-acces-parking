#pragma once
#ifndef BDD_H
#define BDD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QDebug>
#include <QSslSocket>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QCoreApplication>
#include <QObject>
#include <QProcess>

#include "Demande.h"


class BDD : public QObject {
    Q_OBJECT
public:
    static BDD* getInstance();
    bool isConnected();
    bool checkAuthentication(QString login, QString password);
    QList<Demande> getListeDemandes();
    bool BDD::acceptDemande(int id);
    bool BDD::refuserDemande(int id);
    bool BDD::attenteDemande(int id);
    bool BDD::EchangeMessage(int id, QString message);
    void BDD::sendEmail(QString mail, QString nom, QString subject, QString message);
    int idenvoie;

private:
    QNetworkAccessManager manager;
    static BDD* instance;
    BDD();
    QSqlDatabase m_db;
};

#endif // BDD_H
