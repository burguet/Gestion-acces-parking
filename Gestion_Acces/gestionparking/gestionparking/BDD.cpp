#include "BDD.h"
#include <QCoreApplication>


BDD* BDD::instance = nullptr;

BDD* BDD::getInstance()
{
    if (instance == nullptr)
        instance = new BDD();

    return instance;
}

BDD::BDD() {
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
            query.value("nomFichierCarteGrise").toString(),
            query.value("cartegrise").toByteArray());

        listeDemandes.append(demande);
    }
    //qDebug() << "Contenu de cartegrise dans getListeDe$mandes:" << listeDemandes;
    return listeDemandes;
}



void BDD::sendEmail(const QString& recipient, const QString& subject, const QString& body)
{
    

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
    query.prepare("DELETE FROM Demande_Vehicule WHERE `Demande_Vehicule`.`id` = :id");
    query.bindValue(":id", id);

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
        sendEmail("burgetlucas@gmail.com", "Demande refusée", "Votre demande a été refusée.");
        qDebug() << "Changement effectué";
        return true;
    }
    return false;
}
