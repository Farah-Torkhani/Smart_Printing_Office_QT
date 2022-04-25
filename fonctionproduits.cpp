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
bool Produits::ajouterf(QString data)
{
    QSqlQuery query;


        query.prepare("insert into flamme (degree)""values(:degree)");
query.bindValue(":degree",data);
        return  query.exec();
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



QSqlQuery Produits::afficherP()
{
    QSqlQuery query;
    query.exec("select * from PRODUITS");
    return query;
}
QSqlQuery Produits::afficherHistorique()
{
    QSqlQuery query;
    query.exec("select DATE_F from FLAMME");
    return query;
}
QSqlQuery Produits::afficherAllP()
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

QSqlQuery Produits::rechercher(QString chaine)
{

    QSqlQuery query;

    query.exec("SELECT * from PRODUITS where PRODUITID LIKE'"+chaine+"%' OR NOMPRODUIT LIKE'"+chaine+"%' OR QUANTITE LIKE'"+chaine+"%' OR TYPE LIKE'"+chaine+"%' OR PRIXUNITAIRE LIKE'"+chaine+"%' ");
    return query;


}
QStringList Produits::rechercherP()
{
    QSqlQuery query;
    query.exec("SELECT * from PRODUITS");
    QStringList CompletionList;
    while(query.next())
    {
    CompletionList << query.value(0).toString();
    return CompletionList;
    }
}

QSqlQueryModel * Produits::affichertr()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from PRODUITS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("PRODUITID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOMPRODUIT"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("QUANTITE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("PRIXUNITAIRE"));
    return model;
}
QSqlQueryModel * Produits::afficherProduitForExcel()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from PRODUITS");

    return model ;
}


int Produits::statistiqueProduits(int nom)
{
    QSqlQuery query;
    query.prepare("select count(*) from PRODUITS where PRIXUNITAIRE=:nom ");
    query.bindValue(":nom",nom);
    return query.exec();

    int count =-1;





            while(query.next())
                    {
                        count=query.value(0).toInt() ;
                    }

    return count;

}
int Produits::statistiquesProduits(int month)
{
    QSqlQuery query;
    query.prepare("select count(*) from produits where extract(month from DATEP)=:month ");
    query.bindValue(":month",month);
    query.exec();
    query.next();

    return query.value(0).toInt();

}

