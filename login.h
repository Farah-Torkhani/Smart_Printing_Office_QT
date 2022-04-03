#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "employees.h"
#include <QVBoxLayout>
#include <QTimer>
#include "arduino.h"

extern Employees currentEmp;
//extern QVBoxLayout *layoutt;
//extern QTimer *timerRefresh;
//extern QTimer *timerFormulaire;
//extern QTimer *timerCherche;
//extern QTimer *timerAccountInfo;
//extern QTimer *timerCurrentEmp;


namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();
    void getCardUid();
    void authRFID();

private:
    Ui::Login *ui;
    QByteArray data; // variable contenant les données reçu
    Arduino A; // objet temporaire
};


#endif // LOGIN_H
