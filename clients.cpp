#include "clients.h"
#include "client_fonction.h"
#include "ui_clients.h"
#include "duscene.h"
#include "client_row_table.h"

#include <QVBoxLayout>
#include <QScrollArea>

#include <QDebug>
#include <QTimer>

QVBoxLayout *layoutt = new QVBoxLayout();

int cinClient = 0;
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();


Clients::Clients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clients)
{
    ui->setupUi(this);

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
    int i=0;
    while (clientList.next()) {

   // while (i<10) {
 //       i++;
        Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(), "clientList.value(1).toString()","clientList.value(2).toString()","clientList.value(3).toString()","clientList.value(4).toString()");
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

    //end scroll area

    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(3000);



    mScene = new DuScene(this);
    ui->graphicsView->setScene(mScene);


        //statistique
            QBarSet *set0 = new QBarSet("Youssef");
            QBarSet *set1 = new QBarSet("Nombre de clients par mois");
            QBarSet *set2 = new QBarSet("Farah");
            *set1 << 20 << 10 << 40 << 15 << 20 << 30 << 100 << 40 << 10 << 77 << 91 << 13;

            *set2 << 20 << 10 << 40 << 15 << 20 << 30 << 10 << 40 << 10 << 17 << 11 << 13;
            *set0 << 20 << 10 << 40 << 15 << 20 << 30 << 10 << 40 << 10 << 17 << 11 << 13;





                QBarSeries *series = new QBarSeries();

                series->append(set1);
                QColor color(0x6568F3);
                set1->setColor(color);


                QChart *chart = new QChart();
                    chart->addSeries(series);
                    chart->setTitle("");
                    chart->setAnimationOptions(QChart::SeriesAnimations);
                    chart->setBackgroundVisible(false);


                    QStringList categories;
                    categories << "Jan" << "Fiv" << "Mar" << "Avr" << "Mai" << "Juin" << "Jui" <<"Aou" << "sep" << "Oct" << "Nov" << "Dec" ;
                    QBarCategoryAxis *axis = new QBarCategoryAxis();
                    axis->append(categories);
                    chart->createDefaultAxes();
                    chart->setAxisX(axis, series);


                    chart->setVisible(true);
                    chart->legend()->setAlignment(Qt::AlignBottom);




                    QChartView *chartView = new QChartView(chart);

                    chartView->setRenderHint(QPainter::Antialiasing);
                    QPalette pal = qApp->palette();
                    pal.setColor(QPalette::WindowText, QRgb(0x6568F3));
                    pal.setColor(QPalette::Window, QRgb(0x6568F3));
                    qApp->setPalette(pal);

                    chartView->setMaximumWidth(650);
                    chartView->setMaximumHeight(290);


                    chartView->setParent(ui->horizontalFrame);

             //end statistique

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
    bool test_ajout = c.ajouter();

    if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("non effectue\n"
                                               "click cancel to exit."),QMessageBox::Cancel);


    while(!layoutt->isEmpty()){
    QLayoutItem* item = layoutt->itemAt(0);
    layoutt->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }


//    Employees e;
    QSqlQuery clientList = c.afficherCilents();
    while (clientList.next()) {
        Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(),clientList.value(1).toString(),clientList.value(2).toString(),clientList.value(3).toString(),clientList.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }


}


void Client_row_table::deleteBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int cinClient = buttonSender->whatsThis().toInt();
//    qDebug()<< cin;

    QString nomClient="";
    QString prenomClient="";
    QString emailClient="";
    int telClient = 0;


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

//    Client_fonction c;
    c.supprimerClient(cinClient);


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


    QSqlQuery clientList = c.afficherCilents();
    while (clientList.next()) {
        Client_row_table *row = new Client_row_table(ui->scrollArea,clientList.value(0).toString(),clientList.value(1).toString(),clientList.value(2).toString(),clientList.value(3).toString(),clientList.value(4).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

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
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Client updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
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

    timer->start(500);
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
