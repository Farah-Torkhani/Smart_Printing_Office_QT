#ifndef ARDUINO_SMS_ROW_TABLE_H
#define ARDUINO_SMS_ROW_TABLE_H
#include "arduino.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Arduino_sms_row_table : public QLabel
{
    Q_OBJECT
public:
    Arduino B; // objet temporaire
    QByteArray data; // variable contenant les données reçues

    explicit Arduino_sms_row_table(QWidget *parent,QString cinEmp, QString nomEmp, QString prenomEmp, QString roleEmp, QString telEmp);

    Arduino_sms_row_table(QString test);
    QLabel *row_container = new QLabel(this);
    QLabel *nom_label = new QLabel();
    QLabel *prenom_label = new QLabel();
    QLabel *role_label = new QLabel();
    QLabel *tell_label = new QLabel();
    QPushButton *smsBtn = new QPushButton();
    QPushButton *callBtn = new QPushButton();
    QPushButton *deconnectBtn = new QPushButton();


    int testBtnSerial=0;

private slots:
    void smsEmpBtn_clicked();
    void callEmpBtn_clicked();
    void deconnectEmpBtn_clicked();

private:

//    QByteArray data; // variable contenant les données reçues

   // Arduino A; // objet temporaire
};

#endif // ARDUINO_SMS_ROW_TABLE_H
