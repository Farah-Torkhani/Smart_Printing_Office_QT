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

    bool ajouterEmp();
    QSqlQuery afficherAllEmp();
    QSqlQuery afficherEmp(int cin);

};

#endif // EMPLOYEES_H
