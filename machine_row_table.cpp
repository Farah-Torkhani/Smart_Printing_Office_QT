#include "machine_row_table.h"
#include <QLabel>

machine_row_table::machine_row_table(QWidget *parent,QString machineID, QString nomMachine, QString etat, QString prix) : QLabel(parent)
{
    row_container->setGeometry(3,0,840,34);
    row_container->setStyleSheet("background-color: white;\
                             border-top-left-radius: 15px;\
                             border-bottom-left-radius: 15px;\
                             border-top-right-radius: 15px;\
                             border-bottom-right-radius: 15px;\
                             color: #585856;\
");
    row_container->setMinimumHeight(34);
    row_container->setFixedHeight(34);

    nom_label->setParent(row_container);
    nom_label->setGeometry(0,0,121,34);
    nom_label->setText(nomMachine);
    nom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    nom_label->setMinimumHeight(34);


    etat_label->setParent(row_container);
    etat_label->setGeometry(120,0,121,34);
    etat_label->setText(etat);
    etat_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    etat_label->setMinimumHeight(34);

    id_label->setParent(row_container);
    id_label->setGeometry(240,0,101,34);
    id_label->setText(machineID);
    id_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    id_label->setMinimumHeight(34);


   prix_label->setParent(row_container);
   prix_label->setGeometry(520,0,131,34);
   prix_label->setText(prix);
   prix_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
   prix_label->setMinimumHeight(34);

    editBtn->setParent(row_container);
    editBtn->setGeometry(690,0,44,34);
    editBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/machine_img/edit-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    editBtn->setCursor(QCursor(Qt::PointingHandCursor));
    editBtn->setWhatsThis(machineID);

    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setParent(row_container);
    deleteBtn->setGeometry(785,0,44,34);
    deleteBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/machine_img/trash-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
    deleteBtn->setWhatsThis(machineID);


    connect(deleteBtn, &QPushButton::clicked, this, &machine_row_table::deleteBtn_clicked);


}
