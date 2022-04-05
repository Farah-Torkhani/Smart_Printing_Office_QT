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
    Commandes(QString descreption, QString etat, int quantiteCouleur, QString quantiteSansCouleur , int cinemp,int cinclient );

    QString getDescreption(){return descreption;}
    QString getEtat(){return etat;}
    int getQuantiteCouleur(){return  quantiteCouleur;}
    QString getQuantiteSansCouleur(){return quantiteSansCouleur;}
    bool ajouterCommandes(QString date_fin);
     QSqlQuery afficherCommande();
         bool supprimerCommandes(int Commandesid);

         QSqlQuery afficherCommande(int id);
         bool modifierCommande(int id);
        QSqlQuery triCommande(QString test);
        QSqlQuery rechercherCommande(QString chaine);
        QStringList rechercherCommandes();
        int statistiqueCommande(int month);
          QSqlQuery editview(QString);

          int dateFin(int idCommande);



private:

    QString descreption;
    QString etat;
    int quantiteCouleur;
    QString quantiteSansCouleur;
    int cinemp;
    int cinclient;

};

#endif // COMMANDES_H
