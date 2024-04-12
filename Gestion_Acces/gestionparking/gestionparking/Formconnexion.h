#ifndef FORMCONNEXION_H
#define FORMCONNEXION_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

class Formconnexion : public QMainWindow {
    Q_OBJECT
public:
    explicit Formconnexion(QWidget* parent = nullptr);

private slots:
    void message(); // Slot pour gérer la tentative de connexion

private:
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
};

#endif // FORMCONNEXION_H
