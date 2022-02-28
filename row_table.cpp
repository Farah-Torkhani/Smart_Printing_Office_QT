#include "row_table.h"
#include <QLabel>


Row_table::Row_table(QWidget *parent,QString cin,QString nom,QString prenom,QString dateEmb,QString salaire,QString role) : QLabel(parent)
{
    row_container->setGeometry(0,0,890,34);
    row_container->setStyleSheet("background-color: #F5F1F6;\
                             border-top-left-radius: 15px;\
                             border-bottom-left-radius: 15px;\
                             border-top-right-radius: 15px;\
                             border-bottom-right-radius: 15px;\
                             color: #341763;\
");

    row_container->setMinimumHeight(34);
    row_container->setFixedHeight(34);

    cin_label->setParent(row_container);
    cin_label->setGeometry(20,0,142,34);
    cin_label->setText(cin);
    cin_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    cin_label->setMinimumHeight(34);

    nom_label->setParent(row_container);
    nom_label->setGeometry(140,0,120,34);
    nom_label->setText(nom);
    nom_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    nom_label->setMinimumHeight(34);

    prenom_label->setParent(row_container);
    prenom_label->setGeometry(250,0,115,34);
    prenom_label->setText(prenom);
    prenom_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    prenom_label->setMinimumHeight(34);

    dateEmb_label->setParent(row_container);
    dateEmb_label->setGeometry(360,0,140,34);
    dateEmb_label->setText(dateEmb);
    dateEmb_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    dateEmb_label->setMinimumHeight(34);

    salaire_label->setParent(row_container);
    salaire_label->setGeometry(500,0,103,34);
    salaire_label->setText(salaire);
    salaire_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    salaire_label->setMinimumHeight(34);

    role_label->setParent(row_container);
    role_label->setGeometry(600,0,155,34);
    role_label->setText(role);
    role_label->setStyleSheet("color: #341763;font: 63 10pt 'Montserrat SemiBold';");
    role_label->setMinimumHeight(34);


    editBtn->setParent(row_container);
    editBtn->setGeometry(760,1,32,32);
    editBtn->setStyleSheet("QPushButton {background-color: #F5F1F6;border:none;border-radius:15px;qproperty-icon: url(:/resource/img/update.png);qproperty-iconSize: 17px;}QPushButton::hover {background-color: rgb(254, 129, 75);qproperty-icon: url(:/resource/img/update.png);qproperty-iconSize: 17px;}");
    editBtn->setCursor(QCursor(Qt::PointingHandCursor));
    editBtn->setWhatsThis(cin);
    editBtn->setWhatsThis(cin);


    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setParent(row_container);
    //deleteBtn->setGeometry(830,1,32,32);
    deleteBtn->setGeometry(760,1,32,32);
    deleteBtn->setStyleSheet("QPushButton {background-color: #F5F1F6;border:none;border-radius:15px;qproperty-icon: url(:/resource/img/delete.png);qproperty-iconSize: 18px;}QPushButton::hover {background-color: rgb(254, 129, 75);qproperty-icon: url(:/resource/img/delete.png);qproperty-iconSize: 18px;}");
    deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
    deleteBtn->setWhatsThis(cin);


}
