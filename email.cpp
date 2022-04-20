#include "email.h"
#include "ui_email.h"
#include "client_fonction.h"


#include <QDebug>
#include <QTimer>

QTimer *timer_email = new QTimer();

Email::Email(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Email)
{
    ui->setupUi(this);

    setEmail();
    connect(timer_email, SIGNAL(timeout()), this, SLOT(setEmail()));
    timer_email->start(100);
}

Email::~Email()
{
    delete ui;
}


void Email::sendMail()
{
    Smtp* smtp = new Smtp("printini.contact.tn@gmail.com", "printini123", "smtp.gmail.com", 465);
   // connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("iLearn.contact.tn@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

    QMessageBox::information(nullptr,QObject::tr("ok"),
                           QObject::tr(" effectue\n"
                                       "Message sent!"),QMessageBox::Cancel);
}

void Email::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "Message sent!"),QMessageBox::Cancel);
     //   QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void Email::on_sendMailBtn_clicked()
{
    sendMail();
    //connect(ui->sendMailBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    ui->subject->setText("");
    ui->msg->setPlainText("");

}




//***********************************************************************************************
void Email::setEmail()
{
    QString nomClient="";

    Client_fonction c(nomClient);

    qDebug() << "cinClient=" <<cinClient;




    QSqlQuery clientInfo = c.afficherCilent(cinClient);

    clientInfo.next();

    ui->rcpt->setText(clientInfo.value(3).toString());
    ui->rcpt->setReadOnly(true);

    timer_email->stop();
}

