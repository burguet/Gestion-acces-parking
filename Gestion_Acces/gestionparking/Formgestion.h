#ifndef FORMGESTION_H
#define FORMGESTION_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include "User.h"

class Formgestion : public QWidget {
    Q_OBJECT

public:
    Formgestion(QWidget* parent = nullptr);

private slots:
    void Accepter();
    void Refuser();
    void Incomplete();
    void deconnexion();
    void cellDoubleClicked(int row, int column);

private:
    void chargerDonnees();

    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    QTableWidget* tableWidget;
    QLineEdit* lineEdit; // Added QLineEdit member
    User user;
    QList<Demande> demandes;
};

#endif // FORMGESTION_H
