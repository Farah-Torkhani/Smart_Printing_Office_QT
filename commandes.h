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
    Commandes(QString descreption, int quantiteCouleur, QString quantiteSansCouleur,int cinclient,QString date_Fin);

    QString getDescreption(){return descreption;}
    int getQuantiteCouleur(){return  quantiteCouleur;}
    QString getQuantiteSansCouleur(){return quantiteSansCouleur;}
    bool ajouterCommandes();
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
          void repaireDateFinCommande(int idCommande);


private:
    QString descreption;
    int quantiteCouleur;
    QString quantiteSansCouleur;
    int cinclient;
    QString date_Fin;

};

#endif // COMMANDES_H
