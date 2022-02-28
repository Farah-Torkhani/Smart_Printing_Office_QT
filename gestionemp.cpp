#include "gestionemp.h"
#include "ui_gestionemp.h"

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
