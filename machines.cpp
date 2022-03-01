#include "machines.h"
#include "machine_fonction.h"
#include "ui_machines.h"
#include "machine_row_table.h"

#include <QVBoxLayout>
#include <QScrollArea>

#include <QDebug>
#include <QTimer>

QVBoxLayout *layoutt = new QVBoxLayout();

int machineId = 0;
QTimer *timer = new QTimer();
QTimer *timer2 = new QTimer();


Machines::Machines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Machines)
{
    ui->setupUi(this);

    //scroll area
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents ->setLayout( layoutt );


    QString nomMachine="";
    QString machineImg="";
    int prixMachine = 0 ;
    int etatMachine = 0 ;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

    QSqlQuery machineList = m.afficherMachines();
    while (machineList.next()) {

        Machine_row_table *row = new Machine_row_table(ui->scrollArea,machineList.value(0).toString(), machineList.value(1).toString(), machineList.value(2).toString(), machineList.value(3).toString(), machineList.value(4).toString());
        row->setMinimumHeight(64);
        layoutt->addWidget( row );
    }

    //end scroll area
    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(3000);


    //statistique
  /*      QBarSet *set0 = new QBarSet("Youssef");
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

   */      //end statistique

                //***************************************************************
                QPieSeries *series1 = new QPieSeries();
                    series1->append("Machine en bon etat", .80);
                    series1->append("Machine en panne", .20);

                    QPieSlice *slice0 = series1->slices().at(0);
                    slice0->setLabelVisible();

                    QPieSlice *slice1 = series1->slices().at(1);
                    slice1->setExploded();
                    slice1->setLabelVisible();
                    slice1->setPen(QPen(Qt::color1, 0));
                    slice1->setBrush(Qt::color1);



                    QColor color0(0x6568F3);
                    slice0->setColor(color0);

                    QColor color1(0x341763);
                    slice1->setColor(color1);




                    QChart *chart1 = new QChart();
                    chart1->addSeries(series1);
                    chart1->setTitle("Etat des machines");
                    chart1->legend()->hide();
                    chart1->setBackgroundVisible(false);


                    QChartView *chartView1 = new QChartView(chart1);

                    chartView1->setMaximumWidth(500);
                    chartView1->setMaximumHeight(260);
                    chartView1->setParent(ui->circleFrame);
                //-***************************************************************


}

Machines::~Machines()
{
    delete ui;
}





void Machines::on_ajouter_machine_clicked()
{
  //  QString nomMachine="";
  //  QString machineImg="";
  //  int prixMachine = 0 ;
  //  int etatMachine = 0 ;

    QString nomMachine=ui->Nom_f->text();
    QString machineImg=ui->img_f->text();
    int etatMachine=ui->Etat_f->text().toInt();
    int prixMachine=ui->Prix_f->text().toInt();


    Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);
    bool test_ajout = m.ajouter();

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


//    Machines m;
    QSqlQuery machineList = m.afficherMachines();
    while (machineList.next()) {
        Machine_row_table *row = new Machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
        row->setMinimumHeight(64);
        layoutt->addWidget( row );
    }
}


void Machine_row_table::deleteBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineId = buttonSender->whatsThis().toInt();


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);

//
    m.supprimerMachine(machineId);

}

void Machines::on_refreshBtn_clicked()
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


    QString nomMachine=ui->Nom_f->text();
    QString machineImg=ui->img_f->text();
    int etatMachine=ui->Etat_f->text().toInt();
    int prixMachine=ui->Prix_f->text().toInt();


    Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);


    QSqlQuery machineList = m.afficherMachines();
    while (machineList.next()) {
         Machine_row_table *row = new Machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
         row->setMinimumHeight(64);
         layoutt->addWidget( row );
    }

}

void Machines::on_modifier_machine_clicked()
{
    QString nomMachine=ui->Nom_f->text();
    QString machineImg=ui->img_f->text();
    int etatMachine=ui->Etat_f->text().toInt();
    int prixMachine=ui->Prix_f->text().toInt();


    Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);
    bool test = m.modifierMachine(machineId);

    if(test){
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}



void Machines::setFormulaire()
{
    if(machineId != -999999999){

        QString nomMachine="";
        QString machineImg="";
        int etatMachine=0;
        int prixMachine=0;


        Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);

        QSqlQuery machineInfo = m.afficherMachine(machineId);
        machineInfo.next();
        ui->img_f->setText(machineInfo.value(0).toString());
        ui->Nom_f->setText(machineInfo.value(1).toString());
        ui->Etat_f->setText(machineInfo.value(2).toString());
        ui->Prix_f->setText(machineInfo.value(3).toString());

        bool inputsFocus = ui->img_f->hasFocus() || ui->Nom_f->hasFocus() || ui->Etat_f->hasFocus() || ui->Prix_f->hasFocus() ;
        if(inputsFocus){
            timer->stop();
        }
    }
}

void Machine_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    machineId = buttonSender->whatsThis().toInt();

//    QString nomMachine="";
//    QString machineImg="";
//    int etatMachine=0;
//    int prixMachine=0;


//    Machine_fonction m( nomMachine, machineImg,  etatMachine,  prixMachine);

    timer->start(500);
}


void Machines::on_clear_machine_clicked()
{
    timer->stop();
    ui->Nom_f->setText("");
    ui->Etat_f->setText("");
    ui->Prix_f->setText("");
    ui->img_f->setText("");

}
