#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMap>
#include <QList>
#include <qsqlerror.h>
#include "Demande.h"

class User : public QObject {
    Q_OBJECT
public:
    explicit User(const QString& login = "", const QString& password = "", const QString& type = "", QObject* parent = nullptr);

    // Fonction pour r�cup�rer les demandes de v�hicules
    QList<Demande> getListeDemandes();

    // Getters et setters pour les propri�t�s de l'utilisateur
    QString getLogin() const;
    void setLogin(const QString& login);
    QString getPassword() const;
    void setPassword(const QString& password);
    QString getType() const;
    void setType(const QString& type);
    bool isValid() const;
    void Accept(Demande d);
    void Refuser(Demande d);
    void Incomplete(Demande d);
    // Fonction pour tenter de se connecter � la base de donn�es
    bool connexion();

private:
    QString m_login;
    QString m_password;
    QString m_type;   
};

#endif // USER_H
