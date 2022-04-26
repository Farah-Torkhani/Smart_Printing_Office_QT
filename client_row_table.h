#ifndef CLIENT_ROW_TABLE_H
#define CLIENT_ROW_TABLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "arduino.h"

class Client_row_table : public QLabel
{
    Q_OBJECT
public:
    explicit Client_row_table(QWidget *parent,QString cinClient, QString nomClient, QString prenomClient, QString emailClient, QString telClient);

    QLabel *row_container = new QLabel(this);
    QLabel *nom_label = new QLabel();
    QLabel *prenom_label = new QLabel();
    QLabel *cin_label = new QLabel();
    QLabel *email_label = new QLabel();
    QLabel *tell_label = new QLabel();
    QPushButton *editBtn = new QPushButton();
    QPushButton *emailBtn = new QPushButton();
    QPushButton *deleteBtn = new QPushButton();
    QPushButton *smsBtn = new QPushButton();
    QPushButton *callBtn = new QPushButton();

private slots:
    void deleteBtn_clicked();
    void updateBtn_clicked();
    void emailBtn_clicked();
    void smsBtn_clicked();
//    void callBtn_clicked();


private:

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

};

#endif // CLIENT_ROW_TABLE_H
