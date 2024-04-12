#include "Formconnexion.h"
#include "User.h"

Formconnexion::Formconnexion(QWidget* parent)
    : QMainWindow(parent)
{
    // Cr�er les widgets n�cessaires
    QLabel* usernameLabel = new QLabel("Nom d'utilisateur:");
    QLabel* passwordLabel = new QLabel("Mot de passe:");
    usernameLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    QPushButton* loginButton = new QPushButton("Se connecter");

    // Configuration du mot de passe comme champ de mot de passe
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Cr�er un layout pour organiser les widgets
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(loginButton);

    // Cr�er un widget pour contenir le layout
    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    // D�finir le widget central de la fen�tre principale
    setCentralWidget(centralWidget);

    // Connecter le signal de clic du bouton de connexion au slot de gestion de la connexion
    connect(loginButton, &QPushButton::clicked, this, &Formconnexion::message);
}

void Formconnexion::message()
{
    // R�cup�rer le nom d'utilisateur et le mot de passe entr�s par l'utilisateur
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // Cr�er un objet User avec les informations d'identification
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
