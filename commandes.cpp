#include "commandes.h"
#include "date_fin.h"
#include <QSqlQuery>
#include <QDate>
#include <QDebug>




Commandes::Commandes(QString descreption, int quantiteCouleur, QString quantiteSansCouleur ,int cinclient, QString date_Fin)
{
    this->descreption=descreption;
    this->quantiteCouleur=quantiteCouleur;
    this->quantiteSansCouleur=quantiteSansCouleur;
    this->cinclient=cinclient;
    this->date_Fin=date_Fin;
}
bool Commandes::ajouterCommandes()
{
    QSqlQuery query;

    query.prepare("Insert into commandes(descreption, quantiteCouleur, quantiteSansCouleur, cinclient, date_fin, etatCommande)"
                  "Values(:descreption, :quantiteCouleur, :quantiteSansCouleur, :cinclient, :date_fin, :etatCommande)");
    query.bindValue(":descreption", descreption);
    query.bindValue(":quantiteCouleur",quantiteCouleur);
    query.bindValue(":quantiteSansCouleur",quantiteSansCouleur);
    query.bindValue(":cinclient",cinclient);
    query.bindValue(":date_fin",date_Fin);
    query.bindValue(":etatCommande",0);
    return query.exec();
}

QSqlQuery Commandes::afficherCommande()
{
    QSqlQuery query;
    query.exec("select * from commandes");
    return query;
}

bool Commandes::supprimerCommandes(int Commandesid)
{
  QSqlQuery query;
  QString id = QString::number(Commandesid);

  query.prepare("Delete from commandes where Commandeid=:Commandeid");
  query.bindValue(":Commandeid",id);
  return query.exec();

}



QSqlQuery Commandes::afficherCommande(int id)
{
    QSqlQuery query;
    query.prepare("select * from commandes where Commandeid=:Commandeid");
    query.bindValue(":Commandeid",id);

    query.exec();
    return query;
}



bool Commandes::modifierCommande(int Commandeid)
{
    QSqlQuery query;
    query.prepare("update commandes set descreption=:descreption, quantiteCouleur=:quantiteCouleur, quantiteSansCouleur=:quantiteSansCouleur, date_Fin=:date_Fin, cinClient=:cinClient where Commandeid=:Commandeid");
    query.bindValue(":descreption", descreption);
    query.bindValue(":quantiteCouleur",quantiteCouleur);
    query.bindValue(":quantiteSansCouleur",quantiteSansCouleur);
    query.bindValue(":date_Fin", date_Fin);
    query.bindValue(":cinClient", cinclient);
    query.bindValue(":Commandeid",Commandeid);

    return query.exec();
}


QSqlQuery Commandes::triCommande(QString test)
{
    QSqlQuery query;
    if(test == "par défaut"){
         query.exec("select * from commandes");
       }
    else if(test == "date"){
           query.exec("select * from commandes order by date_commande desc");
    }
    else if(test == "etat"){
           query.exec("select * from commandes order by etat");
    }
    else if(test == "quantiteCouleur"){
           query.exec("select * from commandes order by QUANTITECOULEUR desc");
    }

    return query;
}



//**************************recherche*****************************
QSqlQuery Commandes::rechercherCommande(QString chaine)
{

    QSqlQuery query;


    query.exec("SELECT * from commandes where CommandeId LIKE'%"+chaine+"%' OR descreption LIKE'%"+chaine+"%'   ");
    return query;


}

QStringList Commandes::rechercherCommandes()
{

    QSqlQuery query;
    QStringList cblist;

    query.prepare("select * from commandes ");
    query.exec();

    QString n;
    while(query.next())
            {
               // if (query.isValid())
                cblist.push_back(query.value(0).toString() );
                cblist.push_back(query.value(1).toString() );
               // cblist.push_back(query.value(2).toString() );
               // cblist.push_back(query.value(3).toString() );
               // cblist.push_back(query.value(4).toString() );
             //   qDebug() << "test";

            }


    return  cblist;


}

//**************************recherche*****************************


//*******************************statistique Commande********************************************************

int Commandes::statistiqueCommande(int month)
{
    QSqlQuery query;
    query.prepare("select count(*) from commandes where extract(month from date_commande)=:month ");
    query.bindValue(":month",month);
    query.exec();

    int count =50;



        QString cblist;

            while(query.next())
                    {
                        cblist=query.value(0).toString() ;

                        count = cblist.toInt();
//                        qDebug() << "count=" << count ;
                    }

    return count;

}


int Commandes::dateFin(int idCommande)
{
    QSqlQuery query;
    query.prepare("select date_fin, date_commande from commandes where Commandeid=:Commandeid");

    query.bindValue(":Commandeid",idCommande);

    query.exec();

    query.next();

   QString dateF=query.value(0).toString();
   QDate dateff = QDate::fromString(dateF,"dd/MM/yyyy");

    QDate dateFF(2022,4,7);
    QDate dateD=query.value(1).toDate();



   int c=dateD.daysTo(dateff);

   qDebug() << dateff  <<dateD<<c;
    return c;
}


void Commandes::repaireDateFinCommande(int idCommande)
{
    QSqlQuery query;
    query.prepare("select etatCommande from commandes where Commandeid=:Commandeid");
    query.bindValue(":Commandeid",idCommande);
    query.exec();

    query.next();
    int etatCommande = query.value(0).toInt();
    if(etatCommande == 1)
    {
        query.prepare("update commandes set etatCommande=:etatCommande where Commandeid=:Commandeid");
        query.bindValue(":etatCommande", 0);
        query.bindValue(":Commandeid",idCommande);
        query.exec();

    }
    else if(etatCommande == 0)
    {
        query.prepare("update commandes set etatCommande=:etatCommande where commandeId=:commandeId");
        query.bindValue(":etatCommande",1);
        query.bindValue(":commandeId",idCommande);
        query.exec();

    }
}
