#include "callard.h"
#include "ui_callard.h"
#include "arduino.h"


#include "client_fonction.h"

#include <QDebug>
#include <QTimer>

QTimer *timer_numberCallSet = new QTimer();


CallArd::CallArd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallArd)
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

    connect(timer_numberCallSet, SIGNAL(timeout()), this, SLOT(setCallNumberArd()));
    timer_numberCallSet->start(100);
}

CallArd::~CallArd()
{
    delete ui;
}

void CallArd::on_acceptCall_Btn_clicked()
{

    A.write_to_arduino("i");

    data=A.read_from_arduino();
    qDebug() << data;
}

void CallArd::on_CancelCall_Btn_clicked()
{

    A.write_to_arduino("h");

//    data=A.read_from_arduino();
//    qDebug() << data;
}

void CallArd::setCallNumberArd()
{
    QString nomClient="";

    Client_fonction c(nomClient);

  //  call_numIn="55516530";
  //  qDebug() << "numClient=" <<call_numIn.toInt();


   bool test = c.clientExists(call_numIn.toInt());
   if(test == false)
   {
       ui->nomCallArd->setText("Inconnu");
       ui->nomCallArd->setReadOnly(true);
   }

    else
    {
        QSqlQuery clientInfo = c.afficherClientsArd(call_numIn.toInt());

        //QString appelFrom;
        //appelFrom = clientInfo.value(1).toString()+" "+clientInfo.value(2).toString();

        clientInfo.next();
    //    qDebug() << clientInfo.value(1).toString()+" "+clientInfo.value(2).toString();

        ui->nomCallArd->setText(clientInfo.value(0).toString()+" "+clientInfo.value(1).toString());
        ui->nomCallArd->setReadOnly(true);


    }

    ui->numCallArd->setText(call_numIn);
    ui->numCallArd->setReadOnly(true);




    timer_numberCallSet->stop();

}






void CallArd::reject()
{


    A.close_arduino();

    QDialog::reject();

    //this->hide();

    this->close();
}
