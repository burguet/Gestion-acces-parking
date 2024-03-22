#include "FormGestion.h"

Formgestion::Formgestion(QWidget* parent) : QWidget(parent) {
    // Créer les boutons
    button1 = new QPushButton("Accepter");
    button2 = new QPushButton("Refuser");
    button3 = new QPushButton("Incomplete");

    // Créer le tableau avec 5 lignes et 3 colonnes
    tableWidget = new QTableWidget(5, 3);
    QStringList headers;
    headers << "Colonne 1" << "Colonne 2" << "Colonne 3";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Créer un layout vertical pour organiser les widgets
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(tableWidget);

    // Définir le layout pour cette fenêtre
    setLayout(layout);
}
