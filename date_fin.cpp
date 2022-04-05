#include "date_fin.h"
#include "commandes.h"
#include "ui_date_fin.h"


#include <QTimer>
QTimer *timerr = new QTimer();


Date_fin::Date_fin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Date_fin)
{
    ui->setupUi(this);

    connect(timerr, SIGNAL(timeout()), this, SLOT(setDate()));
    timerr->start(500);
}

Date_fin::~Date_fin()
{
    delete ui;
}


void Date_fin::setDate()
{
    QString descreption="";
    QString etat="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinemp=0;
    int cinclient=0;

    Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur,cinemp,cinclient);




     int commandeInfo = c.dateFin(idCommande);

     QString dif;
     ui->dateFin->setText(QString::number(commandeInfo));
     ui->dateFin->setReadOnly(true);

}
