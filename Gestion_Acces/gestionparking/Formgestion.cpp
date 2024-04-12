#include "Formgestion.h"
#include"BDD.h"

Formgestion::Formgestion(QWidget* parent) : QWidget(parent) {
    // Créer les boutons
    button1 = new QPushButton("Accepter");
    button2 = new QPushButton("Refuser");
    button3 = new QPushButton("Incomplete");
    button4 = new QPushButton("deconnexion");

    // Créer le tableau avec 5 lignes et 9 colonnes
    tableWidget = new QTableWidget(5, 7);
    QStringList headers;
    headers << "Nom" << "Prenom" << "Mail" << "statut" << "immatriculation" << "date" << "cartegrise";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Créer un layout vertical pour organiser les widgets
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
   
    layout->addWidget(tableWidget);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Définir le layout pour cette fenêtre
    setLayout(layout);

    // Connecter le signal "clicked" de chaque bouton à la fonction boutonClique()
    connect(button1, &QPushButton::clicked, this, &Formgestion::Accepter);
    connect(button2, &QPushButton::clicked, this, &Formgestion::Refuser);
    connect(button3, &QPushButton::clicked, this, &Formgestion::Incomplete);
    connect(button4, &QPushButton::clicked, this, &Formgestion::deconnexion);
    // Connecter le signal cellDoubleClicked du tableau à la méthode cellDoubleClicked
    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &Formgestion::cellDoubleClicked);
    chargerDonnees();

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Formgestion::Accepter()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton == button1) {
        QItemSelectionModel* select = tableWidget->selectionModel();
        if (select != nullptr)
        {
            QModelIndexList selection = select->selectedRows();
            if (selection.size() == 1)
            {
                int row = selection[0].row();
                // Récupérer l'ID de la demande sélectionner
                user.Accept(demandes[row]); // Supposons que la fonction Accept prend un int comme argument
                chargerDonnees();
            }
        }
    }
}

void Formgestion::Refuser()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton == button2) {
        QItemSelectionModel* select = tableWidget->selectionModel();
        if (select != nullptr)
        {
            QModelIndexList selection = select->selectedRows();
            if (selection.size() == 1)
            {
                int row = selection[0].row();
                // Récupérer l'ID de la demande sélectionner
                user.Refuser(demandes[row]); // Supposons que la fonction refuse prend un int comme argument
                chargerDonnees();
            }
        }
    }
}

void Formgestion::Incomplete()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton == button3) {
        QItemSelectionModel* select = tableWidget->selectionModel();
        if (select != nullptr)
        {
            QModelIndexList selection = select->selectedRows();
            if (selection.size() == 1)
            {
                int row = selection[0].row();
                // Récupérer l'ID de la demande sélectionner
                user.Incomplete(demandes[row]); // Supposons que la fonction refuse prend un int comme argument
                chargerDonnees();
            }
        }
    }
}

void Formgestion::deconnexion()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton == button4) {
        close();
    }
}

void Formgestion::chargerDonnees() {
    // Appel à la fonction getListeDemandes de la classe User
    demandes = user.getListeDemandes();

    // Effacer les données existantes du tableau
    tableWidget->clearContents();

    // Définir le nombre de lignes du tableau en fonction du nombre de demandes
    int nombreDemandes = demandes.size();
    tableWidget->setRowCount(nombreDemandes);

    QList<QString> keyOrder;
    keyOrder.push_back("nom");
    keyOrder.push_back("prenom");
    keyOrder.push_back("mail");
    keyOrder.push_back("statut");
    keyOrder.push_back("immatriculation");
    keyOrder.push_back("date");
    keyOrder.push_back("cartegrise");

    // Afficher les données dans le tableau
    for (int i = 0; i < nombreDemandes; ++i) {
        Demande d = demandes[i];
        int col = 0; // Utiliser une variable pour suivre la colonne
        
        QTableWidgetItem* item2 = new QTableWidgetItem(d.nom);
        tableWidget->setItem(i, col++, item2); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item3 = new QTableWidgetItem(d.prenom);
        tableWidget->setItem(i, col++, item3); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item4 = new QTableWidgetItem(d.mail);
        tableWidget->setItem(i, col++, item4); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item5 = new QTableWidgetItem(d.status);
        tableWidget->setItem(i, col++, item5); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item6 = new QTableWidgetItem(d.immatriculation);
        tableWidget->setItem(i, col++, item6); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item7 = new QTableWidgetItem(d.date);
        tableWidget->setItem(i, col++, item7); // Utiliser col pour incrémenter la colonne

        QTableWidgetItem* item = new QTableWidgetItem(d.nomFichierCarteGrise);
        tableWidget->setItem(i, col++, item); // Utiliser col pour incrémenter la colonne
        
    }
}

void Formgestion::cellDoubleClicked(int row, int column) {
    // Vérifier si la cellule double-cliquée correspond à la colonne de la carte grise
    if (column == 6) { // Assurez-vous que 6 est l'index correct de la colonne de la carte grise
        QByteArray imageData = demandes[row].carteGrise;
        qDebug() << "Contenu de cartebrise dans cellDoubleClicked:" << imageData;
        // Convertir les données binaires en une image JPEG
        QImage image = QImage::fromData(imageData, "JPEG");

        // Afficher la taille de l'image dans la console pour vérifier si elle est correcte
        qDebug() << "Taille de l'image: " << image.size();

        // Vérifier si l'image est vide
        if (image.isNull()) {
            qDebug() << "Image non chargée correctement";
            return;
        }

        // Afficher l'image dans une nouvelle fenêtre de dialogue
        QMessageBox msgBox;
        msgBox.setWindowTitle("Image de la carte grise");
        msgBox.setIconPixmap(QPixmap::fromImage(image));
        msgBox.exec();
    }
}