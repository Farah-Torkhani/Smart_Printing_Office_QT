#include "commandes_row_table.h"
#include <QLabel>
#include "commandes.h"

commandes_row_table::commandes_row_table(QWidget *parent, QString dateC, QString Quantite_Couleur, QString Quantite_sans_couleur,QString id, QString etat): QLabel(parent)
{
    row_container->setGeometry(3,0,830,34);
       row_container->setStyleSheet("background-color: white;\
                                border-top-left-radius: 15px;\
                                border-bottom-left-radius: 15px;\
                                border-top-right-radius: 15px;\
                                border-bottom-right-radius: 15px;\
                                color: #585856;\
   ");
       row_container->setMinimumHeight(34);
       row_container->setFixedHeight(34);

           descreptionBtn->setParent(row_container);
            descreptionBtn->setGeometry(25,0,44,34);
            descreptionBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/eye.png);qproperty-iconSize: 24px;}QPushButton::hover {background-color: #D6DBFD;}");
            descreptionBtn->setCursor(QCursor(Qt::PointingHandCursor));
            descreptionBtn->setWhatsThis(id);

            dateC_label->setParent(row_container);
            dateC_label->setGeometry(130,0,171,34);
            dateC_label->setText(dateC);
            dateC_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
            dateC_label->setMinimumHeight(34);



               //tester date fin
               QString desc="";
               int quantiteCouleur=0;
               QString quantiteSansCouleur="";
               int cinclient=0;
               QString date_Fin="";
               Commandes c(desc,quantiteCouleur,quantiteSansCouleur,cinclient, date_Fin);

                 int terminee=etat.toInt();
                // terminee = 1;
                 int testDate= c.dateFin(id.toInt());


                 if(terminee == 1)
                 {
                     if(testDate >= 0)
                        {
                           etatBtn->setParent(row_container);
                           etatBtn->setGeometry(240,0,171,34);
                           etatBtn->setText("terminee");
                           etatBtn->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
                           etatBtn->setMinimumHeight(34);
                        }
                     else if(testDate < 0)
                        {
                           etatBtn->setParent(row_container);
                           etatBtn->setGeometry(245,0,171,34);
                           etatBtn->setText("terminee en retard");
                           etatBtn->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
                           etatBtn->setMinimumHeight(34);
                        }

                 }
                 else if(terminee == 0)
                 {
                      etatBtn->setObjectName("etatBtn");
                      etatBtn->setParent(row_container);
                      etatBtn->setGeometry(300,0,44,34);
                      etatBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/clock.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
                      etatBtn->setCursor(QCursor(Qt::PointingHandCursor));
                      etatBtn->setWhatsThis(id);
                 }


           QuantiteCouleur_label->setParent(row_container);
            QuantiteCouleur_label->setGeometry(450,0,171,34);
            QuantiteCouleur_label->setText(Quantite_Couleur);
            QuantiteCouleur_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
            QuantiteCouleur_label->setMinimumHeight(34);


            QuantiteSansCouleur_label->setParent(row_container);
           QuantiteSansCouleur_label->setGeometry(555,0,100,34);
           QuantiteSansCouleur_label->setText(Quantite_sans_couleur);
            QuantiteSansCouleur_label->setStyleSheet("color: #585856;padding:6px;font: 63 10pt 'Montserrat SemiBold';");
          QuantiteSansCouleur_label->setMinimumHeight(31);

           editBtn->setParent(row_container);
            editBtn->setGeometry(640,0,44,34);
            editBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/edit-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
            editBtn->setCursor(QCursor(Qt::PointingHandCursor));
            editBtn->setWhatsThis(id);

           deleteBtn->setObjectName("deleteBtn");
              deleteBtn->setParent(row_container);
              deleteBtn->setGeometry(685,0,44,34);
              deleteBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/trash-icon.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
              deleteBtn->setCursor(QCursor(Qt::PointingHandCursor));
              deleteBtn->setWhatsThis(id);


                imprimerBtn->setObjectName("imprimerBtn");
                 imprimerBtn->setParent(row_container);
                 imprimerBtn->setGeometry(730,0,44,34);
                 imprimerBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/imprimante.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
                 imprimerBtn->setCursor(QCursor(Qt::PointingHandCursor));
                 imprimerBtn->setWhatsThis(id);

                 repaireBtn->setParent(row_container);
                 repaireBtn->setGeometry(775,0,44,34);
                 repaireBtn->setStyleSheet("QPushButton {background-color: white;border:none;border-radius:15px;qproperty-icon: url(:/resource/imgCommande/spanner.png);qproperty-iconSize: 19px;}QPushButton::hover {background-color: #D6DBFD;}");
                 repaireBtn->setCursor(QCursor(Qt::PointingHandCursor));
                 repaireBtn->setWhatsThis(id);
                 repaireBtn->setWhatsThis(id);


           connect(deleteBtn, &QPushButton::clicked, this, &commandes_row_table::deleteBtn_clicked);
           connect(editBtn, &QPushButton::clicked, this, &commandes_row_table::updateBtn_clicked);
            connect(imprimerBtn, &QPushButton::clicked, this, &commandes_row_table::imprimerBtn_clicked);
            connect(etatBtn, &QPushButton::clicked, this, &commandes_row_table::etatBtn_clicked);
            connect(descreptionBtn, &QPushButton::clicked, this, &commandes_row_table::descreptionBtn_clicked);
            connect(repaireBtn, &QPushButton::clicked, this, &commandes_row_table::repaireBtn_clicked);


}



