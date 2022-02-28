#include "client_row_table.h"
#include <QLabel>

Client_row_table::Client_row_table(QWidget *parent,QString cinClient, QString nomClient, QString prenomClient, QString emailClient, QString telClient) : QLabel(parent)
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
    nom_label->setText(nomClient);
    nom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    nom_label->setMinimumHeight(34);


    prenom_label->setParent(row_container);
    prenom_label->setGeometry(120,0,121,34);
    prenom_label->setText(prenomClient);
    prenom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    prenom_label->setMinimumHeight(34);

    cin_label->setParent(row_container);
    cin_label->setGeometry(240,0,101,34);
    cin_label->setText(cinClient);
    cin_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    cin_label->setMinimumHeight(34);

    email_label->setParent(row_container);
    email_label->setGeometry(340,0,181,34);
    email_label->setText(emailClient);
    email_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    email_label->setMinimumHeight(31);

    tell_label->setParent(row_container);
    tell_label->setGeometry(520,0,131,34);
    tell_label->setText(telClient);
    tell_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    tell_label->setMinimumHeight(34);

    //editBtn->setObjectName("updateBtn");
    editBtn->setParent(row_container);
    editBtn->setGeometry(690,0,44,34);
    editBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/client_img/edit-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    editBtn->setCursor(QCursor(Qt::PointingHandCursor));
    editBtn->setWhatsThis(cinClient);
    editBtn->setWhatsThis(cinClient);


    emailBtn->setParent(row_container);
    emailBtn->setGeometry(740,0,44,34);
    emailBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/client_img/email.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    emailBtn->setCursor(QCursor(Qt::PointingHandCursor));
    emailBtn->setWhatsThis(cinClient);

    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setParent(row_container);
    deleteBtn->setGeometry(785,0,44,34);
    deleteBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/client_img/trash-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
    deleteBtn->setWhatsThis(cinClient);


    connect(deleteBtn, &QPushButton::clicked, this, &Client_row_table::deleteBtn_clicked);
    connect(editBtn, &QPushButton::clicked, this, &Client_row_table::updateBtn_clicked);


}
