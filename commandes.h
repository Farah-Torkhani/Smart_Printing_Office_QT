#ifndef COMMANDES_H
#define COMMANDES_H
#include <QString>
#include <QDateEdit>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
class Commandes
{
public:
    Commandes();
    Commandes(QString descreption, QString etat, QString quantiteCouleur, QString quantiteSansCouleur);

    QString getDescreption(){return descreption;}
    QString getEtat(){return etat;}
    QString getQuantiteCouleur(){return  quantiteCouleur;}
    QString getQuantiteSansCouleur(){return quantiteSansCouleur;}
    bool ajouterCommandes();
     QSqlQuery afficherCommande();
         bool supprimerCommandes(int Commandesid);

         QSqlQuery afficherCommande(int id);
         bool modifierCommande(int id);
private:

    QString descreption;
    QString etat;
    QString quantiteCouleur;
    QString quantiteSansCouleur;


};

#endif // COMMANDES_H
