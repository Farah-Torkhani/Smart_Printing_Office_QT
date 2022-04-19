#include "arduino_client.h"
#include "ui_arduino_client.h"
#include "arduino_sms_row_table.h"
#include "client_fonction.h"
#include "arduino.h"
#include "callard.h"
#include <QVBoxLayout>
#include <QScrollArea>

#include <QTimer>

#include <stdio.h>
#include <string.h>

QVBoxLayout *layouttEmp = new QVBoxLayout();
QTimer *timerListEmpArd = new QTimer();//refresh
QTimer *timerTestCall = new QTimer();//

QString num1="",num2="";

//QString pch="",pch2="";
//char *numm2=NULL;
//char * pch=NULL ,*pch2=NULL;
//QString pch="",pch2="";


Arduino_client::Arduino_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arduino_client)
{
    ui->setupUi(this);

//    int ret=A.connect_arduino(); // lancer la connexion à arduino
//    switch(ret){
//    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
//        break;
//    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
//       break;
//    case(-1):qDebug() << "arduino is not available";
//    }

    //scroll area
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents ->setLayout( layouttEmp );
    //end scroll area

    connect(timerListEmpArd, SIGNAL(timeout()), this, SLOT(on_refreshEmpArdBtn_clicked()));
    timerListEmpArd->start(100);

   // QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(test_call())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

   // connect(timerTestCall, SIGNAL(timeout()), this, SLOT(test_call()));
   // timerTestCall->start(1500);
}

Arduino_client::~Arduino_client()
{
    delete ui;
}


void Arduino_sms_row_table::smsEmpBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int cinEmp = buttonSender->whatsThis().toInt();

    QString nomClient="";//
    Client_fonction c(nomClient);
    QSqlQuery empInfo= c.afficherEmpArd(cinEmp);
    empInfo.next();

    QString tellEmp = empInfo.value(0).toString();


//    QString dataSend = "55516530";
        QString dataSend = tellEmp;
        B.write_to_arduino(dataSend.toStdString().c_str());

    B.write_to_arduino("m"); //envoyer 'm' à arduino



        if(testBtnSerial == 0)
        {
            B.connect_arduino(); // lancer la connexion à arduino
            if(( dataSend.length()>=8) && (dataSend != "55516530") )
            B.write_to_arduino("s");
            testBtnSerial = 1;
        }
        else if(testBtnSerial == 1)
        {
            testBtnSerial = 0;
            B.close_arduino();
        }




//B.close_arduino();

}


void Arduino_sms_row_table::callEmpBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int cinEmp = buttonSender->whatsThis().toInt();

    QString nomClient="";//
    Client_fonction c(nomClient);
    QSqlQuery empInfo= c.afficherEmpArd(cinEmp);
    empInfo.next();

    QString tellEmp = empInfo.value(0).toString();


//    QString dataSend = "55516530";
        QString dataSend = tellEmp;
        B.write_to_arduino(dataSend.toStdString().c_str());

    B.write_to_arduino("m"); //envoyer 'm' à arduino


   // B.close_arduino();

    if(testBtnSerial == 0)
    {
        B.connect_arduino(); // lancer la connexion à arduino
        if(( dataSend.length()>=8) && (dataSend != "55516530") )
        B.write_to_arduino("c");

       // QString dataSend = "26840169";
   //     B.write_to_arduino(dataSend.toStdString().c_str());
        testBtnSerial = 1;

//        data=B.read_from_arduino();
//            qDebug() << data;
    }
    else if(testBtnSerial == 1)
    {
        testBtnSerial = 0;
        B.close_arduino();
    }


  //  data=A.read_from_arduino();
  //  qDebug() << data;


}



void Arduino_client::test_call()
{/*
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    data=A.read_from_arduino();
    qDebug() << data;


    if(strstr(data,"AT+CLCC\r\n\r\n")!=NULL)
    {
        pch = strstr (data,"\"");
      //  pch2 = strstr (data,"");
        qDebug() <<pch<<  "****"  <<pch2;
      //p= strstr(ch1,ch2);
    }


    if(strstr(data,"\r\n\r\nOK")!=NULL)
    {
        pch2 = strstr (data,"");
        qDebug() <<pch<<  "****"  <<pch2;
      //p= strstr(ch1,ch2);

    }

    if(data == "\r\nRING\r\n")
    {
        qDebug() << "vous aves un appel!";
        A.write_to_arduino("a");

        data=A.read_from_arduino();
        qDebug() << data;


    //    timerTestCall->stop();
    }
    //qDebug()<<"numeroooo=" << pch+pch2;
    QString concat=pch+pch2;
  //  QString numberCall = concat.substr(1, 3);
    QString numberCall=concat.mid(1,8);
    qDebug()<<"numeroooo=" << numberCall;


    //if(data == "\r\nNO CARRIER\r\n")
    if( (data == "\r\nRING\r\n\r\nNO CARRIER\r\n") || (data == "\r\nNO CARRIER\r\n") )
    {
        //quitter

         numberCall="aa";
         qDebug()<<"numeroooo=**********************" << numberCall;

    }

//if( (numberCall.length()<6)  )
//{
//    test=0;
//}
    if( (numberCall.length()>6)  )
    {

        timerTestCall->stop();
        CallArd *call = new CallArd();
       // call->setCinClient(cinClient);
        call->call_numIn = numberCall;

        call->show();
    }

    if(numberCall.length()<6)
    {
        //
    }

  //  if(data == "1")
  //  {
     //   ui->niveauEncre->setText("cv"); // si les données reçues de arduino via la liaison série sont sup à ...
  //  }
  //  else
  //  {
       // ui->niveauEncre->setText("faible");   // si les données reçues de arduino via la liaison série sont inf à ...
  //  }

    timerTestCall->stop();

    */
}





void Arduino_client::on_refreshEmpArdBtn_clicked()
{

    while(!layouttEmp->isEmpty()){
    QLayoutItem* item = layouttEmp->itemAt(0);
    layouttEmp->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }


    QString nomClient="";
    Client_fonction c(nomClient);




    QSqlQuery clientList = c.afficherEmp_pourAlerte();
    while (clientList.next()) {
        Arduino_sms_row_table *row = new Arduino_sms_row_table(ui->scrollArea,clientList.value(0).toString(),clientList.value(1).toString(),clientList.value(2).toString(),clientList.value(6).toString(),clientList.value(3).toString());
        row->setMinimumHeight(34);
        layouttEmp->addWidget( row );
    }





timerListEmpArd->stop();
}



void Arduino_client::reject()
{
    Arduino_sms_row_table aa("ddd");
    aa.B.close_arduino();


    A.close_arduino();
    disconnect(timerListEmpArd, SIGNAL(timeout()), this, SLOT(on_refreshEmpArdBtn_clicked()));

    QDialog::reject();

    //this->hide();
    this->close();
}



