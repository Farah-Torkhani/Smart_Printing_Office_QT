#include "arduino_sms_row_table.h"
#include <QLabel>

#include "arduino_client.h"

Arduino_sms_row_table::Arduino_sms_row_table(QWidget *parent,QString cinEmp, QString nomEmp, QString prenomEmp, QString roleEmp, QString telEmp): QLabel(parent)
{
    row_container->setGeometry(3,0,600,34);
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
    nom_label->setText(nomEmp);
    nom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    nom_label->setMinimumHeight(34);


    prenom_label->setParent(row_container);
    prenom_label->setGeometry(121,0,121,34);
    prenom_label->setText(prenomEmp);
    prenom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    prenom_label->setMinimumHeight(34);

    role_label->setParent(row_container);
    role_label->setGeometry(242,0,121,34);
    role_label->setText(roleEmp);
    role_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    role_label->setMinimumHeight(31);

    tell_label->setParent(row_container);
    tell_label->setGeometry(363,0,121,34);
    tell_label->setText(telEmp);
    tell_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
    tell_label->setMinimumHeight(34);
    //-----------------
    callBtn->setParent(row_container);
    callBtn->setGeometry(484,0,44,34);
    callBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/client_img/phone-call.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
    callBtn->setCursor(QCursor(Qt::PointingHandCursor));
    callBtn->setWhatsThis(cinEmp);

    smsBtn->setParent(row_container);
    smsBtn->setGeometry(535,0,44,34);
    smsBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Resources/client_img/speech-bubble.png);qproperty-iconSize: 20px;}QPushButton::hover {background-color: #D6DBFD;}");
    smsBtn->setCursor(QCursor(Qt::PointingHandCursor));
    smsBtn->setWhatsThis(cinEmp);
    //-----------------

    connect(callBtn, &QPushButton::clicked, this, &Arduino_sms_row_table::callEmpBtn_clicked);
    connect(smsBtn, &QPushButton::clicked, this, &Arduino_sms_row_table::smsEmpBtn_clicked);

    //connect(callBtn, &QPushButton::clicked, this, &Arduino_client::on_call_btn_clicked());

 //   A.connect_arduino();

}


Arduino_sms_row_table::Arduino_sms_row_table(QString test)
{
    //
}
