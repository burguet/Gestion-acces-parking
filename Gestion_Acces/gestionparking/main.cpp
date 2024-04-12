#include "Formconnexion.h"
#include "BDD.h" // Inclure le fichier d'en-tête de la classe BDD
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Formconnexion w;
    w.show();
    return a.exec();
}