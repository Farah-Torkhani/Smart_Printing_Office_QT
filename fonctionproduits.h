#ifndef FONCTIONPRODUITS_H
#define FONCTIONPRODUITS_H



#include<QSqlQueryModel>
//#include<QSqlQuery>
#include <QCoreApplication>
#include <QtSql/QSqlQuery>






class Produits
{
private:
    int PRODUITID;
    QString nomProduit,type,quantite,prixunitaire;


public:
    Produits();
    Produits(QString,QString,QString,QString);
    QString getNomProduit(){return nomProduit;}
    QString getNomType(){return type;}
    QString getQuantite(){return quantite;}
    QString getPrix(){return prixunitaire;}
    int getID(){return PRODUITID;}

    void setNomProduit(QString n){nomProduit=n;}
    void setType(QString t){type=t;}
    void setQuantite(QString q){quantite=q;}
    void setPrix(QString p){prixunitaire=p;}
    void setID(int id){this->PRODUITID=id;}

    bool ajouter();
    QSqlQuery  afficher();
    QSqlQuery  afficherAll();
    QSqlQuery afficherPr(int id);
    QSqlQueryModel * trier();
    bool supprimer(int);
    bool modifier(int id);

    bool supprimerTout();



};

#endif // FONCTIONPRODUITS_H
