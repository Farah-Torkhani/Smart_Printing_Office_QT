#include "login.h"
#include "ui_login.h"
#include "gestionemp.h"
#include "employees.h"
#include <QDebug>
#include <QMessageBox>


Employees currentEmp;
//QVBoxLayout *layoutt = new QVBoxLayout();
//QTimer *timerRefresh = new QTimer();
//QTimer *timerFormulaire = new QTimer();
//QTimer *timerCherche = new QTimer();
//QTimer *timerAccountInfo = new QTimer();
//QTimer *timerCurrentEmp = new QTimer();

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QString email = ui->login_email->text();
    QString password = ui->login_password->text();

    if(email == "" && password == ""){
        QMessageBox::critical(nullptr, QObject::tr("login status"),QObject::tr("please fill the email and password input.\nClick Cancel to exit."), QMessageBox::Cancel);
    }else {
        Employees e(email.toLower(),password);

    //    qDebug()<< e.authEmp();
        if(e.authEmp()){
            QSqlQuery emp = e.afficherEmp(email.toLower());
            emp.next();
            qDebug()<< emp.value(0).toString();
            Employees test(emp.value(0).toInt(), emp.value(2).toString(), emp.value(1).toString(), emp.value(7).toString(), emp.value(8).toString(), emp.value(9).toString(), emp.value(3).toInt(), emp.value(8).toInt(), emp.value(6).toString());
            currentEmp = test;
                this->close();
                GestionEmp gEmp;
                gEmp.show();
                QEventLoop loop;

                connect(&gEmp, SIGNAL(closed()), &loop, SLOT(quit()));

                loop.exec();
        }else {
            QMessageBox::critical(nullptr, QObject::tr("login status"),QObject::tr("email or password are incorrect.\nClick Cancel to exit."), QMessageBox::Cancel);
        }


    }


}
