#include "machines.h"
#include "machine_fonction.h"
#include "ui_machines.h"
#include "machine_row_table.h"
#include "historiques_machine.h"
#include "arduino_machine.h"

#include <QVBoxLayout>
#include <QScrollArea>

#include <QDebug>
#include <QTimer>

#include <QFileInfo>

QVBoxLayout *layoutt = new QVBoxLayout();

int machineId = 0;
QString machineImg ="";
QTimer *timer = new QTimer();//setFormulaire
QTimer *timer2 = new QTimer();//refresh
QTimer *timer3 = new QTimer(); //recher
QTimer *timer4 = new QTimer(); //stat


Machines::Machines(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Machines)
{
    ui->setupUi(this);



    //*******************controle de saisie*****************************
        ui->Prix_f->setValidator(new QIntValidator (0,99999999,ui->Prix_f));
       // ui->Nom_f->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
    //*******************controle de saisie*****************************

    //*******************trie options**************************
            ui->machine_combo->addItem("par défaut");
                ui->machine_combo->addItem("nom");
                ui->machine_combo->addItem("etat");
                ui->machine_combo->addItem("prix");
                ui->machine_combo->addItem("date_achat");
    //*******************trie options***************************


    //scroll area
    ui->scrollArea->setWidget( ui->scrollAreaWidgetContents );
    ui->scrollAreaWidgetContents ->setLayout( layoutt );


    //end scroll area
    connect(timer, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer2->start(100);

    connect(timer3, SIGNAL(timeout()), this, SLOT(on_search_machine_clicked()));
//    timer3->start(3000);


    //  afficherStatistique();

          connect(timer4, SIGNAL(timeout()), this, SLOT(on_statMachine_clicked()));
          timer4->start(500);



}

Machines::~Machines()
{
    delete ui;
}





void Machines::on_ajouter_machine_clicked()
{

    QString nomMachine=ui->Nom_f->text();
    //QString machineImg=ui->img_f->text();
    //int etatMachine=ui->Etat_f->text().toInt();
    int prixMachine=ui->Prix_f->text().toInt();
    int etatMachine;
    if(ui->radioButton_bon->isChecked())
    {
         etatMachine = 1;
    }
    if(ui->radioButton_panne->isChecked())
    {
        etatMachine = 0;
    }


    Machine_fonction m( nomMachine, machineImg, prixMachine, etatMachine);
    bool test_ajout = m.ajouter();

    if(test_ajout)
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr(" effectue\n"
                                           "click cancel to exit."),QMessageBox::Cancel);
        timer2->start(100);
        timer4->start(100);
    }
    else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                   QObject::tr("non effectue\n"
                                               "click cancel to exit."),QMessageBox::Cancel);



}


void Machine_row_table::deleteBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineId = buttonSender->whatsThis().toInt();


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

//
    bool test = m.supprimerMachine(machineId);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("Machine deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        timer4->start(100);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("Machine not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

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
    //int etatMachine=ui->Etat_f->text().toInt();
    int prixMachine=ui->Prix_f->text().toInt();

    int etatMachine;
    if(ui->radioButton_bon->isChecked())
    {
         etatMachine = 1;
    }
    if(ui->radioButton_panne->isChecked())
    {
        etatMachine = 0;
    }

    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);


    QString trieOption = ui->machine_combo->currentText();

    QSqlQuery machineList = m.trierMachines(trieOption);
    //QSqlQuery machineList = m.afficherMachines();
    while (machineList.next()) {
         Machine_row_table *row = new Machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
         row->setMinimumHeight(64);
         layoutt->addWidget( row );
    }

    QStringList CompletionList;
    CompletionList = m.rechercherMachines_completer();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->search_input_machine->setCompleter(stringCompleter);


    timer2->stop();

}

void Machines::on_modifier_machine_clicked()
{
    QString nomMachine=ui->Nom_f->text();
    int prixMachine=ui->Prix_f->text().toInt();

    int etatMachine;
    if(ui->radioButton_bon->isChecked())
    {
         etatMachine = 1;
    }
    if(ui->radioButton_panne->isChecked())
    {
        etatMachine = 0;
    }


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);
    bool test = m.modifierMachine(machineId);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("Machine updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        timer4->start(100);
        on_clear_machine_clicked();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}



void Machines::setFormulaire()
{
    if(machineId != -999999999){

        QString nomMachine="";
        int etatMachine=0;
        int prixMachine=0;


        Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

        QSqlQuery machineInfo = m.afficherMachine(machineId);
        machineInfo.next();
        QPixmap image (machineInfo.value(2).toString());//get image path
        machineImg = machineInfo.value(2).toString();

        ui->lblBkImge->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        image = image.scaled(130,100,Qt::IgnoreAspectRatio,Qt::FastTransformation);

        ui->lblBkImge->setPixmap(image);
        ui->img_f->setText(machineInfo.value(2).toString());
        ui->Nom_f->setText(machineInfo.value(1).toString());
       // ui->Etat_f->setText(machineInfo.value(4).toString());
        etatMachine = machineInfo.value(4).toString().toInt();
                if(etatMachine == 1)
                {
                     ui->radioButton_bon->setChecked(true);
                }
                if(etatMachine == 0)
                {
                    ui->radioButton_panne->setChecked(true);
                }
        ui->Prix_f->setText(machineInfo.value(3).toString());

        bool inputsFocus = ui->img_f->hasFocus() || ui->Nom_f->hasFocus() || ui->Prix_f->hasFocus() ;
        if(inputsFocus){
            timer->stop();
        }
    }
    timer->stop();
}

void Machine_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    machineId = buttonSender->whatsThis().toInt();

    timer->start(100);
}


void Machines::on_clear_machine_clicked()
{
    timer->stop();
    ui->Nom_f->setText("");
    ui->Prix_f->setText("");
    ui->img_f->setText("");
    ui->radioButton_bon->setChecked(true);

    QPixmap image ("");
    ui->lblBkImge->setPixmap(image);
}

void Machines::on_search_machine_clicked()
{
       QString chaine_c=ui->search_input_machine->text();

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



        QString nomMachine="";
        QString machineImg="";
        int etatMachine=0;
        int prixMachine=0;


        Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);




        QSqlQuery machineList = m.rechercherMachine(chaine_c);
        while (machineList.next()) {
             Machine_row_table *row = new Machine_row_table(ui->scrollArea,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
             row->setMinimumHeight(64);
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

void Machines::on_search_input_machine_textChanged(const QString &arg1)
{
    on_search_machine_clicked();

}

void Machines::on_trier_machine_clicked()
{
    on_refreshBtn_clicked();
}


void Machines::on_statMachine_clicked()
{
    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

    QPieSeries *series1 = new QPieSeries();

        series1->append("Machine en bon etat", m.statistiqueMachine(1));
        series1->append("Machine en panne", m.statistiqueMachine(0));

        for(auto slice : series1->slices())
            slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));


       QColor color0(0x6568F3);
       QColor color1(0x341763);

        QPieSlice *slice0 = series1->slices().at(0);
        slice0->setLabelVisible();

        QPieSlice *slice1 = series1->slices().at(1);
        slice1->setExploded();
        slice1->setLabelVisible(true);
        slice1->setPen(QPen(Qt::color1, 0));
        slice1->setBrush(Qt::color1);


        slice0->setColor(color0);
        slice1->setColor(color1);


        QChart *chart1 = new QChart();
        chart1->addSeries(series1);

        chart1->legend()->markers(series1)[0]->setLabel("Machine en bon etat");
        chart1->legend()->markers(series1)[1]->setLabel("Machine en panne");

        chart1->setTitle("Etat des machines");
        chart1->legend()->setVisible(true);
        chart1->legend()->setAlignment(Qt::AlignBottom);
        chart1->setBackgroundVisible(false);


        QChartView *chartView1 = new QChartView(chart1);

        chartView1->setMaximumWidth(500);
        chartView1->setMaximumHeight(260);
        chartView1->setParent(ui->circleFrame);

        chartView1->show();


timer4->stop();

}

void Machines::on_excel_btn_clicked()
{
    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

    QTableView *table=new QTableView;
    table->setModel(m.afficherMachineForExcel());



               QString filters("CSV files (*.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");//
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);//d:fenetre d'enrgtr
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {//tc:type de fch
                   QTextStream data(&file);
                   QStringList strList;//separation des chaines


                   for (int i = 0; i < model->columnCount(); i++)
                   {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }

                   data << strList.join(";") << "\n";


                   for (int i = 0; i < model->rowCount(); i++)
                   {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++)
                       {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                   data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                             QObject::tr("Export avec succes .\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }
}


void Machines::on_add_imageBtn_clicked()
{

    QString imageFile = QFileDialog ::getOpenFileName(0,"Select Image","/home/","Image Files (*.png)");

      QFileInfo info(imageFile);
    QFileInfo  filename = info.fileName(); //path de l'image

    QPixmap image (imageFile);
      ui->lblBkImge->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
      image = image.scaled(130,100,Qt::IgnoreAspectRatio,Qt::FastTransformation);
      ui->lblBkImge->setPixmap(image);
      ui->lblBkImge->show();
     // qDebug() << image <<endl << imageFile <<endl<<info.fileName();

     machineImg = imageFile;

}



void Machine_row_table::repaireBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineId = buttonSender->whatsThis().toInt();


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

    bool test = m.entretienMachine(machineId);
    if(test){
        QMessageBox::information(nullptr, QObject::tr("maintenance status"),QObject::tr("Well repaired machine.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        timer4->start(100);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("maintenance status"),QObject::tr("Machine is already in good condition.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}


void Machine_row_table::historiqueBtn_clicked()
 {

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineId =buttonSender->whatsThis().toInt();


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);

    int test = m.historiqueCount(machineId);
    if(test == 0)
    {
        QMessageBox::critical(nullptr, QObject::tr("historique status"),QObject::tr("this machine had never been repaired.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        Historiques_machine *historique = new Historiques_machine();
        historique->machineId = machineId;


        historique->show();

    }


 }

void Machines::on_arduinoM_btn_clicked()
{
    Arduino_machine *arduino = new Arduino_machine();

    arduino->show();

}





//****************************************************************************************************
void Machine_row_table::arduinoBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int machineId =buttonSender->whatsThis().toInt();

    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Machine_fonction m( nomMachine, machineImg,  prixMachine,  etatMachine);


    QSqlQuery machineList = m.afficherMachine(machineId);
    machineList.next();
    //nomMachine = machineList.value(1).toString();

    Arduino_machine *arduino = new Arduino_machine();
    arduino->nomMachine = machineList.value(1).toString();

    arduino->show();

}
