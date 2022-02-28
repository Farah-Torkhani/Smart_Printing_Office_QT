#include "fonctionproduits.h"


Produits::Produits(){

}


Produits::Produits(QString nomProduit,QString quantite ,QString type,QString prixunitaire)
{
    this->nomProduit=nomProduit;
    this->quantite=quantite;
    this->type=type;
    this->prixunitaire=prixunitaire;



}

bool Produits::ajouter()
{ QSqlQuery query;


    query.prepare("insert into produits (nomProduit,quantite,type,prixunitaire)""values(:nomProduit,:quantite,:type,:prixunitaire)");


    query.bindValue(":nomProduit",nomProduit);
    query.bindValue(":quantite",quantite);
    query.bindValue(":type",type);
    query.bindValue(":prixunitaire",prixunitaire);




    return  query.exec();
}



QSqlQuery Produits::afficher()
{
    QSqlQuery query;
    query.exec("select * from PRODUITS");
    return query;
}
QSqlQuery Produits::afficherAll()
{
    QSqlQuery query;
    query.exec("select * from PRODUITS");
    return query;
}

QSqlQuery Produits::afficherPr(int id)
{
    QSqlQuery query;
    query.prepare("select * from PRODUITS where PRODUITID=:id");
    query.bindValue(":id",id);
    query.exec();
    return query;
}



bool Produits::modifier(int PRODUITID)
{  QSqlQuery query;
    query.prepare("update PRODUITS set nomProduit=:nomProduit, quantite=:quantite, type=:type, prixunitaire=:prixunitaire where PRODUITID=:PRODUITID");
    query.bindValue(":nomProduit",nomProduit);
    query.bindValue(":quantite",quantite);
    query.bindValue(":type",type);
    query.bindValue(":prixunitaire",prixunitaire);
    query.bindValue(":PRODUITID",PRODUITID);
    return  query.exec();
}

bool Produits::supprimer(int id)
{


  QSqlQuery query;
  QString res = QString::number(id);

  query.prepare("Delete from Produits where PRODUITID= :id");
  query.bindValue(":id",res);

  return query.exec();
}



bool Produits::supprimerTout()
{ QSqlQuery query;

   query.prepare("delete from Produits ");

  return query.exec();
}
