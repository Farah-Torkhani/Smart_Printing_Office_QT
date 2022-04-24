#include "descreption_commande.h"
#include "ui_descreption_commande.h"
#include <QSqlQuery>

#include <QTimer>
QTimer *timerSetDescreption = new QTimer();



Descreption_commande::Descreption_commande(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Descreption_commande)
{
    ui->setupUi(this);

    connect(timerSetDescreption, SIGNAL(timeout()), this, SLOT(setDescreptionInfo()));
    timerSetDescreption->start(100);
}

Descreption_commande::~Descreption_commande()
{
    delete ui;
}



void Descreption_commande::setDescreptionInfo()
{


    QSqlQuery query;
    query.prepare("select descreption from commandes where Commandeid=:Commandeid");
    query.bindValue(":Commandeid",idCommande);

    query.exec();
    query.next();
    ui->desc_textEdit->setPlainText(query.value(0).toString());
    ui->desc_textEdit->setReadOnly(true);


    timerSetDescreption->stop();

}
