#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Employees
{
private:
    int cin;
    QString nom;
    QString prenom;
    QString email;
    QString password;
    QString numCard;
    int tel;
    int salaire;
    QString dateEmb;
    QString role;


public:
    Employees();
    Employees(int cin,QString nom,QString prenom,QString email,QString password,QString numCard,int tel,int salaire,QString role);
    Employees(QString email,QString password);
    Employees(QString numCard);

    bool ajouterEmp();
    QSqlQuery afficherAllEmp();
    QSqlQuery afficherEmp(int cin);
    bool modifierEmp();
    bool supprimerEmp(int cin);
    QSqlQuery rechercheEmp(QString test);
    QSqlQuery trieEmp(QString test);
    bool authEmp();
    bool authEmpCardRfid();
    QSqlQuery afficherEmp(QString email);
    QSqlQuery afficherEmpByCardNum(QString numCard);

    int statEmp(int month);

    int getCin(){
        return cin;
    }
    QString getNom(){
        return nom;
    }
    QString getPrenom(){
        return prenom;
    }
    QString getRole(){
        return role;
    }
    QString getCard(){
        return numCard;
    }

};

#endif // EMPLOYEES_H
