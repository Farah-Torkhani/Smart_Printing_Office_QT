#include "arduino_produit.h"
#include "ui_arduino_produit.h"
#include "fonctionproduits.h"
QVBoxLayout *layoutttP = new QVBoxLayout();
QTimer *timerP10 = new QTimer();

Arduino_Produit::Arduino_Produit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arduino_Produit)
{
    ui->setupUi(this);
    ui->scrollArea_P2->setWidget( ui->scrollAreaContents_P2 );

    ui->scrollAreaContents_P2 ->setLayout( layoutttP );

    connect(timerP10, SIGNAL(timeout()), this, SLOT(refreshHistorique()));
    timerP10->start(100);



}

Arduino_Produit::~Arduino_Produit()
{
    delete ui;
}
void Arduino_Produit::refreshHistorique()
{
    while(!layoutttP->isEmpty()){
        QLayoutItem* item = layoutttP->itemAt(0);
        layoutttP->removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
    }

    Produits m;


    QSqlQuery historiqueList = m.afficherHistorique() ;
    while (historiqueList.next()) {
        QLabel *l = new QLabel();
        l->setText(historiqueList.value(0).toString());
        l->setMinimumHeight(40);
        layoutttP->addWidget( l );
    }
    timerP10->stop();
}
