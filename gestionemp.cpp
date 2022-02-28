#include "gestionemp.h"
#include "ui_gestionemp.h"

#include "chat.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "employees.h"
#include "row_table.h"
#include <QMessageBox>
#include <QTimer>


QVBoxLayout *layoutt = new QVBoxLayout();
QTimer *timer = new QTimer();

GestionEmp::GestionEmp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionEmp)
{
    ui->setupUi(this);

    ui->scrollArea->setWidget( ui->scrollAreaContents );
    ui->scrollAreaContents ->setLayout( layoutt );

    Employees e;
    QSqlQuery empList = e.afficherAllEmp();
    while (empList.next()) {
        Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }

    connect(timer, SIGNAL(timeout()), this, SLOT(on_refreshBtn_clicked()));
    timer->start(3000);
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
    bool test = e.ajouterEmp();

    if(test){
        QMessageBox::critical(nullptr, QObject::tr("add status"),QObject::tr("employe added.\nClick Cancel to exit."), QMessageBox::Cancel,QMessageBox::NoIcon);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("add status"),QObject::tr("employe not added.\nClick Cancel to exit."), QMessageBox::Cancel);
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
    QSqlQuery empList = e.afficherAllEmp();
    while (empList.next()) {
        Row_table *row = new Row_table(ui->scrollArea,empList.value(0).toString(),empList.value(1).toString(),empList.value(2).toString(),empList.value(5).toString().split("T")[0],empList.value(4).toString(),empList.value(6).toString());
        row->setMinimumHeight(34);
        layoutt->addWidget( row );
    }
}
