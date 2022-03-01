#include "imprimer_recu.h"
#include "ui_imprimer_recu.h"

imprimer_recu::imprimer_recu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imprimer_recu)
{
    ui->setupUi(this);
}

imprimer_recu::~imprimer_recu()
{
    delete ui;
}
