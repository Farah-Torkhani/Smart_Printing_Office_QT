#include "commandes_row_table.h"
#include <QLabel>
commandes_row_table::commandes_row_table(QWidget *parent,QString descreption,QString etat,QString dateC, QString Quantite_Couleur, QString Quantite_sans_couleur,QString id): QLabel(parent)
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
       descreption_label->setParent(row_container);
           descreption_label->setGeometry(0,0,191,34);
           descreption_label->setText(descreption);
           descreption_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
           descreption_label->setMinimumHeight(34);



          etat_label->setParent(row_container);
              etat_label->setGeometry(191,0,141,34);
               etat_label->setText(etat);
               etat_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
               etat_label->setMinimumHeight(34);


           dateC_label->setParent(row_container);
               dateC_label->setGeometry(330,0,171,34);
               dateC_label->setText(dateC);
               dateC_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
               dateC_label->setMinimumHeight(34);

           QuantiteCouleur_label->setParent(row_container);
            QuantiteCouleur_label->setGeometry(500,0,131,34);
            QuantiteCouleur_label->setText(Quantite_Couleur);
            QuantiteCouleur_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
            QuantiteCouleur_label->setMinimumHeight(34);


            QuantiteSansCouleur_label->setParent(row_container);
           QuantiteSansCouleur_label->setGeometry(630,0,141,34);
           QuantiteSansCouleur_label->setText(Quantite_sans_couleur);
            QuantiteSansCouleur_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
          QuantiteSansCouleur_label->setMinimumHeight(31);

           editBtn->setParent(row_container);
            editBtn->setGeometry(690,0,44,34);
            editBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/img/ressources/img/edit-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
            editBtn->setCursor(QCursor(Qt::PointingHandCursor));
            editBtn->setWhatsThis(id);

           deleteBtn->setObjectName("deleteBtn");
              deleteBtn->setParent(row_container);
              deleteBtn->setGeometry(785,0,44,34);
              deleteBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/img/ressources/img/trash-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
              deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
              deleteBtn->setWhatsThis(id);



           connect(deleteBtn, &QPushButton::clicked, this, &commandes_row_table::deleteBtn_clicked);
           connect(editBtn, &QPushButton::clicked, this, &commandes_row_table::updateBtn_clicked);

}
