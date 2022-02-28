#include "login.h"
#include "ui_login.h"
#include "gestionemp.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    this->close();
    GestionEmp gEmp;
    gEmp.show();
    QEventLoop loop;

    connect(&gEmp, SIGNAL(closed()), &loop, SLOT(quit()));

    loop.exec();
}
