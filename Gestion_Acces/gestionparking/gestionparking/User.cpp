#include "User.h"
#include "Formgestion.h"
#include "BDD.h"

User::User(const QString& login, const QString& password, const QString& type, QObject* parent)
    : QObject(parent), m_login(login), m_password(password), m_type(type) {

}

QString User::getLogin() const {
    return m_login;
}

void User::setLogin(const QString& login) {
    m_login = login;
}

QString User::getPassword() const {
    return m_password;
}

void User::setPassword(const QString& password) {
    m_password = password;
}

QString User::getType() const {
    return m_type;
}

void User::setType(const QString& type) {
    m_type = type;
}

bool User::isValid() const {
    return !m_login.isEmpty() && !m_password.isEmpty();
}

void User::Accept(Demande d) {
    //return BDD::isAccept()->Accept();
    BDD::getInstance()->acceptDemande(d.id);
}

void User::Refuser(Demande d)
{
    BDD::getInstance()->refuserDemande(d.id);
}

void User::Incomplete(Demande d)
{
    BDD::getInstance()->attenteDemande(d.id);
}

bool User::connexion() {
    if (!isValid()) {
        qDebug() << "Les informations de connexion ne sont pas valides.";
        return false;
    }


    if (BDD::getInstance()->checkAuthentication(m_login, m_password))
    {
        // Cr�er une nouvelle instance de la fen�tre de gestion
        Formgestion* formGestion = new Formgestion;
        formGestion->show(); // Afficher la nouvelle fen�tre de gestion
    }
}
QList<Demande> User::getListeDemandes() {
    return BDD::getInstance()->getListeDemandes();
}