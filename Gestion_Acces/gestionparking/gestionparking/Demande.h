#pragma once
#include <qstring.h>


struct Demande
{
    int id;
    QString nom;
    QString prenom;
    QString mail;
    QString status;
    QString immatriculation;
    QString date;
    QString nomFichierCarteGrise;
    QByteArray carteGrise;

    Demande(const int id ,const QString& nom, const QString& prenom, const QString& mail,
        const QString& status, const QString& immatriculation,
        const QString& date, const QString nomFichierCarteGrise, const QByteArray& carteGrise) :
        id(id), nom(nom), prenom(prenom), mail(mail), status(status),
        immatriculation(immatriculation), date(date), nomFichierCarteGrise(nomFichierCarteGrise), carteGrise(carteGrise) {}
};