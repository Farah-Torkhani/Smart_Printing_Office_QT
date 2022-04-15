#include "login.h"
#include "ui_login.h"
#include "gestionemp.h"
#include "employees.h"
#include <QDebug>
#include <QMessageBox>
#include <integration.h>


Employees currentEmp;
QString cardUID="";
QString test="";
int yo=1;


QTimer *timerAuthRfid = new QTimer();

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(getCardUid())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

//    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(timerAuthRfid, SIGNAL(timeout()), this, SLOT(authRFID()));
yo=1;

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
                //GestionEmp gEmp;
                Integration integ;
                integ.show();
                QEventLoop loop;

                disconnect(timerAuthRfid, SIGNAL(timeout()), this, SLOT(authRFID()));
                yo=0;

                connect(&integ, SIGNAL(closed()), &loop, SLOT(quit()));

                loop.exec();
        }else {
            QMessageBox::critical(nullptr, QObject::tr("login status"),QObject::tr("email or password are incorrect.\nClick Cancel to exit."), QMessageBox::Cancel);
        }


    }

}

void Login::getCardUid()
{
    if(yo==1){
        timerAuthRfid->start(100);
    }
    data=A.read_from_arduino();
    //test = data;

    //test = "";
    if(test.length() <11){
        test += data;
    }else{
        test="";
    }

    if(test.length() ==11){
//        qDebug()<<test;
        cardUID = test;
        test="";
    }
//qDebug()<<test;
}

void Login::authRFID()
{
//    qDebug()<<cardUID;
    Employees e(cardUID);
    qDebug()<<e.getCard();

    if(e.authEmpCardRfid()){
        disconnect(timerAuthRfid, SIGNAL(timeout()), this, SLOT(authRFID()));
        yo=0;
        QSqlQuery emp = e.afficherEmpByCardNum(e.getCard());
        emp.next();
        qDebug()<< emp.value(0).toString();
        Employees test(emp.value(0).toInt(), emp.value(2).toString(), emp.value(1).toString(), emp.value(7).toString(), emp.value(8).toString(), emp.value(9).toString(), emp.value(3).toInt(), emp.value(8).toInt(), emp.value(6).toString());
        currentEmp = test;
            this->close();
            //GestionEmp gEmp;
            Integration integ;
            integ.show();
            QEventLoop loop;
            connect(&integ, SIGNAL(closed()), &loop, SLOT(quit()));


            loop.exec();

    }else {
        QMessageBox::critical(nullptr, QObject::tr("login status"),QObject::tr("Card not valid.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    timerAuthRfid->stop();
}
