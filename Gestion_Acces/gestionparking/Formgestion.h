#ifndef FORMGESTION_H
#define FORMGESTION_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QByteArray>
#include <QFile>
#include <QMessageBox>
#include "User.h"
#include "BDD.h"

class Formgestion : public QWidget {
    Q_OBJECT
public:
    explicit Formgestion(QWidget* parent = nullptr);

private slots:
    void Accepter();
    void Refuser();
    void Incomplete();
    void deconnexion();
    void chargerDonnees();
    void cellDoubleClicked(int row, int column);

private:
    QList<Demande> demandes;

    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;

    QTableWidget* tableWidget;
    User user;
};

#endif // FORMGESTION_H
