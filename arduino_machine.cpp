#include "arduino_machine.h"
#include "ui_arduino_machine.h"

#include <QTimer>


QTimer *timerEncre = new QTimer();//niveauEncre
QTimer *timerNomMachine = new QTimer();//nomMach




Arduino_machine::Arduino_machine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arduino_machine)
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
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).

   //  connect(timerEncre, SIGNAL(timeout()), this, SLOT(update_label()));
   //  timerEncre->start(100);

       connect(timerNomMachine, SIGNAL(timeout()), this, SLOT(setNomMachine()));
       timerNomMachine->start(100);

}

Arduino_machine::~Arduino_machine()
{
    delete ui;
}

void Arduino_machine::update_label()
{
    data=A.read_from_arduino();
    qDebug() << data;


    if(data == "1")
    {
        ui->niveauEncre->setText("cv"); // si les données reçues de arduino via la liaison série sont sup à ...
    }
    else
    {

        ui->niveauEncre->setText("faible");   // si les données reçues de arduino via la liaison série sont inf à ...
    }

    timerEncre->stop();
}



void Arduino_machine::on_showLCD_btn_clicked()
{
    QString dataSend = nomMachine;
    A.write_to_arduino(dataSend.toStdString().c_str());

    //A.write_to_arduino("1"); //envoyer 1 à arduino
}

void Arduino_machine::on_mute_btn_clicked()
{
    A.write_to_arduino("0");  //envoyer 0 à arduino
}

void Arduino_machine::on_refreshBtn_clicked()
{
    timerEncre->start(100);
    timerNomMachine->start(100);
}

void Arduino_machine::setNomMachine()
{
    ui->nomMachine->setText(nomMachine);
    timerNomMachine->stop();
}
