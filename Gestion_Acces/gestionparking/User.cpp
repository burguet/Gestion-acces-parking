#include "User.h"
#include "Formgestion.h"

User::User(const QString& login, const QString& password, const QString& type)
    : m_login(login), m_password(password), m_type(type)
{
    // Initialiser la connexion � la base de donn�es dans le constructeur
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("192.168.65.167");
    m_db.setDatabaseName("parking");
    m_db.setUserName("root");
    m_db.setPassword("root");
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
bool User::connexion() {
    if (!isValid()) {
        qDebug() << "Les informations de connexion ne sont pas valides.";
        return false;
    }

    if (!m_db.open()) {
        qDebug() << "Erreur lors de la connexion � la base de donn�es :" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE login = :username AND password = :password AND type = 'admin'");
    query.bindValue(":username", m_login);
    query.bindValue(":password", m_password);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ex�cution de la requ�te :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "Authentification r�ussie ! Type d'utilisateur : admin";

        // Cr�er une nouvelle instance de la fen�tre de gestion
        Formgestion* formGestion = new Formgestion;
        formGestion->show(); // Afficher la nouvelle fen�tre de gestion

        return true;
    }
    else {
        qDebug() << "Authentification �chou�e. Veuillez v�rifier votre nom d'utilisateur et votre mot de passe.";
        return false;
    }
}

