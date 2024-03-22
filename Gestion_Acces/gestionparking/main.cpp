#include "Formconnexion.h"
#include "User.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Formconnexion w;
    w.show();
    return a.exec();
}
