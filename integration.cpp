#include "integration.h"
#include "ui_integration.h"


//GESTION EMP***
QVBoxLayout *layoutt = new QVBoxLayout();
QTimer *timerRefresh = new QTimer();
QTimer *timerFormulaire = new QTimer();
QTimer *timerCherche = new QTimer();
QTimer *timerAccountInfo = new QTimer();
QTimer *timerCurrentEmp = new QTimer();
QTimer *timerChercheTest = new QTimer();
QTimer *timerChartEmp = new QTimer();
int cin = 0;
//GESTION EMP***

//GESTION Client***
int testnum=0;
QVBoxLayout *layouttClient = new QVBoxLayout();
int cinClient = 0;
QTimer *timer = new QTimer();//setFormulaire
QTimer *timer2 = new QTimer();//refresh
QTimer *timer3 = new QTimer(); //recher
QTimer *timer4 = new QTimer(); //stat
QTimer *timerTestCall2 = new QTimer();//
QString pch="",pch2="";
//GESTION Client***

//GESTION Machine***
QVBoxLayout *layouttMachine = new QVBoxLayout();

int machineId = 0;
QString machineImg ="";
QTimer *timerMach = new QTimer();//setFormulaire
QTimer *timer2Mach = new QTimer();//refresh
QTimer *timer3Mach = new QTimer(); //recher
QTimer *timer4Mach = new QTimer(); //stat
//GESTION Machine***

//GESTION Commande***
int id = 0;
QTranslator T;
QTimer *timerCommande = new QTimer();//setFormulaire
QTimer *timer2Commande = new QTimer();//reflesh
QTimer *timer3Commande = new QTimer(); //recher
QTimer *timer4Commande = new QTimer(); //stat
QTimer *timer5Commande = new QTimer(); //cin combobox
QVBoxLayout *layouttCommande = new QVBoxLayout();
//GESTION Commande***

//GESTION Produit***
#include <stdlib.h>
#include "row_table_produits.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QUrl>
#include <QDesktopServices>

#include "qrcode.h"
#include <QtSvg/QSvgRenderer>
#include <fstream>
#include "arduino_produit.h"
//GESTION Produit***



QVBoxLayout *layouttP = new QVBoxLayout();

QTimer *timerP = new QTimer();
QTimer *timerP2 = new QTimer();
QTimer *timerP3 = new QTimer();
QTimer *timerP4 = new QTimer();
QTimer *timerP5 = new QTimer();
QTimer *timerP8 = new QTimer();
int idP=0,idd=0;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


Integration::Integration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Integration)
{
    ui->setupUi(this);

    //GESTION EMP:START***********************************************
    ui->trieOption->addItem("par défaut");
    ui->trieOption->addItem("nom");
    ui->trieOption->addItem("date_emb");
    ui->trieOption->addItem("salaire");


    ui->scrollArea->setWidget( ui->scrollAreaContents );
    ui->scrollAreaContents ->setLayout( layoutt );

    ui->fullnameLabel->setText(currentEmp.getNom()+" "+ currentEmp.getPrenom());

    refreshAccountInfo();

    ui->cinInput->setValidator(new QIntValidator (0,99999999,ui->cinInput));
    ui->nomInput->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
    ui->prenomInput->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
    ui->salaireInput->setValidator(new QIntValidator (0,99999999,ui->salaireInput));
    ui->numCarteInput->setValidator(new QRegExpValidator(  QRegExp("[0-9]*")  ));
    ui->telnput->setValidator(new QIntValidator (0,99999999,ui->telnput));
    ui->roleInput->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));


    if(currentEmp.getRole() != "admin"){
        ui->adminInterface->hide();
        ui->cinInput->setDisabled(true);
        ui->roleInput->setDisabled(true);
        ui->salaireInput->setDisabled(true);
        connect(timerAccountInfo, SIGNAL(timeout()), this, SLOT(refreshAccountInfo()));
        timerAccountInfo->start(500);
    }else {
        ui->userInterface->hide();
        ui->account_info->hide();
        connect(timerCurrentEmp, SIGNAL(timeout()), this, SLOT(refreshCurrentEmp()));
        timerCurrentEmp->start(500);
    }

    chartEmp();

    on_refreshBtn_clicked();
    connect(timerRefresh, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timerRefresh->start(2000);

    on_chercheBtn_clicked();
    connect(timerFormulaire, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    connect(timerCherche, SIGNAL(timeout()), this, SLOT(on_chercheBtn_clicked()));
    connect(timerChartEmp, SIGNAL(timeout()), this, SLOT(chartEmp()));
//    timerChartEmp->start(3000);


//    connect(timerTrie, SIGNAL(timeout()), this, SLOT(on_trieBtn_clicked()));
//    testChercheInput();
//    connect(timerChercheTest, SIGNAL(timeout()), this, SLOT(testChercheInput()));
//    timerChercheTest->start(500);

    //GESTION EMP:END*******************************************************************************


    //***********************************Gestion Client********************************************
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
        ui->scrollAreaClient->setWidget( ui->scrollAreaWidgetContentsClient );
        ui->scrollAreaWidgetContentsClient ->setLayout( layouttClient );
        //end scroll area


        connect(timer, SIGNAL(timeout()), this, SLOT(setClientFormulaire()));
        //timer->start(500);
        connect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshClientBtn_clicked()));
        timer2->start(100);
        connect(timer3, SIGNAL(timeout()), this, SLOT(on_search_client_clicked()));
    //    timer3->start(3000);

        mScene = new DuScene(this);
        ui->graphicsView->setScene(mScene);

        connect(timer4, SIGNAL(timeout()), this, SLOT(on_stat_clicked()));
        timer4->start(500);

    //  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(test_callArd())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

        connect(timerTestCall2, SIGNAL(timeout()), this, SLOT(test_callArd()));
         //timerTestCall2->start(1500);

        //***********************************End Gestion Client********************************************


        //**********************gestion machine************************************************
        //*******************controle de saisie Machine*****************************
            ui->Prix_f->setValidator(new QIntValidator (0,99999999,ui->Prix_f));
           // ui->Nom_f->setValidator(new QRegExpValidator(  QRegExp("[A-Za-z]*")  ));
        //*******************controle de saisie Machine*****************************

        //*******************trie options Machine**************************
                ui->machine_combo->addItem("par défaut");
                    ui->machine_combo->addItem("nom");
                    ui->machine_combo->addItem("etat");
                    ui->machine_combo->addItem("prix");
                    ui->machine_combo->addItem("date_achat");
        //*******************trie options Machine***************************


        //scroll area
        ui->scrollAreaMachine->setWidget( ui->scrollAreaWidgetContentsMachine );
        ui->scrollAreaWidgetContentsMachine ->setLayout( layouttMachine );


        //end scroll area
        connect(timerMach, SIGNAL(timeout()), this, SLOT(setFormulaireMachine()));
        //timer->start(500);

        connect(timer2Mach, SIGNAL(timeout()), this, SLOT(on_refreshBtnMachine_clicked()));
        timer2Mach->start(100);

        connect(timer3Mach, SIGNAL(timeout()), this, SLOT(on_search_machine_clicked()));
    //    timer3->start(3000);


        //  afficherStatistique();

        connect(timer4Mach, SIGNAL(timeout()), this, SLOT(on_statMachine_clicked()));
        timer4Mach->start(500);
        //**********************End gestion machine************************************************


        //***********************************Gestion Commande********************************************

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
            connect(timer5Commande, SIGNAL(timeout()), this, SLOT(setCinClient_combo()));
            setCinClient_combo();

            //*****************************End Gestion Commande********************************************




            //*************************START GESTION Pr  ****************************

            //scroll area
            ui->scrollArea_P->setWidget( ui->scrollAreaContents_P );
            ui->scrollAreaContents_P ->setLayout( layouttP);
            ui->edit_prix->setValidator(new QIntValidator (0,99999999,ui->edit_prix));
            ui->edit_qu->setValidator(new QIntValidator (0,99999999,ui->edit_qu));
            Produits p;

           // ui->tab_produits->setModel(p.affichertr());
           int ret=A.connect_arduino(); // lancer la connexion à arduino
            switch(ret){
            case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                break;
            case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
               break;
            case(-1):qDebug() << "arduino is not available";
                break;
            }
               /* connect(timerP8, SIGNAL(timeout()), this, SLOT(update_label()));
                timerP8->start(100);*/



            connect(timerP, SIGNAL(timeout()), this, SLOT(setFormulaire1()));

            connect(timerP2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked1()));
            timerP2->start(200);
            connect(timerP4, SIGNAL(timeout()), this, SLOT(on_statP_clicked()));
            timerP4->start(100);
            connect(timerP5, SIGNAL(timeout()), this, SLOT(on_statP1_clicked()));
            timerP5->start(100);

            connect(timerP3, SIGNAL(timeout()), this, SLOT(setQR()));
            popUp = new PopUp();
            // ************  Gestion Pr END *******************





}

Integration::~Integration()
{
    delete ui;
}

//GESTION EMP:START***
void Integration::on_chatBtn_clicked()
{
    Chat *chat = new Chat();
    chat->show();
}

void Integration::on_addBtn_clicked()
{
    timerChartEmp->start(3000);
    int cin = ui->cinInput->text().toInt();
    QString nom = ui->nomInput->text();
    QString prenom = ui->prenomInput->text();
    QString email = ui->emailInput->text();
    QString password = ui->passwordInput->text();
    QString numCard = ui->numCarteInput->text();
    int tel = ui->telnput->text().toInt();
    int salaire = ui->salaireInput->text().toInt();
    QString role = ui->roleInput->text();
    Employees e(cin,nom,prenom,email,password,numCard,tel,salaire,role);

    if(is_email_valid(email)){
        bool test = e.ajouterEmp();

        if(test){
            QMessageBox::information(nullptr, QObject::tr("add status"),QObject::tr("employe added.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("add status"),QObject::tr("employe not added.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("invalid email"),QObject::tr("email not valid.\nClick Cancel to exit."), QMessageBox::Cancel);
    }




    while(!layoutt->isEmpty()){
    QLayoutItem* item = layoutt->itemAt(0);
    layoutt->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }

    QSqlQuery empList = e.afficherAllEmp();
    while (empList.next()) {
        Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }
}

void Integration::on_refreshBtn_clicked()
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

    Employees e;
    QString trieOption = ui->trieOption->currentText();
    QSqlQuery empList = e.trieEmp(trieOption);
    while (empList.next()) {
        Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }
}

void Integration::setFormulaire()
{
    if(cin != -999999999){
        Employees e;
        QSqlQuery emp = e.afficherEmp(cin);
        emp.next();
        ui->cinInput->setText(emp.value(0).toString()); //cin 0
        ui->nomInput->setText(emp.value(1).toString()); //nom 1
        ui->prenomInput->setText(emp.value(2).toString()); //prenom 2
        ui->emailInput->setText(emp.value(7).toString()); //tel 3
        ui->passwordInput->setText(emp.value(8).toString()); //salaire 4
        ui->numCarteInput->setText(emp.value(9).toString()); //date 5
        ui->salaireInput->setText(emp.value(4).toString()); //role 6
        ui->telnput->setText(emp.value(3).toString()); //email 7
        ui->roleInput->setText(emp.value(6).toString()); //pass 8

        bool inputsFocus = ui->cinInput->hasFocus() || ui->nomInput->hasFocus() || ui->prenomInput->hasFocus() || ui->emailInput->hasFocus() || ui->passwordInput->hasFocus() || ui->numCarteInput->hasFocus() || ui->salaireInput->hasFocus() || ui->telnput->hasFocus() || ui->roleInput->hasFocus();
        if(inputsFocus){
            timerFormulaire->stop();
        }
    }
}

void Row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    cin = buttonSender->whatsThis().toInt();
    timerFormulaire->start(500);
}

void Integration::on_clearBtn_clicked()
{
    timerFormulaire->stop();
    if(currentEmp.getRole() == "admin"){
        ui->cinInput->setText("");
        ui->roleInput->setText("");
        ui->salaireInput->setText("");
    }

    ui->nomInput->setText("");
    ui->prenomInput->setText("");
    ui->emailInput->setText("");
    ui->passwordInput->setText("");
    ui->numCarteInput->setText("");
    ui->telnput->setText("");
}

void Integration::on_updateBtn_clicked()
{
    int cin2 = ui->cinInput->text().toInt();
    QString nom = ui->nomInput->text();
    QString prenom = ui->prenomInput->text();
    QString email = ui->emailInput->text();
    QString password = ui->passwordInput->text();
    QString numCard = ui->numCarteInput->text();
    int tel = ui->telnput->text().toInt();
    int salaire = ui->salaireInput->text().toInt();
    QString role = ui->roleInput->text();

    if(is_email_valid(email)){
        Employees e(cin2,nom,prenom,email,password,numCard,tel,salaire,role);
        bool test = e.modifierEmp();

        if(test){
            QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("employe updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("employe not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }else {
        QMessageBox::critical(nullptr, QObject::tr("invalid email"),QObject::tr("email not valid.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}

void Row_table::deleteBtn_clicked()
{
    timerChartEmp->start(3000);
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int cin2 = buttonSender->whatsThis().toInt();
    Employees e;
    bool test = e.supprimerEmp(cin2);
//    qDebug()<< cin;

    if(test){
        QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("employe deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        if(cin2 == currentEmp.getCin()){
            timerRefresh->stop();
            timerFormulaire->stop();
            timerCherche->stop();
            timerAccountInfo->stop();
            timerCurrentEmp->stop();
            this->close();
            Login login;
            login.show();
            QEventLoop loop;

            connect(&login, SIGNAL(closed()), &loop, SLOT(quit()));

            loop.exec();
        }
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("employe not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void Integration::on_chercheBtn_clicked()
{
    QString recherche = ui->chercheInput->text();

    if(recherche != ""){
        timerRefresh->stop();
        timerCherche->start(1000);

        while(!layoutt->isEmpty()){
        QLayoutItem* item = layoutt->itemAt(0);
        layoutt->removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
        }

        Employees e;
        QSqlQuery empList = e.rechercheEmp(recherche);
        while (empList.next()) {
            Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
            row->setMinimumHeight(34);
            layoutt->addWidget( row );
        }
    }else {
        timerCherche->stop();
        timerRefresh->start(2000);
    }
}

void Integration::on_formationBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.inforoutefpt.org/formation-professionnelle/diplome-etudes-professionnelles/5313/"));
}

bool Integration::is_email_valid(QString email)
{
    QRegularExpression regex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b");

    return regex.match(email).hasMatch();
}

void Integration::on_logoutBtn_clicked()
{
    timerRefresh->stop();
    timerFormulaire->stop();
    timerCherche->stop();
    timerAccountInfo->stop();
    timerCurrentEmp->stop();
    timerChartEmp->stop();

    disconnect(timerCurrentEmp, SIGNAL(timeout()), this, SLOT(refreshCurrentEmp()));
    disconnect(timerRefresh, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    disconnect(timerFormulaire, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    disconnect(timerCherche, SIGNAL(timeout()), this, SLOT(on_chercheBtn_clicked()));
    disconnect(timerAccountInfo, SIGNAL(timeout()), this, SLOT(refreshAccountInfo()));
    disconnect(timerChartEmp, SIGNAL(timeout()), this, SLOT(chartEmp()));

    //client part
        timer->stop();
        timer2->stop();
        timer3->stop();
        timer4->stop();
        timerTestCall2->stop();

        disconnect(timer, SIGNAL(timeout()), this, SLOT(refreshCurrentEmp()));

        disconnect(timer, SIGNAL(timeout()), this, SLOT(setClientFormulaire()));
        disconnect(timer2, SIGNAL(timeout()), this, SLOT(on_refreshClientBtn_clicked()));
        disconnect(timer3, SIGNAL(timeout()), this, SLOT(on_search_client_clicked()));
        disconnect(timer4, SIGNAL(timeout()), this, SLOT(on_stat_clicked()));
        disconnect(timerTestCall2, SIGNAL(timeout()), this, SLOT(test_callArd()));
    //client part

    //machine part
        timerMach->stop();
        timer2Mach->stop();
        timer3Mach->stop();
        timer4Mach->stop();

        disconnect(timerMach, SIGNAL(timeout()), this, SLOT(setFormulaireMachine()));
        disconnect(timer2Mach, SIGNAL(timeout()), this, SLOT(on_refreshBtnMachine_clicked()));
        disconnect(timer3Mach, SIGNAL(timeout()), this, SLOT(on_search_machine_clicked()));
        disconnect(timer4Mach, SIGNAL(timeout()), this, SLOT(on_statMachine_clicked()));
    //machine part

    //commande part
        timerCommande->stop();
        timer2Commande->stop();
        timer3Commande->stop();
        timer4Commande->stop();
        timer5Commande->stop();

        disconnect(timerCommande, SIGNAL(timeout()), this, SLOT(setCommandeFormulaire()));
        disconnect(timer2Commande, SIGNAL(timeout()), this, SLOT(on_refreshCommandeBtn_clicked()));
        disconnect(timer3Commande, SIGNAL(timeout()), this, SLOT(on_search_commandeBtn_clicked()));
        disconnect(timer4Commande, SIGNAL(timeout()), this, SLOT(on_statCommande_clicked()));
        disconnect(timer5Commande, SIGNAL(timeout()), this, SLOT(setCinClient_combo()));
    //commande part

    //produit part
        timerP->stop();
        timerP2->stop();
        timerP3->stop();
        timerP4->stop();
        timerP5->stop();
        timerP8->stop();

        connect(timerP, SIGNAL(timeout()), this, SLOT(setFormulaire1()));
        connect(timerP2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked1()));
        connect(timerP4, SIGNAL(timeout()), this, SLOT(on_statP_clicked()));
        connect(timerP5, SIGNAL(timeout()), this, SLOT(on_statP1_clicked()));
        connect(timerP3, SIGNAL(timeout()), this, SLOT(setQR()));
    //produit part

    this->close();

//    delete timerRefresh;
//    qApp->quit();
//    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
//    delete this->centralWidget();
//    delete this->menuBar();
//    delete this->statusBar();
//    deleteLater();
//    this->destroy(true,true);
//    delete this;
    Login login;
    login.show();
    QEventLoop loop;

    connect(&login, SIGNAL(closed()), &loop, SLOT(quit()));

    loop.exec();
}

void Integration::on_me_formationBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.inforoutefpt.org/formation-professionnelle/diplome-etudes-professionnelles/5313/"));
}

void Integration::on_me_setForm_clicked()
{
    Employees e;
    QSqlQuery emp = e.afficherEmp(currentEmp.getCin());
    emp.next();
    ui->cinInput->setText(emp.value(0).toString()); //cin 0
    ui->nomInput->setText(emp.value(1).toString()); //nom 1
    ui->prenomInput->setText(emp.value(2).toString()); //prenom 2
    ui->emailInput->setText(emp.value(7).toString()); //tel 3
    ui->passwordInput->setText(emp.value(8).toString()); //salaire 4
    ui->numCarteInput->setText(emp.value(9).toString()); //date 5
    ui->salaireInput->setText(emp.value(4).toString()); //role 6
    ui->telnput->setText(emp.value(3).toString()); //email 7
    ui->roleInput->setText(emp.value(6).toString()); //pass 8

}

void Integration::refreshAccountInfo()
{
    Employees e;
    QSqlQuery emp = e.afficherEmp(currentEmp.getCin());
    emp.next();
    Employees test(emp.value(0).toInt(), emp.value(2).toString(), emp.value(1).toString(), emp.value(7).toString(), emp.value(8).toString(), emp.value(9).toString(), emp.value(3).toInt(), emp.value(8).toInt(), emp.value(6).toString());
    currentEmp = test;

    ui->me_nom->setText(emp.value(1).toString());
    ui->me_prenom->setText(emp.value(2).toString());
    ui->me_email->setText(emp.value(7).toString());
    ui->me_salaire->setText(emp.value(4).toString());
    ui->me_num_tel->setText(emp.value(3).toString());
    ui->me_num_carte->setText(emp.value(9).toString());
    ui->me_fullname->setText( emp.value(1).toString() +" "+ emp.value(2).toString() );
    ui->fullnameLabel->setText( emp.value(1).toString() +" "+ emp.value(2).toString() );
    ui->me_role->setText(emp.value(6).toString());
}

void Integration::on_me_updateBtn_clicked()
{
    int cin2 = ui->cinInput->text().toInt();
    QString nom = ui->nomInput->text();
    QString prenom = ui->prenomInput->text();
    QString email = ui->emailInput->text();
    QString password = ui->passwordInput->text();
    QString numCard = ui->numCarteInput->text();
    int tel = ui->telnput->text().toInt();
    int salaire = ui->salaireInput->text().toInt();
    QString role = ui->roleInput->text();

    if(is_email_valid(email)){
        Employees e(cin2,nom,prenom,email,password,numCard,tel,salaire,role);
        bool test = e.modifierEmp();

        if(test){
            QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("employe updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        }
        else {
            QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("employe not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    }else {
        QMessageBox::critical(nullptr, QObject::tr("invalid email"),QObject::tr("email not valid.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void Integration::on_me_deleteBtn_clicked()
{
    Employees e;
    bool test = e.supprimerEmp(currentEmp.getCin());
//    qDebug()<< cin;

    if(test){
        QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("employe deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        on_logoutBtn_clicked();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("employe not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void Integration::refreshCurrentEmp()
{
    Employees e;
    QSqlQuery emp = e.afficherEmp(currentEmp.getCin());
    emp.next();
    Employees test(emp.value(0).toInt(), emp.value(2).toString(), emp.value(1).toString(), emp.value(7).toString(), emp.value(8).toString(), emp.value(9).toString(), emp.value(3).toInt(), emp.value(8).toInt(), emp.value(6).toString());
    currentEmp = test;

    ui->fullnameLabel->setText( emp.value(1).toString() +" "+ emp.value(2).toString() );
}

void Integration::on_me_chatBtn_clicked()
{
    Chat *chat = new Chat();
    chat->show();
}

void Integration::test(){
    QStringList CompletionList;
                  Employees e;
                  QSqlQuery test = e.afficherAllEmp();
                  while (test.next()) {
                        CompletionList.push_back(test.value(1).toString());
                        CompletionList.push_back(test.value(2).toString());
                  }

                 QCompleter *stringCompleter = new QCompleter(CompletionList,this);
                 stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);

                 ui->chercheInput->setCompleter(stringCompleter);
}

void Integration::testChercheInput(){
    QString recherche = ui->chercheInput->text();

    if(recherche != ""){
        timerCherche->start(1000);
    }
}

void Integration::on_chercheInput_textChanged(const QString &arg1)
{
    on_chercheBtn_clicked();
}

void Integration::chartEmp()
{
    Employees e;
    QChart *chart = new QChart();
    chart->setAnimationDuration(0);
    QChartView *chartView = new QChartView(chart);
    QBarSet *set1 = new QBarSet("Nombre d'employees par mois");


    *set1 << e.statEmp(1)
          << e.statEmp(2)
          << e.statEmp(3)
          << e.statEmp(4)
          << e.statEmp(5)
          << e.statEmp(6)
          << e.statEmp(7)
          << e.statEmp(8)
          << e.statEmp(9)
          << e.statEmp(10)
          << e.statEmp(11)
          << e.statEmp(12);

    QColor color(0x6568F3);
    set1->setColor(color);

        QBarSeries *series = new QBarSeries();
        series->append(set1);


        chart->addSeries(series);
        chart->setTitle("");
//        chart->setAnimationOptions(QChart::SeriesAnimations);
//        chart->setBackgroundVisible(false);

        //  chart->setAnimationOptions(QChart::SeriesAnimations);
        QColor bgColor(0xF4DCD3);
        chart->setBackgroundBrush(QBrush(QColor(bgColor)));

        chart->setBackgroundVisible(true);
        //  chart->setBackgroundVisible(false);


        QStringList categories;
        categories << "Jan" << "Fiv" << "Mar" << "Avr" << "Mai" << "Juin" << "Jui" <<"Aou" << "sep" << "Oct" << "Nov" << "Dec" ;
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);


        chart->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);


        chartView->setRenderHint(QPainter::Antialiasing);
        QPalette pal = qApp->palette();
        pal.setColor(QPalette::WindowText, QRgb(0x6568F3));
        pal.setColor(QPalette::Window, QRgb(0x6568F3));
        qApp->setPalette(pal);

        chartView->setMaximumWidth(560);
        chartView->setMaximumHeight(240);


        chartView->setParent(ui->chartContainer);
        chart->setParent(ui->adminInterface);

        chartView->show();

        timerChartEmp->stop();
}

//GESTION EMP:END************************************************************************************

//********************************Gestion Client**********************************************************
void Integration::on_ajouter_client_clicked()
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


     //
     setCinClient_combo();
     //
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

    bool test = c.supprimerClient(cinClient);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("delete status"),QObject::tr("Client deleted.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
        timer2->start(100);
        timer4->start(100);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("Client not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    //
    timer5Commande->start(100);
    //
}

void Integration::on_refreshClientBtn_clicked()
{

    while(!layouttClient->isEmpty()){
    QLayoutItem* item = layouttClient->itemAt(0);
    layouttClient->removeItem(item);
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
        layouttClient->addWidget( row );
    }
    QStringList CompletionList;

     CompletionList = c.rechercherClients();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->search_input->setCompleter(stringCompleter);


    //openSSl version

    qDebug()<<QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();





timer2->stop();
}

void Integration::on_modifier_client_clicked()
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

void Integration::setClientFormulaire()
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

void Integration::on_clear_client_clicked()
{
    timer->stop();
    ui->Cin_f->setText("");
    ui->Nom_f->setText("");
    ui->Prenom_f->setText("");
    ui->Email_f->setText("");
    ui->Phone_f->setText("");
}

void Integration::on_pdfBtn_clicked()
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

void Integration::on_search_client_clicked()
{

       QString chaine_c=ui->search_input->text();

       if(chaine_c !="")
       {
           timer2->stop();
           timer3->start(100);


        while(!layouttClient->isEmpty()){
        QLayoutItem* item = layouttClient->itemAt(0);
        layouttClient->removeItem(item);
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
            layouttClient->addWidget( row );
        }

        }
       else
       {
           timer3->stop();
           timer2->start(100);

       }

timer3->stop();

}

void Integration::on_search_input_textChanged(const QString &arg1)
{
    on_search_client_clicked();
}

void Integration::on_stat_clicked()
{

    QBarSet *set1 = new QBarSet("Nombre de clients par mois");

    int cinClient=0;
    QString nomClient="";
    QString prenomClient="";
    QString emailClient="";
    int telClient=0;


    Client_fonction c( cinClient, nomClient,  prenomClient,  emailClient,  telClient );

    *set1 <<  c.statistiqueCilents(1)
          <<  c.statistiqueCilents(2)
          <<  c.statistiqueCilents(3)
          <<  c.statistiqueCilents(4)
          << c.statistiqueCilents(5)
          << c.statistiqueCilents(6)
          << c.statistiqueCilents(7)
          << c.statistiqueCilents(8)
          << c.statistiqueCilents(9)
          << c.statistiqueCilents(10)
          << c.statistiqueCilents(11)
          << c.statistiqueCilents(12) ;

        qDebug()<< c.statistiqueCilents(2);



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
//               chart->setBackgroundVisible(false);

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


            timer4->stop();

}

void Integration::on_trie_client_clicked()
{
    on_refreshClientBtn_clicked();
}

void Client_row_table::emailBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    cinClient = buttonSender->whatsThis().toInt();

    Email *email = new Email();
    email->cinClient = cinClient;

    email->show();


}

void Integration::on_Alerte_btn_clicked()
{
    ui->etatReceiveCall->setText("OFF");
    timerTestCall2->stop();
    A.close_arduino();
 int c=   A.close_arduino();

    Arduino_client *arduino = new Arduino_client();

    arduino->show();

}

void Client_row_table::callBtn_clicked()
{
//
}

void Client_row_table::smsBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    cinClient = buttonSender->whatsThis().toInt();

    Sms *sms = new Sms();
    sms->setCinClient(cinClient);

    sms->show();

}

void Integration::test_callArd()
{
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
          timerTestCall2->stop();
         //A.close_arduino();

    }

//if( (numberCall.length()<6)  )
//{
//    test=0;
//}
    if( (numberCall.length()>6)  )
    {
        ui->etatReceiveCall->setText("OFF");
        A.close_arduino();
        testnum=1;
        timerTestCall2->stop();
        CallArd *call = new CallArd();
       // call->setCinClient(cinClient);
        call->call_numIn = numberCall;

        call->show();
    }

    if(numberCall.length()<6)
    {
        testnum=0;
    }

  //  if(data == "1")
  //  {
     //   ui->niveauEncre->setText("cv"); // si les données reçues de arduino via la liaison série sont sup à ...
  //  }
  //  else
  //  {
       // ui->niveauEncre->setText("faible");   // si les données reçues de arduino via la liaison série sont inf à ...
  //  }

//    timerTestCall2->stop();


}

void Integration::on_call_testBtn_clicked()
{
    ui->etatReceiveCall->setText("OFF");
    CallArd *call = new CallArd();
   // call->setCinClient(cinClient);
    //call->call_numIn = numberCall;

    call->show();


}

void Integration::on_recive_callBtnTimer_clicked()
{
    timerTestCall2->start(1500);
    ui->etatReceiveCall->setText("ON");
}

//********************************End Gestion Client**********************************************************

//********************************Gestion Machine**********************************************************

void Integration::on_ajouter_machine_clicked()
{

    QString nomMachine=ui->Nom_Mach->text();
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
        timer2Mach->start(100);
        timer4Mach->start(100);
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
        timer2Mach->start(100);
        timer4Mach->start(100);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("delete status"),QObject::tr("Machine not deleted.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}

void Integration::on_refreshBtnMachine_clicked()
{
    while(!layouttMachine->isEmpty()){
    QLayoutItem* item = layouttMachine->itemAt(0);
    layouttMachine->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }


    QString nomMachine=ui->Nom_Mach->text();
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
         Machine_row_table *row = new Machine_row_table(ui->scrollAreaMachine,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
         row->setMinimumHeight(64);
         layouttMachine->addWidget( row );
    }

    QStringList CompletionList;
    CompletionList = m.rechercherMachines_completer();

    stringCompleter = new QCompleter(CompletionList,this);
    stringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->search_input_machine->setCompleter(stringCompleter);


    timer2Mach->stop();

}

void Integration::on_modifier_machine_clicked()
{
    QString nomMachine=ui->Nom_Mach->text();
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
        timer2Mach->start(100);
        timer4Mach->start(100);
        on_clear_machine_clicked();
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("Machine not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void Integration::setFormulaireMachine()
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
        ui->Nom_Mach->setText(machineInfo.value(1).toString());
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

        bool inputsFocus = ui->img_f->hasFocus() || ui->Nom_Mach->hasFocus() || ui->Prix_f->hasFocus() ;
        if(inputsFocus){
            timerMach->stop();
        }
    }
    timerMach->stop();
}

void Machine_row_table::updateBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    machineId = buttonSender->whatsThis().toInt();

    timerMach->start(100);
}

void Integration::on_clear_machine_clicked()
{
    timerMach->stop();
    ui->Nom_Mach->setText("");
    ui->Prix_f->setText("");
    ui->img_f->setText("");
    ui->radioButton_bon->setChecked(true);

    QPixmap image ("");
    ui->lblBkImge->setPixmap(image);
}

void Integration::on_search_machine_clicked()
{
       QString chaine_c=ui->search_input_machine->text();

       if(chaine_c !="")
       {
           timer2Mach->stop();
           timer3Mach->start(100);


        while(!layouttMachine->isEmpty()){
        QLayoutItem* item = layouttMachine->itemAt(0);
        layouttMachine->removeItem(item);
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
             Machine_row_table *row = new Machine_row_table(ui->scrollAreaMachine,machineList.value(0).toString(),machineList.value(1).toString(),machineList.value(2).toString(),machineList.value(3).toString(), machineList.value(4).toString());
             row->setMinimumHeight(64);
             layouttMachine->addWidget( row );
        }

        }
       else
       {
           timer3Mach->stop();
           timer2Mach->start(100);

       }

timer3Mach->stop();

}

void Integration::on_search_input_machine_textChanged(const QString &arg1)
{
    on_search_machine_clicked();
}

void Integration::on_trier_machine_clicked()
{
    on_refreshBtnMachine_clicked();
}

void Integration::on_statMachine_clicked()
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


timer4Mach->stop();

}

void Integration::on_excel_btn_clicked()
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

void Integration::on_add_imageBtn_clicked()
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
        timer2Mach->start(100);
        timer4Mach->start(100);
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

void Integration::on_arduinoM_btn_clicked()
{
    Arduino_machine *arduino = new Arduino_machine();

    arduino->show();

}

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
//*************************************End gestion machine**************************************************************

//*************************************Gestion Commande*****************************************************************
void Integration::on_ajouter_commande_clicked()
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

void Integration::on_modifier_commande_clicked()
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

void Integration::on_refreshCommandeBtn_clicked()
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

void Integration::setCommandeFormulaire()
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

void Integration::on_clear_commande_clicked()
{
    timerCommande->stop();
    ui->descreption->setPlainText("");
    ui->Qc->setText("");
    ui->Qsc->setText("");

    QDate cd = QDate::currentDate();
    ui->dateFinCommande->setDate(cd);
    ui->selectCinClient->setCurrentText("");
}

void Integration::on_search_commandeBtn_clicked()
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

void Integration::on_chercher_commande_textChanged(const QString &arg1)
{
      on_search_commandeBtn_clicked();
}

void Integration::on_statCommande_clicked()
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



            chartView->setParent(ui->horizontalFrame_2);
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

void Integration::setCinClient_combo()
{

   QSqlQueryModel * modal=new QSqlQueryModel();

    QSqlQuery query;
     query.prepare("select cinClient from clients ");
    query.exec();
    modal->setQuery(query);
    ui->selectCinClient->setModel(modal);

    timer5Commande->stop();

}

void commandes_row_table::etatBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int idComm = buttonSender->whatsThis().toInt();


        Date_fin *date = new Date_fin();
        date ->idCommande = idComm;

        date->show();
}

void Integration::on_trie_commande_clicked()
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

//*************************************End gestion commande*************************************************************


//************************************* START GEST PRODUIT *****************************************************
void Integration::update_label()
{
    data=A.read_from_arduino();
    qDebug() << data;
if(data !="")
{
        popUp->setPopupText("flamme !!!");

        popUp->show();
        Produits P;
        P.ajouterf(data);

}
}
void Integration::on_statP_clicked(){

    Produits p;
    QBarSet *set0 = new QBarSet("Quantité des produits a consommés");

    *set0 << p.statistiquesProduits(1) << p.statistiquesProduits(2) << p.statistiquesProduits(3) << p.statistiquesProduits(4) << p.statistiquesProduits(5) << p.statistiquesProduits(6) << p.statistiquesProduits(7) << p.statistiquesProduits(8) << p.statistiquesProduits(9) << p.statistiquesProduits(10) <<p.statistiquesProduits(11) << p.statistiquesProduits(12);


    QColor color(0x6568F3);
    set0->setColor(color);

    QBarSeries *series = new QBarSeries();
    series->append(set0);




    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);

    QColor bgColor(0xF4DCD3);
                   chart->setBackgroundBrush(QBrush(QColor(bgColor)));

                   chart->setBackgroundVisible(true);

    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun" << "Jui" << "Aou" << "Sep" << "Oct" << "Nov" << "Dec";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);

    QChartView *chartView = new QChartView(chart);

    chartView->setMaximumWidth(631);
    chartView->setMaximumHeight(300);
    chartView->setParent(ui->horizontalFrame_P);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView->show();
    timerP4->stop();
}
void Integration::on_statP1_clicked(){
    Produits c;

    QPieSeries *series1 = new QPieSeries();
    series1->append(" 150", c.statistiqueProduits(150));
    series1->append("50", c.statistiqueProduits(50));
    series1->append("500", c.statistiqueProduits(500));
    series1->append("100", c.statistiqueProduits(100));
    series1->append(" 250", c.statistiqueProduits(250));

    QPieSlice *slice0 = series1->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice *slice1 = series1->slices().at(1);
   // slice1->setExploded();
    slice1->setLabelVisible();
   // slice1->setPen(QPen(Qt::color1, 0));
   // slice1->setBrush(Qt::color1);

    QPieSlice *slice2 = series1->slices().at(2);
    slice2->setLabelVisible();

    QPieSlice *slice3 = series1->slices().at(3);
    slice3->setLabelVisible();

    QPieSlice *slice4 = series1->slices().at(4);
    slice4->setLabelVisible();
    QColor color(0x6568F3);
    QColor color0(0x6568F3);
    slice0->setColor(color);

    QColor color1(0x341763);
    slice1->setColor(color1);

    QColor color2(0xFF7244);
    slice2->setColor(color2);

    QColor color3(0x585856);
    slice3->setColor(color3);

    QColor color4(0x6568F3);
    slice4->setColor(color4);


    QChart *chart1 = new QChart();
    chart1->addSeries(series1);
    chart1->setTitle("Quantité des produits en stock");
    chart1->legend()->hide();
    chart1->setBackgroundVisible(false);

    QColor bgColor(0xF4DCD3);
                   chart1->setBackgroundBrush(QBrush(QColor(bgColor)));

                   chart1->setBackgroundVisible(true);

    QChartView *chartView1 = new QChartView(chart1);

    chartView1->setMaximumWidth(500);
    chartView1->setMaximumHeight(260);
    chartView1->setParent(ui->circleFrame_P);
    chartView1->show();
    timerP5->stop();

                                  }
void Integration::on_valider_b_clicked()
{

        QString nomProduits=ui->edit_nom->text();
        QString quantite=ui->edit_qu->text();
        QString type=ui->edit_type->text();
        QString prixunitaire=ui->edit_prix->text();


        Produits P(nomProduits,quantite,type,prixunitaire);

        bool test=P.ajouter();

       if(test)
        {
           QMessageBox::information(nullptr,QObject::tr("ok"),
                                  QObject::tr(" effectue\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
       }
       else  QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                      QObject::tr("non effectue\n"
                                                "click cancel to exit."),QMessageBox::Cancel);

       while(!layouttP->isEmpty()){
       QLayoutItem* item = layouttP->itemAt(0);
       layouttP->removeItem(item);
       QWidget* widgett = item->widget();
       if(widgett)
           {
               delete widgett;
           }
       }


       QSqlQuery pro_liste = P.afficherAllP();
       while (pro_liste.next()) {
           row_table_produits *row = new row_table_produits(ui->scrollArea_P,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
           row->setMinimumHeight(34);
           layouttP->addWidget( row );
       }
       popUp->setPopupText(nomProduits+" est bien ajouter");

       popUp->show();
       timerP4->start();
       timerP5->start();
       timerP2->start();
}

void row_table_produits::deleteBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    int id = buttonSender->whatsThis().toInt();

    Produits p;
    p.supprimer(id);

    while(!layouttP->isEmpty()){
    QLayoutItem* item = layouttP->itemAt(0);
    layouttP->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }

timerP4->start();
timerP5->start();

}
void row_table_produits::editBtn_clicked()
{

    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    idP = buttonSender->whatsThis().toInt();
    timerP->start(500);
}
void row_table_produits::qrGBtn_clicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    idd = buttonSender->whatsThis().toInt();
    timerP3->start(500);
}
void Integration::setQR()
{
//    int reference=idd;
    Produits p;
    QSqlQuery pro_liste = p.afficherPr(idd);
    pro_liste.next();
    QString reference = pro_liste.value(1).toString() +" | "+ pro_liste.value(2).toString()+" | "+ pro_liste.value(3).toString()+" | "+ pro_liste.value(4).toString();
    QByteArray ba = reference.toLocal8Bit();
    const char *c_str2 = ba.data();
    const QrCode qr = QrCode::encodeText(/*std::to_string(reference).c_str()*/c_str2, QrCode::Ecc::LOW);
    std::ofstream myfile;
    myfile.open ("qrcode.svg") ;
    myfile << qr.toSvgString(1);
    myfile.close();
    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix( QSize(120, 120) );
    QPainter pixPainter( &pix );
    svgRenderer.render( &pixPainter );
    ui->QRCODE_3->setPixmap(pix);
    bool inputsFocus = ui->QRCODE_3->hasFocus();
    if(inputsFocus){
        timerP3->stop();

    }
}

void Integration::setFormulaire1()
{
    if(idP != -999999999){
        Produits p;
        QSqlQuery emp = p.afficherPr(idP);
        emp.next();
        ui->edit_nom->setText(emp.value(1).toString());
        ui->edit_type->setText(emp.value(3).toString());
        ui->edit_prix->setText(emp.value(4).toString()); //tel 3
        ui->edit_qu->setText(emp.value(2).toString()); //salaire 4

        bool inputsFocus = ui->edit_nom->hasFocus() || ui->edit_type->hasFocus() || ui->edit_prix->hasFocus() || ui->edit_qu->hasFocus();
        int reference=idP;
        const QrCode qr = QrCode::encodeText(std::to_string(reference).c_str(), QrCode::Ecc::LOW);
        std::ofstream myfile;
        myfile.open ("qrcode.svg") ;
        myfile << qr.toSvgString(1);
        myfile.close();
        QSvgRenderer svgRenderer(QString("qrcode.svg"));
        QPixmap pix( QSize(120, 120) );
        QPainter pixPainter( &pix );
        svgRenderer.render( &pixPainter );
        ui->QRCODE_3->setPixmap(pix);

        if(inputsFocus){
            timerP->stop();

        }
    }
}
void Integration::on_refreshBtn_clicked1()
{
    while(!layouttP->isEmpty()){
        QLayoutItem* item = layouttP->itemAt(0);
        layouttP->removeItem(item);
        QWidget* widgett = item->widget();
        if(widgett)
            {
                delete widgett;
            }
    }


    Produits P;
    QSqlQuery pro_liste = P.afficherAllP();
    while (pro_liste.next()) {
        row_table_produits *row = new row_table_produits(ui->scrollArea_P,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
        row->setMinimumHeight(34);
        layouttP->addWidget( row );
    }
    timerP2->stop();
}



void Integration::on_modifier_b_clicked()
{
    QString nomproduit = ui->edit_nom->text();
    QString type = ui->edit_type->text();
    QString quantite = ui->edit_qu->text();
    QString prix = ui->edit_prix->text();

    Produits P(nomproduit,quantite,type,prix);
    bool test = P.modifier(idP);

    if(test){
        QMessageBox::information(nullptr, QObject::tr("update status"),QObject::tr("produit updated.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("update status"),QObject::tr("produit not updated.\nClick Cancel to exit."), QMessageBox::Cancel);
    }


}

void Integration::on_b_searsh_clicked()
{
    QString chaine_r=ui->edit_r->text();


    while(!layouttP->isEmpty()){
    QLayoutItem* item = layouttP->itemAt(0);
    layouttP->removeItem(item);
    QWidget* widgett = item->widget();
    if(widgett)
        {
            delete widgett;
        }
    }

Produits P;
    QSqlQuery pro_liste = P.rechercher(chaine_r);
    while (pro_liste.next()) {
        row_table_produits *r = new row_table_produits(ui->scrollArea_P,pro_liste.value(0).toString(),pro_liste.value(1).toString(),pro_liste.value(2).toString(),pro_liste.value(3).toString(),pro_liste.value(4).toString());
        r->setMinimumHeight(34);
        layouttP->addWidget( r );
    }
    connect(timerP, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    //timer->start(500);

    connect(timerP2, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timerP2->start(5000);

}
void Integration::on_edit_r_textChanged(const QString &arg1)
{
    on_b_searsh_clicked();
}

void Integration::on_excel_clicked()
{


    QString nomMachine="";
    QString machineImg="";
    int etatMachine=0;
    int prixMachine=0;


    Produits m;

    QTableView *table=new QTableView;
    table->setModel(m.afficherProduitForExcel());



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










void Integration::on_arduino_clicked()
{
    Arduino_Produit *arduinoo = new Arduino_Produit();
    arduinoo->show();
}
//************ END Gest Produis *****************

void Integration::on_arduino_2_clicked()
{
    Arduino_Produit *arduinoo = new Arduino_Produit();
    arduinoo->show();
}
