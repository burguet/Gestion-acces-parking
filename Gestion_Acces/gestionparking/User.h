#ifndef USER_H
#define USER_H

#include <QString>
#include <QtSql>

class User {
public:
    User(const QString& login, const QString& password, const QString& type);
    QString getLogin() const;
    void setLogin(const QString& login);
    QString getPassword() const;
    void setPassword(const QString& password);
    QString getType() const;
    void setType(const QString& type);
    bool isValid() const;

    bool connexion();

private:
    QString m_login;
    QString m_password;
    QString m_type;
    QSqlDatabase m_db; // Ajout d'un objet QSqlDatabase pour la connexion à la base de données
};

#endif // USER_H
