#include "row_table_produits.h"
#include <QLabel>
#include <string.h>

row_table_produits::row_table_produits(){}


row_table_produits::row_table_produits(QWidget *parent,QString id,QString nomP,QString quantite,QString type,QString prixU) : QLabel(parent)
{
    row_container->setGeometry(0,0,750,51);
    row_container->setStyleSheet("background-color: #F5F1F6;\
                             border-top-left-radius: 15px;\
                             border-bottom-left-radius: 15px;\
                             border-top-right-radius: 15px;\
                             border-bottom-right-radius: 15px;\
                             color: #341763;\
");

    row_container->setMinimumHeight(51);
    row_container->setFixedHeight(51);

    nomP_label->setParent(row_container);
    nomP_label->setGeometry(20,-7,121,51);
    nomP_label->setText(nomP);
    nomP_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    nomP_label->setMinimumHeight(34);

    type_label->setParent(row_container);
    type_label->setGeometry(150,-7,121,51);
    type_label->setText(type);
    type_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    type_label->setMinimumHeight(34);

    quantite_label->setParent(row_container);
    quantite_label->setGeometry(400,-7,81,51);
    quantite_label->setText(quantite);
    quantite_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    quantite_label->setMinimumHeight(34);

    prixU_label->setParent(row_container);
    prixU_label->setGeometry(280,-7,91,51);
    prixU_label->setText(prixU);
    prixU_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    prixU_label->setMinimumHeight(34);



    qrGBtn->setParent(row_container);
    qrGBtn->setGeometry(515,0,31,31);
    qrGBtn->setStyleSheet("QPushButton {background-color: #F5F1F6;border:none;border-radius:15px;qproperty-icon: url(:/resources/img/update.png);qproperty-iconSize: 17px;}QPushButton::hover {background-color: rgb(254, 129, 75);qproperty-icon: url(:/resource/img/update.png);qproperty-iconSize: 17px;}");
    qrGBtn->setCursor(QCursor(Qt::PointingHandCursor));
    qrGBtn->setWhatsThis(id);



    editBtn->setParent(row_container);
    editBtn->setGeometry(600,0,31,31);
    editBtn->setStyleSheet("QPushButton {background-color: #F5F1F6;border:none;border-radius:15px;qproperty-icon: url(:/resources/img/update.png);qproperty-iconSize: 17px;}QPushButton::hover {background-color: rgb(254, 129, 75);qproperty-icon: url(:/resource/img/update.png);qproperty-iconSize: 17px;}");
    editBtn->setCursor(QCursor(Qt::PointingHandCursor));
    editBtn->setWhatsThis(id);



    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setParent(row_container);
    deleteBtn->setGeometry(640,0,31,31);
    deleteBtn->setStyleSheet("QPushButton {background-color: #F5F1F6;border:none;border-radius:15px;qproperty-icon: url(:/resources/img/delete.png);qproperty-iconSize: 18px;}QPushButton::hover {background-color: rgb(254, 129, 75);qproperty-icon: url(:/resource/img/delete.png);qproperty-iconSize: 18px;}");
    deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
    deleteBtn->setWhatsThis(id);

    connect(deleteBtn, &QPushButton::clicked, this, &row_table_produits::deleteBtn_clicked);
    connect(editBtn, &QPushButton::clicked, this, &row_table_produits::editBtn_clicked);
    connect(qrGBtn, &QPushButton::clicked, this, &row_table_produits::qrGBtn_clicked);


}

