#include "gestcommandes.h"
#include "ui_gestcommandes.h"
#include "commandes.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "commandes_row_table.h"
#include <QDebug>
#include <QTimer>

int id = 0;
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();



QVBoxLayout *layoutt = new QVBoxLayout();
Gestcommandes::Gestcommandes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gestcommandes)
{
    ui->setupUi(this);
QString descreption="";
QString etat="";
QString quantiteCouleur="";
QString quantiteSansCouleur="";

ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
 ui->scrollAreaWidgetContents ->setLayout( layoutt );

Commandes c("","","","");

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
    timer2->start(3000);



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
    categories << "Jan" << "Fev" << "Mar" << "Avr" << "Mai" << "Juin" << "Jui" <<"Aou" << "sep" << "Oct" << "Nov" << "Dec" ;
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

    chartView->setMaximumWidth(550);
    chartView->setMaximumHeight(290);

    chartView->setParent(ui->horizontalFrame);
}

Gestcommandes::~Gestcommandes()
{
    delete ui;
}



void Gestcommandes::on_ajouter_clicked()
{
   QString descreption=ui->descreption->text();
   QString etat=ui->eta->text();
 QString quantiteCouleur=ui->Qc->text();
 QString quantiteSansCouleur=ui->Qsc->text();

Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);
 bool test_ajout = c.ajouterCommandes();
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
QString quantiteCouleur="";
QString quantiteSansCouleur="";
Commandes c( descreption,etat,quantiteCouleur,  quantiteSansCouleur );
c.supprimerCommandes(commandesid);



}


void Gestcommandes::on_modifier_commande_clicked()
{
    QString descreption=ui->descreption->text();
    QString etat=ui->eta->text();
  QString quantiteCouleur=ui->Qc->text();
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
    QString quantiteCouleur=ui->Qc->text();
    QString quantiteSansCouleur=ui->Qsc->text();

    Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


    QSqlQuery commandeList = c.afficherCommande();
    while (commandeList.next()) {
         commandes_row_table *row = new commandes_row_table(ui->scrollArea,commandeList.value(1).toString(),commandeList.value(2).toString(),commandeList.value(3).toString(),commandeList.value(4).toString(),commandeList.value(5).toString(),commandeList.value(0).toString());
         row->setMinimumHeight(34);
         layoutt->addWidget( row );
    }
}



void Gestcommandes::setFormulaire()
{
    if(id != -999999999){

        QString descreption="";
        QString etat="";
        QString quantiteCouleur="";
        QString quantiteSansCouleur="";

        Commandes c(descreption,etat,quantiteCouleur,quantiteSansCouleur);


        QSqlQuery commandeInfo = c.afficherCommande(id);

        commandeInfo.next();

        ui->descreption->setText(commandeInfo.value(1).toString());
        ui->eta->setText(commandeInfo.value(2).toString());
        ui->Qc->setText(commandeInfo.value(3).toString());
        ui->Qsc->setText(commandeInfo.value(4).toString());

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
