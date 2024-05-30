#include "BDD.h"
#include <QCoreApplication>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>


BDD* BDD::instance = nullptr;

BDD* BDD::getInstance()
{
    if (instance == nullptr)
        instance = new BDD();

    return instance;
}

BDD::BDD() : QObject(nullptr) {
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("192.168.65.167");
    m_db.setDatabaseName("parking");
    m_db.setUserName("root");
    m_db.setPassword("root");
    m_db.open();
}

bool BDD::isConnected() {
    return m_db.isOpen();
}

bool BDD::checkAuthentication(QString login, QString password)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM User WHERE login = :username AND password = :password AND type = 'admin'");
    query.bindValue(":username", login);
    query.bindValue(":password", password);
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        qDebug() << "Authentification réussie ! Type d'utilisateur : admin";
        idenvoie = query.value("id").toInt();
        return true;
    }
    else {
        qDebug() << "Authentification échouée. Veuillez vérifier votre nom d'utilisateur et votre mot de passe.";
        return false;
    }
}

QList<Demande> BDD::getListeDemandes()
{
    QList<Demande> listeDemandes;

    // Exécution de la requête SQL
    if (!m_db.isOpen()) {
        qDebug() << "La connexion à la base de données est fermée.";
        return listeDemandes;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM Demande_Vehicule WHERE statut = 'Traitement en cours'");
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return listeDemandes;
    }

    // Récupération des résultats de la requête et ajout dans la liste
    while (query.next()) {
        Demande demande(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("prenom").toString(),
            query.value("mail").toString(),
            query.value("statut").toString(),
            query.value("immatriculation").toString(),
            query.value("date").toString(),
            query.value("cartegrise").toByteArray());

        listeDemandes.append(demande);
    }
    //qDebug() << "Contenu de cartegrise dans getListeDe$mandes:" << listeDemandes;
    return listeDemandes;
}






void BDD::sendEmail(QString mail, QString nom, QString subject, QString message)
{
    QString fromEmail = "noreply.parking.lapro@gmail.com";
    QString fromName = "Noreply";
    QString toEmail = mail;
    QString toName = nom;

    QUrl url("http://127.0.0.1:3000/sendmail");

    QJsonObject jsonObject;
    jsonObject.insert("senderEmail", fromEmail);
    jsonObject.insert("senderName", fromName);
    jsonObject.insert("destEmail", toEmail);
    jsonObject.insert("destName", toName);
    jsonObject.insert("subject", subject);
    jsonObject.insert("message", message);

    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = manager->post(request, jsonData);
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Email envoyé avec succès.";
        }
        else {
            qDebug() << "Échec de l'envoi de l'email:" << reply->errorString();
        }
        reply->deleteLater();
        });
}




bool BDD::EchangeMessage(int id, QString message)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO `Message` (`id`, `id_demande`, `id_user`, `contenu`) VALUES (NULL, :id, :idenvoie, :message)");
    query.bindValue(":message", message); // Remplacez "Nouveau statut" par le statut souhaité
    query.bindValue(":id", id);
    query.bindValue(":idenvoie", 20);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    else {
        qDebug() << "Changement effectué";
        return true;
    }
    return false;
}


bool BDD::acceptDemande(int id)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE Demande_Vehicule SET statut = :statuts WHERE id = :id");
    query.bindValue(":statuts", "Validee"); // Remplacez "Nouveau statut" par le statut souhaité
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    else {
        qDebug() << "Changement effectué";
        return true;
    }
}

bool BDD::refuserDemande(int id)
{
    QSqlQuery query(m_db);

    // Début de la transaction
    if (!m_db.transaction()) {
        qDebug() << "Erreur lors du début de la transaction :" << m_db.lastError().text();
        return false;
    }

    // Suppression des enregistrements dans la table Message liés à l'id_demande
    query.prepare("DELETE FROM Message WHERE id_demande = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression des messages :" << query.lastError().text();
        m_db.rollback();
        return false;
    }

    // Suppression de l'enregistrement dans la table Demande_Vehicule
    query.prepare("DELETE FROM Demande_Vehicule WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de la demande de véhicule :" << query.lastError().text();
        m_db.rollback();
        return false;
    }

    // Commit de la transaction
    if (!m_db.commit()) {
        qDebug() << "Erreur lors de la validation de la transaction :" << m_db.lastError().text();
        return false;
    }

    qDebug() << "La demande a été refusée avec succès";
    return true;
}

bool BDD::attenteDemande(int id)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE `Demande_Vehicule` SET `statut` = 'Informations demandees' WHERE `Demande_Vehicule`.`id` = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    else {
        // Envoyer un e-mail de notification de refus de la demande
        
        qDebug() << "Changement effectué";
        return true;
    }
    return false;
}

