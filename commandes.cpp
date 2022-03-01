#include "commandes.h"
#include <QSqlQuery>


Commandes::Commandes(QString descreption, QString etat, QString quantiteCouleur, QString quantiteSansCouleur)
{

    this->descreption=descreption;
    this->etat=etat;
    this->quantiteCouleur=quantiteCouleur;
    this->quantiteSansCouleur=quantiteSansCouleur;



}
bool Commandes::ajouterCommandes()
{
    QSqlQuery query;

    query.prepare("Insert into commandes(descreption, etat, quantiteCouleur, quantiteSansCouleur)"
                  "Values(:descreption, :etat, :quantiteCouleur, :quantiteSansCouleur)");
    query.bindValue(":descreption", descreption);
    query.bindValue(":etat",etat);
    query.bindValue(":quantiteCouleur",quantiteCouleur);
    query.bindValue(":quantiteSansCouleur",quantiteSansCouleur);
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


