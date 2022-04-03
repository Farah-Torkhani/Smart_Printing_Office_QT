#include "commandes.h"
#include <QSqlQuery>


Commandes::Commandes(QString descreption, QString etat, int quantiteCouleur, QString quantiteSansCouleur , int cinemp,int cinclient )
{

    this->descreption=descreption;
    this->etat=etat;
    this->quantiteCouleur=quantiteCouleur;
    this->quantiteSansCouleur=quantiteSansCouleur;
    this->cinemp=cinemp;
    this->cinclient=cinclient;


}
bool Commandes::ajouterCommandes()
{
    QSqlQuery query;

    query.prepare("Insert into commandes(descreption, etat, quantiteCouleur, quantiteSansCouleur,cinemp,cinclient)"
                  "Values(:descreption, :etat, :quantiteCouleur, :quantiteSansCouleur,:cinemp,:cinclient)");
    query.bindValue(":descreption", descreption);
    query.bindValue(":etat",etat);
    query.bindValue(":quantiteCouleur",quantiteCouleur);
    query.bindValue(":quantiteSansCouleur",quantiteSansCouleur);
    query.bindValue(":cinemp",cinemp);
    query.bindValue(":cinclient",cinclient);
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


    query.prepare("update commandes set descreption=:descreption, etat=:etat, quantiteCouleur=:quantiteCouleur, quantiteSansCouleur=:quantiteSansCouleur where Commandeid=:Commandeid");
    query.bindValue(":descreption", descreption);
    query.bindValue(":etat",etat);
    query.bindValue(":quantiteCouleur",quantiteCouleur);
    query.bindValue(":quantiteSansCouleur",quantiteSansCouleur);
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

