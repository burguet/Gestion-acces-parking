#include "Formconnexion.h"
#include "User.h"

Formconnexion::Formconnexion(QWidget* parent)
    : QMainWindow(parent)
{
    // Créer les widgets nécessaires
    QLabel* usernameLabel = new QLabel("Nom d'utilisateur:");
    QLabel* passwordLabel = new QLabel("Mot de passe:");
    usernameLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    QPushButton* loginButton = new QPushButton("Se connecter");

    // Configuration du mot de passe comme champ de mot de passe
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Créer un layout pour organiser les widgets
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    // Créer un widget pour contenir le layout
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    // Définir le widget central de la fenêtre principale
    setCentralWidget(centralWidget);

    // Connecter le signal de clic du bouton de connexion au slot de gestion de la connexion
    connect(loginButton, &QPushButton::clicked, this, &Formconnexion::message);
}

void Formconnexion::message()
{
    // Récupérer le nom d'utilisateur et le mot de passe entrés par l'utilisateur
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // Créer un objet User avec les informations d'identification
    User user(username, password, "admin"); // Vous pouvez ajuster le type d'utilisateur selon vos besoins

    // Appeler la fonction de connexion sur l'objet User
    if (user.connexion())
    {
        hide();
    }
    else
    {
        QMessageBox(QMessageBox::Icon::Warning, "Attention", "Password ou login incorrect", QMessageBox::Button::Ok, this).exec();
    }
    
}
