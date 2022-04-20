#include "sms.h"
#include "ui_sms.h"
#include <QDesktopServices>

#include "client_fonction.h"

#include <QDebug>
#include <QTimer>

QTimer *timer_smsInfo = new QTimer();


Sms::Sms(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sms)
{
    ui->setupUi(this);

    connect(timer_smsInfo, SIGNAL(timeout()), this, SLOT(setSmsInfo()));
    timer_smsInfo->start(100);
}

Sms::~Sms()
{
    delete ui;
}

void Sms::on_sendSmsBtn_clicked()
{
    QString myMobile = ui->numSms->text();
    QString mySms = ui->msgSms->toPlainText();
    QString mySender = "TunSMS";

    QDateTime now = QDateTime::currentDateTime();
    QString myDate = now.toString();

    QString myTime = "14:38";


    QString url="", key="",mobile="", sms="", sender="", date="", heure="";
    url="https://www.tunisiesms.tn/client/Api/Api.aspx?";
    key="fct=sms&key=8AyZ/Lm/Xo/-/XuoYDrY7SAH24WFS9LNNnNdBX5rq4LKdwxHF9uRijDREh9y5//v7fSG59iW9vUhwpNdmQgfkfm8l/-/7YM9IRM4";
    mobile="&mobile=216"+myMobile;
    sms ="&sms="+mySms;
    sender="&sender=TunSMS Test";
    date="&date="+myDate;
    heure="&heure=13:50";

    QDesktopServices::openUrl(QUrl(url+key+mobile+sms+sender+date+heure));

}


void Sms::setSmsInfo()
{
    QString nomClient="";

    Client_fonction c(nomClient);

    qDebug() << "cinClient=" <<cinClient;

    QSqlQuery clientInfo = c.afficherCilent(cinClient);

    clientInfo.next();

    QString destSms;
    destSms = clientInfo.value(1).toString()+" "+clientInfo.value(2).toString();

    ui->destSms->setText(destSms);
    ui->destSms->setReadOnly(true);

    ui->numSms->setText(clientInfo.value(4).toString());
    ui->numSms->setReadOnly(true);

    timer_smsInfo->stop();
}
