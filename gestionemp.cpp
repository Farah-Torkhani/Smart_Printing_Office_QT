#include "gestionemp.h"
#include "ui_gestionemp.h"

#include "chat.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "employees.h"
#include "row_table.h"


QVBoxLayout *layoutt = new QVBoxLayout();

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
