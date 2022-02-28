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

bool Employees::ajouterEmp()
{
    QSqlQuery query;

        query.prepare("INSERT all INTO EMPLOYEES (cin, nom, prenom, tel, salaire,role) VALUES (:cin, :nom, :prenom, :tel, :salaire, :role) INTO COMPTES (email, password, num_card, cin) VALUES (:email, :password, :num_card, :cin) SELECT * FROM dual;");
        query.bindValue(":cin",cin);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":tel",tel);
        query.bindValue(":salaire",salaire);
        query.bindValue(":role",role);

        query.bindValue(":email",email);
        query.bindValue(":password",password);
        query.bindValue(":num_card",numCard);

        return query.exec();
}

QSqlQuery Employees::afficherAllEmp()
{
    QSqlQuery query;
    query.exec("select * from employees");
    return query;
}

QSqlQuery Employees::afficherEmp(int cin)
{
    QSqlQuery query;
    query.prepare("select * from employees inner join COMPTES on employees.cin = COMPTES.cin where employees.cin=:cin");
    query.bindValue(":cin",cin);
    query.exec();
    return query;
}


