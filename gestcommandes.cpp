#include "gestcommandes.h"
#include "ui_gestcommandes.h"
#include "commandes.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "commandes_row_table.h"
#include <QDebug>
#include <QTimer>
#include <qtranslator.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>

#include "descreption_commande.h"
#include "date_fin.h"
#include <imprimer_recu.h>

int id = 0;
QTranslator T;
QTimer *timerCommande = new QTimer();//setFormulaire
QTimer *timer2Commande = new QTimer();//reflesh
QTimer *timer3Commande = new QTimer(); //recher
QTimer *timer4Commande = new QTimer(); //stat

QVBoxLayout *layouttCommande = new QVBoxLayout();
Gestcommandes::Gestcommandes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestcommandes)
{



    ui->setupUi(this);

    ui->commande_combo->addItem("par défaut");
    ui->commande_combo->addItem("date");
    ui->commande_combo->addItem("etat");
    ui->commande_combo->addItem("quantiteCouleur");
    QString descreption="";
    QString etat="";
    QString quantiteCouleur="";
    QString quantiteSansCouleur="";


    ui->scrollAreaCommande->setWidget( ui->scrollAreaWidgetContentsCommande );
     ui->scrollAreaWidgetContentsCommande ->setLayout( layouttCommande );
   //end scroll area

    connect(timerCommande, SIGNAL(timeout()), this, SLOT(setCommandeFormulaire()));
    //timer->start(500);

    connect(timer2Commande, SIGNAL(timeout()), this, SLOT(on_refreshCommandeBtn_clicked()));
    timer2Commande->start(100);


    connect(timer3Commande, SIGNAL(timeout()), this, SLOT(on_search_commandeBtn_clicked()));
//    timer3->start(3000);


        //afficherStatistique();
        connect(timer4Commande, SIGNAL(timeout()), this, SLOT(on_statCommande_clicked()));
        timer4Commande->start(100);

        //set cin client comboBox
        setCinClient_combo();

}

Gestcommandes::~Gestcommandes()
{
    delete ui;
}



void Gestcommandes::on_ajouter_commande_clicked()
{
   int cinClient=ui->selectCinClient->currentText().toInt();
    QString descreption=ui->descreption->toPlainText();
    int quantiteCouleur=ui->Qc->text().toInt();
    QString quantiteSansCouleur=ui->Qsc->text();

    QString date_fin=ui->dateFinCommande->text();
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinClient, date_fin);


     bool test_ajout = c.ajouterCommandes();
    if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        timer2Commande->start(100);
        timer4Commande->start(100);
    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("non effectue\n"
                                               "click cancel to exit."),QMessageBox::Cancel);

}


void commandes_row_table::deleteBtn_clicked()
{


QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
int commandesid = buttonSender->whatsThis().toInt();


    QString descreption="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);

    bool test = c.supprimerCommandes(commandesid);

     if(test){
         QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("Commmande deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
         timer2Commande->start(100);
         timer4Commande->start(100);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("Commmande not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
     }
}


void Gestcommandes::on_modifier_commande_clicked()
{
    QString descreption=ui->descreption->toPlainText();
    int quantiteCouleur=ui->Qc->text().toInt();
    QString quantiteSansCouleur=ui->Qsc->text();
    int cinClient=ui->selectCinClient->currentText().toInt();
    QString date_Fin=ui->dateFinCommande->text();

Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinClient, date_Fin);

 bool test = c.modifierCommande(id);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("Commande updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2Commande->start(100);
        on_clear_commande_clicked();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Commande not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}


void Gestcommandes::on_refreshCommandeBtn_clicked()
{
    while(!layouttCommande->isEmpty()){
    QLayoutItem* item = layouttCommande->itemAt(0);
    layouttCommande->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }


    QString descreption="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);


    QString trieOption = ui->commande_combo->currentText();
    QSqlQuery commandeList = c.triCommande(trieOption);
    while (commandeList.next()) {
         commandes_row_table *row = new commandes_row_table(ui->scrollAreaCommande,commandeList.value(2).toString().split("T")[0],commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(0).toString(), commandeList.value(8).toString());
         row->setMinimumHeight(34);
         layouttCommande->addWidget( row );
    }

    QStringList CompletionList;

     CompletionList = c.rechercherCommandes();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->chercher_commande->setCompleter(stringCompleter);

    timer2Commande->stop();
}



void Gestcommandes::setCommandeFormulaire()
{
    if(id != -999999999){

        QString descreption="";
        int quantiteCouleur=0;
        QString quantiteSansCouleur="";
        int cinclient=0;
        QString date_Fin="";
        Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);

        QSqlQuery commandeInfo = c.afficherCommande(id);

        commandeInfo.next();

        ui->descreption->setPlainText(commandeInfo.value(1).toString());
        ui->Qc->setText(commandeInfo.value(3).toString());
        ui->Qsc->setText(commandeInfo.value(4).toString());
        ui->dateFinCommande->setDate(commandeInfo.value(7).toDate());
        ui->selectCinClient->setCurrentText(commandeInfo.value(6).toString());

        bool inputsFocus = ui->selectCinClient->hasFocus() || ui->descreption->hasFocus() || ui->dateFinCommande->hasFocus() || ui->Qc->hasFocus() || ui->Qsc->hasFocus() ;
        if(inputsFocus){
            timerCommande->stop();
        }
    }
}



void commandes_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    id = buttonSender->whatsThis().toInt();

    timerCommande->start(100);
}




void Gestcommandes::on_clear_commande_clicked()
{
    timerCommande->stop();
    ui->descreption->setPlainText("");
    ui->Qc->setText("");
    ui->Qsc->setText("");

    QDate cd = QDate::currentDate();
    ui->dateFinCommande->setDate(cd);
    ui->selectCinClient->setCurrentText("");
}




void Gestcommandes::on_search_commandeBtn_clicked()
{
    QString chaine_c=ui->chercher_commande->text();

    if(chaine_c !="")
    {
        timer2Commande->stop();
        timer3Commande->start(100);


     while(!layouttCommande->isEmpty()){
     QLayoutItem* item = layouttCommande->itemAt(0);
     layouttCommande->removeItem(item);
     QWidget* widgett = item->widget();
     if(widgett)
         {
             delete widgett;
         }
     }


     QString descreption="";
     int quantiteCouleur=0;
     QString quantiteSansCouleur="";
     int cinclient=0;
     QString date_Fin="";
     Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);


     QSqlQuery commandeList = c.rechercherCommande(chaine_c);
     while (commandeList.next()) {
            commandes_row_table *row = new commandes_row_table(ui->scrollAreaCommande,commandeList.value(2).toString().split("T")[0],commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(0).toString(), commandeList.value(8).toString());
          row->setMinimumHeight(34);
          layouttCommande->addWidget( row );
     }

     }
    else
    {
        timer3Commande->stop();
        timer2Commande->start(100);

    }

}

void Gestcommandes::on_chercher_commande_textChanged(const QString &arg1)
{
      on_search_commandeBtn_clicked();
}


void Gestcommandes::on_statCommande_clicked()
{

    QBarSet *set1 = new QBarSet("Nombre de commandes par mois");

    QString descreption="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(descreption,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);


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
           //    chart->setBackgroundVisible(false);

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
            chartView->show();

            timer4Commande->stop();


}


void commandes_row_table::imprimerBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
        int idComm = buttonSender->whatsThis().toInt();
        imprimer_recu *recu = new imprimer_recu();
        recu->idComm = idComm;
        qDebug() << idComm;

        recu->show();
}


void Gestcommandes::setCinClient_combo()
{

   QSqlQueryModel * modal=new QSqlQueryModel();

    QSqlQuery query;
     query.prepare("select cinClient from clients ");
    query.exec();
    modal->setQuery(query);
    ui->selectCinClient->setModel(modal);

}


void commandes_row_table::etatBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int idComm = buttonSender->whatsThis().toInt();


        Date_fin *date = new Date_fin();
        date ->idCommande = idComm;

        date->show();
}


void Gestcommandes::on_trie_commande_clicked()
{
    timer2Commande->start(100);
}


void commandes_row_table::descreptionBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int idComm = buttonSender->whatsThis().toInt();


    Descreption_commande *desc = new Descreption_commande();
        desc->idCommande= idComm;

        desc->show();
}


void commandes_row_table::repaireBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int idComm = buttonSender->whatsThis().toInt();

    QString desc="";
    int quantiteCouleur=0;
    QString quantiteSansCouleur="";
    int cinclient=0;
    QString date_Fin="";
    Commandes c(desc,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);
    c.repaireDateFinCommande(idComm);
      timer2Commande->start(100);
}
