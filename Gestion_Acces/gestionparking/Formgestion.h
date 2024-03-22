#ifndef FORMGESTION_H
#define FORMGESTION_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

class Formgestion : public QWidget {
    Q_OBJECT
public:
    explicit Formgestion(QWidget* parent = nullptr);

private:
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QTableWidget* tableWidget;
};

#endif // FORMGESTION_H
