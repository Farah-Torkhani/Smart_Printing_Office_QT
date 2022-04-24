#include "date_fin.h"
#include "commandes.h"
#include "ui_date_fin.h"

#include <QTimer>
QTimer *timerrSetDate = new QTimer();


Date_fin::Date_fin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Date_fin)
{
    ui->setupUi(this);

    connect(timerrSetDate, SIGNAL(timeout()), this, SLOT(setDate()));
    timerrSetDate->start(100);
}

Date_fin::~Date_fin()
{
    delete ui;
}


void Date_fin::setDate()
{
    QString descreption="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);




     int commandeInfo = c.dateFin(idCommande);

     QString dif;
     ui->dateFin->setText(QString::number(commandeInfo));
     ui->dateFin->setReadOnly(true);

     timerrSetDate->stop();
}
