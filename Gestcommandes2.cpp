#include "Gestcommandes2.h"
#include "ui_Gestcommandes.h"

GestCommandes::GestCommandes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GestCommandes)
{
    ui->setupUi(this);




}

GestCommandes::~GestCommandes()
{
    delete ui;
}





