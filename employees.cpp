#include "employees.h"

Employees::Employees()
{

}

Employees::Employees(int cin,QString nom,QString prenom,QString email,QString password,QString numCard,int tel,int salaire,QString role)
{
    this->cin = cin;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->password = password;
    this->numCard = numCard;
    this->tel = tel;
    this->salaire = salaire;
    this->role = role;
}

QSqlQuery Employees::afficherAllEmp()
{
    QSqlQuery query;
    query.exec("select * from employees");
    return query;
}
