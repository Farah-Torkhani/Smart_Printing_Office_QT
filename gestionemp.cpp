#include "gestionemp.h"
#include "ui_gestionemp.h"

#include "chat.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "employees.h"
#include "row_table.h"
#include <QMessageBox>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <regex>
#include "login.h"
#include <QDebug>


QVBoxLayout *layoutt = new QVBoxLayout();
QTimer *timerRefresh = new QTimer();
QTimer *timerFormulaire = new QTimer();
QTimer *timerCherche = new QTimer();
QTimer *timerAccountInfo = new QTimer();
QTimer *timerCurrentEmp = new QTimer();
//QTimer *timerTrie = new QTimer();
int cin = 0;

GestionEmp::GestionEmp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionEmp)
{
    ui->setupUi(this);
    ui->trieOption->addItem("par défaut");
    ui->trieOption->addItem("nom");
    ui->trieOption->addItem("date_emb");
    ui->trieOption->addItem("salaire");

    ui->scrollArea->setWidget( ui->scrollAreaContents );
    ui->scrollAreaContents ->setLayout( layoutt );

    ui->fullnameLabel->setText(currentEmp.getNom()+" "+ currentEmp.getPrenom());

    refreshAccountInfo();

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

//    qDebug()<< currentEmp.nom;
    Employees e;
    QString trieOption = ui->trieOption->currentText();
    QSqlQuery empList = e.trieEmp(trieOption);
    while (empList.next()) {
        Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

    connect(timerRefresh, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timerRefresh->start(2000);

    connect(timerFormulaire, SIGNAL(timeout()), this, SLOT(setFormulaire()));
    connect(timerCherche, SIGNAL(timeout()), this, SLOT(on_chercheBtn_clicked()));
//    connect(timerTrie, SIGNAL(timeout()), this, SLOT(on_trieBtn_clicked()));


}

GestionEmp::~GestionEmp()
{
    delete ui;
}

void GestionEmp::on_chatBtn_clicked()
{
    Chat chat;
    chat.exec();
}

void GestionEmp::on_addBtn_clicked()
{
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

void GestionEmp::on_refreshBtn_clicked()
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

void GestionEmp::setFormulaire()
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

void GestionEmp::on_clearBtn_clicked()
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

void GestionEmp::on_updateBtn_clicked()
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

void GestionEmp::on_chercheBtn_clicked()
{
    QString recherche = ui->chercheInput->text();

    if(recherche != ""){
        timerRefresh->stop();
        timerCherche->start(3000);

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

void GestionEmp::on_formationBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.inforoutefpt.org/formation-professionnelle/diplome-etudes-professionnelles/5313/"));
}

bool GestionEmp::is_email_valid(QString email)
{
    QRegularExpression regex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b");

    return regex.match(email).hasMatch();
}

void GestionEmp::on_logoutBtn_clicked()
{
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

void GestionEmp::on_me_formationBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.inforoutefpt.org/formation-professionnelle/diplome-etudes-professionnelles/5313/"));
}

void GestionEmp::on_me_setForm_clicked()
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

void GestionEmp::refreshAccountInfo()
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

void GestionEmp::on_me_updateBtn_clicked()
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

void GestionEmp::on_me_deleteBtn_clicked()
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

void GestionEmp::refreshCurrentEmp()
{
    Employees e;
    QSqlQuery emp = e.afficherEmp(currentEmp.getCin());
    emp.next();
    Employees test(emp.value(0).toInt(), emp.value(2).toString(), emp.value(1).toString(), emp.value(7).toString(), emp.value(8).toString(), emp.value(9).toString(), emp.value(3).toInt(), emp.value(8).toInt(), emp.value(6).toString());
    currentEmp = test;

    ui->fullnameLabel->setText( emp.value(1).toString() +" "+ emp.value(2).toString() );
}
