#include "clients.h"
#include "client_fonction.h"
#include "ui_clients.h"
#include "duscene.h"
#include "client_row_table.h"


#include "email.h"

#include <QVBoxLayout>
#include <QScrollArea>

#include <QTimer>
#include <QDate>


#include <QCoreApplication>
#include <QDebug>
#include <QSslSocket> //To use QSslSocket Class
int test = 0;
int i =0;
int j=0;

QVBoxLayout *layoutt = new QVBoxLayout();

int cinClient = 0;
QTimer *timer = new QTimer();//setFormulaire
QTimer *timer2 = new QTimer();//refresh
QTimer *timer3 = new QTimer(); //recher
QTimer *timer4 = new QTimer(); //stat


Clients::Clients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clients)
{
    ui->setupUi(this);
//*******************trie options**************************
    ui->clien_combo->addItem("par défaut");
        ui->clien_combo->addItem("nom");
        ui->clien_combo->addItem("prenom");
        ui->clien_combo->addItem("date_ajout");
//*******************trie options***************************


//*******************controle de saisie*****************************
    ui->Cin_f->setValidator(new QIntValidator (0,99999999,ui->Cin_f));
    ui->Nom_f->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
    ui->Prenom_f->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
    ui->Phone_f->setValidator(new QIntValidator (0,99999999,ui->Phone_f));

//*******************controle de saisie*****************************

    //scroll area
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents ->setLayout( layoutt );

    int cinClient = 0 ;
    QString nomClient="";
    QString prenomClient="";
    QString emailClient="";
    int telClient = 0;


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

    //Client_fonction cl ;


    QSqlQuery clientList = c.afficherCilents();
    while (clientList.next()) {
        Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(), clientList.value(1).toString(), clientList.value(2).toString(), clientList.value(3).toString(), clientList.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

    //end scroll area



    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(100);

    connect(timer3, SIGNAL(timeout()), this, SLOT(on_search_client_clicked()));
//    timer3->start(3000);



    mScene = new DuScene(this);
    ui->graphicsView->setScene(mScene);


  //  afficherStatistique();

        connect(timer4, SIGNAL(timeout()), this, SLOT(on_stat_clicked()));
        timer4->start(500);








}


Clients::~Clients()
{
    delete ui;
}

void Clients::on_ajouter_client_clicked()
{
    int cinClient=ui->Cin_f->text().toInt();
    QString nomClient=ui->Nom_f->text();
    QString prenomClient=ui->Prenom_f->text();
    QString emailClient=ui->Email_f->text();
    int telClient=ui->Phone_f->text().toInt();



    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );
    c.is_email_valid(emailClient);

     if(c.is_email_valid(emailClient))
     {
           bool test_ajout = c.ajouter();

        if(test_ajout)
        {
            QMessageBox::information(nullptr,QObject::tr("ok"),
                                   QObject::tr(" effectue\n"
                                               "click cancel to exit."),QMessageBox::Cancel);
            timer2->start(100);
            timer4->start(100);
            on_clear_client_clicked();
        }
        else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                       QObject::tr("non effectue\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);

     }
     else  QMessageBox::critical(nullptr,QObject::tr("invalid email"),
                                    QObject::tr("invalid email\n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);


}


void Client_row_table::deleteBtn_clicked()
{
    i=1;

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int cinClient = buttonSender->whatsThis().toInt();
//    qDebug()<< cin;

    QString nomClient="";
    QString prenomClient="";
    QString emailClient="";
    int telClient = 0;


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

//    Client_fonction c;

    bool test = c.supprimerClient(cinClient);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("Client deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        timer4->start(100);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("Client not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
//    connect(timer4, SIGNAL(timeout()), this, SLOT(afficherStatistique()));
//    timer4->start(3000);

}


void Clients::on_refreshBtn_clicked()
{

    while(!layoutt->isEmpty()){
    QLayoutItem* item = layoutt->itemAt(0);
    layoutt->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }


    int cinClient=ui->Cin_f->text().toInt();
    QString nomClient=ui->Nom_f->text();
    QString prenomClient=ui->Prenom_f->text();
    QString emailClient=ui->Email_f->text();
    int telClient=ui->Phone_f->text().toInt();


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );


    QString triOption = ui->clien_combo->currentText();

    QSqlQuery clientList = c.trierCilent(triOption);
    while (clientList.next()) {
        Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(),clientList.value(1).toString(),clientList.value(2).toString(),clientList.value(3).toString(),clientList.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }
    QStringList CompletionList;
   // CompletionList <<"ali" <<"ahmed" << "amor" << "arij" << "assma" ;
  //  CompletionList <<"nabil" ;
     CompletionList = c.rechercherClients();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->search_input->setCompleter(stringCompleter);


    //openSSl version

    qDebug()<<QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();





timer2->stop();
}

void Clients::on_modifier_client_clicked()
{
    int cinClient = ui->Cin_f->text().toInt();
    QString nomClient = ui->Nom_f->text();
    QString prenomClient = ui->Prenom_f->text();
    QString emailClient = ui->Email_f->text();
    int telClient = ui->Phone_f->text().toInt();

    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );
    bool test = c.modifierClient();

    if(test){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("Client updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        on_clear_client_clicked();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Client not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}



void Clients::setFormulaire()
{
    if(cinClient != -999999999){

        //int cinClient=0;
        QString nomClient="";
        QString prenomClient="";
        QString emailClient="";
        int telClient=0;


        Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

        QSqlQuery clientInfo = c.afficherCilent(cinClient);
        clientInfo.next();
        ui->Cin_f->setText(clientInfo.value(0).toString());
        ui->Nom_f->setText(clientInfo.value(1).toString());
        ui->Prenom_f->setText(clientInfo.value(2).toString());
        ui->Email_f->setText(clientInfo.value(3).toString());
        ui->Phone_f->setText(clientInfo.value(4).toString());

        bool inputsFocus = ui->Cin_f->hasFocus() || ui->Nom_f->hasFocus() || ui->Prenom_f->hasFocus() || ui->Email_f->hasFocus() || ui->Phone_f->hasFocus() ;
        if(inputsFocus){
            timer->stop();
        }
    }
}



void Client_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    cinClient = buttonSender->whatsThis().toInt();

    QString nomClient="";
    QString prenomClient="";
    QString emailClient="";
    int telClient=0;


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

    timer->start(100);
}

void Clients::on_clear_client_clicked()
{
    timer->stop();
    ui->Cin_f->setText("");
    ui->Nom_f->setText("");
    ui->Prenom_f->setText("");
    ui->Email_f->setText("");
    ui->Phone_f->setText("");
}

void Clients::on_pdfBtn_clicked()
{
    QPdfWriter pdf("C:/Users/ALI/Desktop/Pdf/Liste_Client.pdf");

   QPainter painter(&pdf);
   int i = 4100;
   const QImage image(":/Resources/client_img/logo.png");
               const QPoint imageCoordinates(155,0);
               int width1 = 1600;
               int height1 = 1600;
               QImage img=image.scaled(width1,height1);
               painter.drawImage(imageCoordinates, img );


          QColor dateColor(0x4a5bcf);
          painter.setPen(dateColor);

          painter.setFont(QFont("Montserrat SemiBold", 11));
          QDate cd = QDate::currentDate();
          painter.drawText(8400,250,cd.toString("Tunis"));
          painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

          QColor titleColor(0x341763);
          painter.setPen(titleColor);
          painter.setFont(QFont("Montserrat SemiBold", 25));

          painter.drawText(3000,2700,"Liste des clients");

          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          //painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3300,9400,500);

          painter.setFont(QFont("Montserrat SemiBold", 10));

          painter.drawText(500,3600,"Cin");
          painter.drawText(2000,3600,"Nom");
          painter.drawText(3300,3600,"Prenom");
          painter.drawText(4500,3600,"Email");
          painter.drawText(7500,3600,"Phone");
          painter.setFont(QFont("Montserrat", 10));
          painter.drawRect(100,3300,9400,9000);

          QSqlQuery query;
          query.prepare("select * from clients");
          query.exec();
          int y=4300;
          while (query.next())
          {
              painter.drawLine(100,y,9490,y);
              y+=500;
              painter.drawText(500,i,query.value(0).toString());
              painter.drawText(2000,i,query.value(1).toString());
              painter.drawText(3300,i,query.value(2).toString());
              painter.drawText(4500,i,query.value(3).toString());
              painter.drawText(7500,i,query.value(4).toString());

             i = i + 500;
          }
          QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
          QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void Clients::on_search_client_clicked()
{

       QString chaine_c=ui->search_input->text();

       if(chaine_c !="")
       {
           timer2->stop();
           timer3->start(100);


        while(!layoutt->isEmpty()){
        QLayoutItem* item = layoutt->itemAt(0);
        layoutt->removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
        }


        int cinClient=0;
        QString nomClient="";
        QString prenomClient="";
        QString emailClient="";
        int telClient=0;


        Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );



        QSqlQuery clientList = c.rechercherClient(chaine_c);
        while (clientList.next()) {
            Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(),clientList.value(1).toString(),clientList.value(2).toString(),clientList.value(3).toString(),clientList.value(4).toString());
            row->setMinimumHeight(34);
            layoutt->addWidget( row );
        }

        }
       else
       {
           timer3->stop();
           timer2->start(100);

       }

timer3->stop();

}

void Clients::on_search_input_textChanged(const QString &arg1)
{
    on_search_client_clicked();
}


