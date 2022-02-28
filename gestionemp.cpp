#include "gestionemp.h"
#include "ui_gestionemp.h"

#include "chat.h"

GestionEmp::GestionEmp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GestionEmp)
{
    ui->setupUi(this);
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
