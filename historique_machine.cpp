#include "historique_machine.h"
#include "ui_historique_machine.h"
#include "machine_fonction.h"

#include <QLabel>
#include <QtDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTimer>
#include <QLabel>

QVBoxLayout layouttt ;
QTimer timerH;//refresh historique

Historique_machine::Historique_machine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Historique_machine)
{
    ui->setupUi(this);
    ui->scrollArea->setWidget( ui->scrollAreaContents );
    ui->scrollAreaContents ->setLayout( &layouttt );

    refreshHistorique();
    connect(&timerH, SIGNAL(timeout()), this, SLOT(refreshHistorique()));
    timerH.start(100);
}

Historique_machine::~Historique_machine()
{
    delete ui;
}


void Historique_machine::refreshHistorique()
{
    while(!layouttt.isEmpty()){
        QLayoutItem* item = layouttt.itemAt(0);
        layouttt.removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
    }

    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);


    QSqlQuery historiqueList = m.afficherHistorique(machineId) ;
    qDebug() << "machineId ="<< machineId ;
    while (historiqueList.next()) {
        QLabel *l = new QLabel();
        l->setText(historiqueList.value(0).toString());
        qDebug() << "machinevalue ="<< historiqueList.value(0).toString() ;
//        l->setText("test");
        l->setMinimumHeight(40);
        layouttt.addWidget( l );
    }
  //  timerH.stop();
}

void Historique_machine::reject()
{
    disconnect(&timerH, SIGNAL(timeout()), this, SLOT(refreshMessageList()));
//    QDialog::reject();

    this->hide();
}
