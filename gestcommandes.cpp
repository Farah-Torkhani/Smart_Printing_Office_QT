#include "gestcommandes.h"
#include "ui_gestcommandes.h"
#include "commandes.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "commandes_row_table.h"
#include <QDebug>
#include <QTimer>
#include <qtranslator.h>

int id = 0;
QTranslator T;
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();
QTimer *timer3 = new QTimer(); //recher
QTimer *timer4 = new QTimer(); //stat


QVBoxLayout *layoutt = new QVBoxLayout();
Gestcommandes::Gestcommandes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestcommandes)
{



    ui->setupUi(this);
    ui->comboBox_7->addItem("par défaut");
        ui->comboBox_7->addItem("date");
        ui->comboBox_7->addItem("etat");
        ui->comboBox_7->addItem("quantiteCouleur");
QString descreption="";
QString etat="";
QString quantiteCouleur="";
QString quantiteSansCouleur="";

ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
 ui->scrollAreaWidgetContents ->setLayout( layoutt );

Commandes c("","",0,"");

 QSqlQuery commandeList = c.afficherCommande();

    while (commandeList.next()) {

      commandes_row_table *row = new commandes_row_table(ui->scrollArea,commandeList.value(1).toString(),commandeList.value(2).toString(),commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(5).toString(),commandeList.value(0).toString());
       row->setMinimumHeight(34);
       layoutt->addWidget( row );
   }

   //end scroll area

    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(500);


    connect(timer3, SIGNAL(timeout()), this, SLOT(on_search_commandeBtn_clicked()));
//    timer3->start(3000);


  //  afficherStatistique();

        connect(timer4, SIGNAL(timeout()), this, SLOT(on_statCommande_clicked()));
        timer4->start(500);



}

Gestcommandes::~Gestcommandes()
{
    delete ui;
}



void Gestcommandes::on_ajouter_clicked()
{
   QString descreption=ui->descreption->text();
   QString etat=ui->eta->text();
 int quantiteCouleur=ui->Qc->text().toInt();
 QString quantiteSansCouleur=ui->Qsc->text();

Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);
 bool test_ajout = c.ajouterCommandes();
 if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        timer4->start(100);
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
 QSqlQuery commandeList = c.afficherCommande();
   while (commandeList.next()) {
      commandes_row_table *row = new commandes_row_table(ui->scrollArea,commandeList.value(1).toString(),commandeList.value(2).toString(),commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(5).toString(),commandeList.value(0).toString());
       row->setMinimumHeight(34);
       layoutt->addWidget( row );
   }


}


void commandes_row_table::deleteBtn_clicked()
{


QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
int commandesid = buttonSender->whatsThis().toInt();


QString descreption="";
QString etat="";
int quantiteCouleur=0;
QString quantiteSansCouleur="";
Commandes c( descreption,etat,quantiteCouleur,  quantiteSansCouleur );
c.supprimerCommandes(commandesid);

timer4->start(100);

}


void Gestcommandes::on_modifier_commande_clicked()
{
    QString descreption=ui->descreption->text();
    QString etat=ui->eta->text();
  int quantiteCouleur=ui->Qc->text().toInt();
  QString quantiteSansCouleur=ui->Qsc->text();

 Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


 bool test = c.modifierCommande(id);

    if(test){
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void Gestcommandes::on_refreshBtn_clicked()
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


    QString descreption=ui->descreption->text();
    QString etat=ui->eta->text();
    int quantiteCouleur=ui->Qc->text().toInt();
    QString quantiteSansCouleur=ui->Qsc->text();

    Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


    QString trieOption = ui->comboBox_7->currentText();
    QSqlQuery commandeList = c.triCommande(trieOption);
    while (commandeList.next()) {
         commandes_row_table *row = new commandes_row_table(ui->scrollArea,commandeList.value(1).toString(),commandeList.value(2).toString().split("T")[0],commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(5).toString(),commandeList.value(0).toString());
         row->setMinimumHeight(34);
         layoutt->addWidget( row );
    }

    QStringList CompletionList;

     CompletionList = c.rechercherCommandes();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->chercher_commande->setCompleter(stringCompleter);

}



void Gestcommandes::setFormulaire()
{
    if(id != -999999999){

        QString descreption="";
        QString etat="";
        int quantiteCouleur=0;
        QString quantiteSansCouleur="";

        Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


        QSqlQuery commandeInfo = c.afficherCommande(id);

        commandeInfo.next();

        ui->descreption->setText(commandeInfo.value(1).toString());
        ui->eta->setText(commandeInfo.value(3).toString());
        ui->Qc->setText(commandeInfo.value(4).toString());
        ui->Qsc->setText(commandeInfo.value(5).toString());

        bool inputsFocus = ui->descreption->hasFocus() || ui->eta->hasFocus() || ui->Qc->hasFocus() || ui->Qsc->hasFocus() ;
        if(inputsFocus){
            timer->stop();
        }
    }
}



void commandes_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    id = buttonSender->whatsThis().toInt();

    timer->start(500);
}




void Gestcommandes::on_clear_commande_clicked()
{
    timer->stop();
    ui->descreption->setText("");
    ui->eta->setText("");
    ui->Qc->setText("");
    ui->Qsc->setText("");
}




void Gestcommandes::on_search_commandeBtn_clicked()
{
    QString chaine_c=ui->chercher_commande->text();

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


     QString descreption="";
     QString etat="";
     int quantiteCouleur=0;
     QString quantiteSansCouleur="";

     Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


     QSqlQuery commandeList = c.rechercherCommande(chaine_c);
     while (commandeList.next()) {
          commandes_row_table *row = new commandes_row_table(ui->scrollArea,commandeList.value(1).toString(),commandeList.value(2).toString().split("T")[0],commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(5).toString(),commandeList.value(0).toString());
          row->setMinimumHeight(34);
          layoutt->addWidget( row );
     }

     }
    else
    {
        timer3->stop();
        timer2->start(100);

    }

}

void Gestcommandes::on_chercher_commande_textChanged(const QString &arg1)
{
      on_search_commandeBtn_clicked();
}





//********************************afficher statistique graphe***************************************************


void Gestcommandes::on_statCommande_clicked()
{

    QBarSet *set1 = new QBarSet("Nombre de commandes par mois");

    QString descreption="";
    QString etat="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";

    Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);

//        set1->insert(1,c.statistiqueCilents(2));
    *set1 <<  c.statistiqueCommande(1)
          <<  c.statistiqueCommande(2)
          <<  c.statistiqueCommande(3)
          <<  c.statistiqueCommande(4)
          << c.statistiqueCommande(5)
          << c.statistiqueCommande(6)
          << c.statistiqueCommande(7)
          << c.statistiqueCommande(8)
          << c.statistiqueCommande(9)
          << c.statistiqueCommande(10)
          << c.statistiqueCommande(11)
          << c.statistiqueCommande(12) ;

    //    qDebug()<< c.statistiqueCommande(2);



        QBarSeries *series = new QBarSeries();

       // set1->remove(0);
       // series->deleteLater();
        //series->append(set1);

        //series->deleteLater();

        series->append(set1);

        QColor color(0x6568F3);
        set1->setColor(color);


        QChart *chart = new QChart();




            chart->addSeries(series);
            chart->setTitle("");
          //  chart->setAnimationOptions(QChart::SeriesAnimations);

               QColor bgColor(0xF4DCD3);
               chart->setBackgroundBrush(QBrush(QColor(bgColor)));

               chart->setBackgroundVisible(true);
               //i=0;


           //    chart->setBackgroundVisible(false);




            QStringList categories;
            categories << "Jan" << "Fiv" << "Mar" << "Avr" << "Mai" << "Juin" << "Jui" <<"Aou" << "sep" << "Oct" << "Nov" << "Dec" ;
            QBarCategoryAxis *axis = new QBarCategoryAxis();


            axis->append(categories);

            chart->createDefaultAxes();
            chart->setAxisX(axis, series);


            chart->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);



          //  series->remove(0);//*****************
          //  chart->removeAxis(axis);//******************
           // chart->removeSeries(series);//****************

            QChartView *chartView = new QChartView(chart);

            chartView->setRenderHint(QPainter::Antialiasing);
            QPalette pal = qApp->palette();
            pal.setColor(QPalette::WindowText, QRgb(0x6568F3));
            pal.setColor(QPalette::Window, QRgb(0x6568F3));
            qApp->setPalette(pal);

            chartView->setMaximumWidth(650);
            chartView->setMaximumHeight(290);



            chartView->setParent(ui->horizontalFrame);
         //   chartView->update();
            chartView->show();

                if(NULL != chart){
                       series->remove(0);

                    }
timer4->stop();

//                chart->removeSeries(series);

//                delete chartView;
//

//                chart->update();


     //end statistique


}




