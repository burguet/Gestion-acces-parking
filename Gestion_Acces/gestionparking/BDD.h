#pragma once
#ifndef BDD_H
#define BDD_H

#include <QtSql>
#include <QtMessageHandler>
#include "Demande.h"


class BDD {
public:
    static BDD* getInstance();
    bool isConnected();
    bool checkAuthentication(QString login, QString password);
    QList<Demande> getListeDemandes();
    bool BDD::acceptDemande(int id);
    bool BDD::refuserDemande(int id);
    bool BDD::attenteDemande(int id);
    void sendEmail(const QString& recipient, const QString& subject, const QString& body);


private:
    static BDD* instance;
    BDD();
    QSqlDatabase m_db;
};

#endif // BDD_H
