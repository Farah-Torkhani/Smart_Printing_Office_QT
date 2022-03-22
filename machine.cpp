#include "machine.h"
#include "machine_fonction.h"
#include "ui_machine.h"
#include "duscene.h"
#include "machine_row_table.h"

#include <QVBoxLayout>
#include <QScrollArea>

#include <QDebug>

QVBoxLayout *layoutt = new QVBoxLayout();

machine::machine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::machine)
{
    ui->setupUi(this);

    //scroll area
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents ->setLayout( layoutt );

    int machineID = 0 ;
    QString nomMachine="";
    QString etat="";
    int prix = 0;


    machine_fonction c( machineID, nomMachine,  etat,  prix );

    //machine_fonction cl ;

    //testttttttttttttttt

    //testttttttttttttttttttt

    QSqlQuery machineList = c.affichermachine();
    int i=0;
    while (machineList.next()) {

   // while (i<10) {
        i++;
        machine_row_table *row = new machine_row_table(ui->scrollArea,machineList.value(0).toString(), "machineList.value(1).toString()","machineList.value(2).toString()","machineList.value(3).toString()");
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

    //end scroll area


    mScene = new DuScene(this);
    ui->graphicsView->setScene(mScene);


        //statistique
            QBarSet *set0 = new QBarSet("HP");
            QBarSet *set1 = new QBarSet("Nombre de machine par mois");
            QBarSet *set2 = new QBarSet("LG");
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

                    chartView->setMaximumWidth(550);
                    chartView->setMaximumHeight(290);


                    chartView->setParent(ui->horizontalFrame);

             //end statistique

}


machine::~machine()
{
    delete ui;
}

void machine::on_ajouter_machine_clicked()
{
    int machineID=ui->id_f->text().toInt();
    QString nomMachine=ui->Nom_f->text();
    QString etat=ui->etat_f->text();
    int prix=ui->prix_f->text().toInt();


    machine_fonction c( machineID, nomMachine,  etat,  prix );
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


//    machine e;
    QSqlQuery machineList = c.affichermachine();
    while (machineList.next()) {
        machine_row_table *row = new machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }


}


void machine_row_table::deleteBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineID = buttonSender->whatsThis().toInt();
//    qDebug()<< cin;

    QString nomMachine="";
    QString etat="";
    int prix = 0;


    machine_fonction c( machineID, nomMachine,  etat,  prix );

//    machine_fonction c;
    c.supprimermachine(machineID);

}


void machine::on_refreshBtn_clicked()
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


    int machineID=ui->id_f->text().toInt();
    QString nomMachine=ui->Nom_f->text();
    QString etat=ui->etat_f->text();
    int prix=ui->prix_f->text().toInt();


    machine_fonction c( machineID, nomMachine,  etat, prix );


    QSqlQuery machineList = c.affichermachine();
    while (machineList.next()) {
        machine_row_table *row = new machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

}
