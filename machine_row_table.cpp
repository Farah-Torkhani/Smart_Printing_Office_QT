#include "machine_row_table.h"
#include <QLabel>
#include <QPainter>
#include <QDebug>

Machine_row_table::Machine_row_table(QWidget *parent ,QString machineId,QString nomMachine, QString machineImg, QString prixMachine, QString etatMachine) : QLabel(parent)
{
    row_container->setGeometry(3,0,840,64);
    row_container->setStyleSheet("background-color: white;\
                             border-top-left-radius: 15px;\
                             border-bottom-left-radius: 15px;\
                             border-top-right-radius: 15px;\
                             border-bottom-right-radius: 15px;\
                             color: #585856;\
");


   row_container->setMinimumHeight(64);
   row_container->setFixedHeight(64);

   img_label->setParent(row_container);
   img_label->setGeometry(0,0,121,64);

   QPixmap image (machineImg);
   img_label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
   image = image.scaled(121,64,Qt::IgnoreAspectRatio,Qt::FastTransformation);

   img_label->setPixmap(image);

   img_label->setMinimumHeight(64);

   nom_label->setParent(row_container);
   nom_label->setGeometry(120,0,121,64);
   nom_label->setText(nomMachine);
   nom_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
   nom_label->setMinimumHeight(64);

   prix_label->setParent(row_container);
   prix_label->setGeometry(240,0,101,64);
   prix_label->setText(prixMachine);
   prix_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
   prix_label->setMinimumHeight(64);

   etat_label->setParent(row_container);
   etat_label->setGeometry(330,0,181,64);
 //  qDebug() <<"etatMachine="<< etatMachine;
   if(etatMachine.toInt() == 1)
   {
       etat_label->setText("bon");
       etat_label->setStyleSheet("color: #03BF8A;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
   }
   else if(etatMachine.toInt() == 0)
   {
       etat_label->setText("panne");
       etat_label->setStyleSheet("color: #f53e00;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
   }
   etat_label->setMinimumHeight(64);

   repaireBtn->setParent(row_container);
   repaireBtn->setGeometry(440,0,54,64);
   repaireBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Machine_resources/img_m/spanner.png);qproperty-iconSize: 24px;}QPushButton::hover {background-color: #D6DBFD;}");
   repaireBtn->setCursor(QCursor(Qt::PointingHandCursor));
   repaireBtn->setWhatsThis(machineId);
   repaireBtn->setWhatsThis(machineId);

   historiqueBtn->setParent(row_container);
   historiqueBtn->setGeometry(540,0,54,64);
   historiqueBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Machine_resources/img_m/eye.png);qproperty-iconSize: 24px;}QPushButton::hover {background-color: #D6DBFD;}");
   historiqueBtn->setCursor(QCursor(Qt::PointingHandCursor));
   historiqueBtn->setWhatsThis(machineId);
   historiqueBtn->setWhatsThis(machineId);

   editBtn->setParent(row_container);
   editBtn->setGeometry(650,0,54,64);
   editBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Machine_resources/img_m/edit-icon.png);qproperty-iconSize: 22px;}QPushButton::hover {background-color: #D6DBFD;}");
   editBtn->setCursor(QCursor(Qt::PointingHandCursor));
   editBtn->setWhatsThis(machineId);
   editBtn->setWhatsThis(machineId);

   deleteBtn->setObjectName("deleteBtn");
   deleteBtn->setParent(row_container);
   deleteBtn->setGeometry(710,0,54,64);
   deleteBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Machine_resources/img_m/trash-icon.png);qproperty-iconSize: 22px;}QPushButton::hover {background-color: #D6DBFD;}");
   deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
   deleteBtn->setWhatsThis(machineId);

   arduinoBtn->setObjectName("arduinoBtn");
   arduinoBtn->setParent(row_container);
   arduinoBtn->setGeometry(770,0,54,64);
   arduinoBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/Machine_resources/img_m/customer-support.png);qproperty-iconSize: 22px;}QPushButton::hover {background-color: #D6DBFD;}");
   arduinoBtn->setCursor(QCursor(Qt::PointingHandCursor));
   arduinoBtn->setWhatsThis(machineId);





   connect(deleteBtn, &QPushButton::clicked, this, &Machine_row_table::deleteBtn_clicked);
   connect(editBtn, &QPushButton::clicked, this, &Machine_row_table::updateBtn_clicked);
   connect(repaireBtn, &QPushButton::clicked, this, &Machine_row_table::repaireBtn_clicked);
   connect(historiqueBtn, &QPushButton::clicked, this, &Machine_row_table::historiqueBtn_clicked);
   connect(arduinoBtn, &QPushButton::clicked, this, &Machine_row_table::arduinoBtn_clicked);


}
