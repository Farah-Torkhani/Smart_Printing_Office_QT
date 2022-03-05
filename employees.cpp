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

Employees::Employees(QString email,QString password)
{
    this->email = email;
    this->password = password;
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
        query.bindValue(":role",role.toLower());

        query.bindValue(":email",email.toLower());
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

bool Employees::modifierEmp()
{
    QSqlQuery query,query2,query3;
    query.prepare("update EMPLOYEES set nom=:nom, prenom=:prenom, tel=:tel, salaire=:salaire, role=:role  where cin=:cin");
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel);
    query.bindValue(":salaire",salaire);
    query.bindValue(":role",role.toLower());
    query.bindValue(":cin",cin);

    query2.prepare("update COMPTES set email=:email, password=:password, num_card=:num_card  where cin=:cin");
    query2.bindValue(":email",email.toLower());
    query2.bindValue(":password",password);
    query2.bindValue(":num_card",numCard);
    query2.bindValue(":cin",cin);

    query3.prepare("select * from employees inner join COMPTES on employees.cin = COMPTES.cin where employees.cin=:cin");
    query3.bindValue(":cin",cin);
    query3.exec();
    if(!query3.next()){
        return false;
    }

    return query.exec() && query2.exec();
}

bool Employees::supprimerEmp(int cin)
{
    QSqlQuery query,query2;
    query.prepare("Delete from employees where cin=:cin");
    query2.prepare("Delete from COMPTES where cin=:cin");
    query.bindValue(":cin",cin);
    query2.bindValue(":cin",cin);
    return query2.exec() && query.exec();
}

QSqlQuery Employees::rechercheEmp(QString test)
{
    QSqlQuery query;
    query.exec("select * from employees where (UPPER(nom) like UPPER('%"+test+"%') or UPPER(prenom) like UPPER('%"+test+"%') )");
    return query;
}

QSqlQuery Employees::trieEmp(QString test)
{
    QSqlQuery query;
    if(test == "par défaut"){
        query.exec("select * from employees");
    }
    else if(test == "nom"){
        query.exec("select * from employees order by nom");
    }else if (test == "date_emb") {
        query.exec("select * from employees order by DATE_EMB desc");
    } else if (test == "salaire") {
        query.exec("select * from employees order by salaire");
    }

    return query;
}


bool Employees::authEmp()
{
    bool test = false;
    QSqlQuery query;
    query.prepare("select * from COMPTES where email=:email");
    query.bindValue(":email",email);
    if(query.exec()){
        query.next();
        if(query.value(1).toString() == password){
             test = true;
        }else {
             test = false;
        }
    }else {
        test = false;
    }

    return test;
}

QSqlQuery Employees::afficherEmp(QString email)
{
    QSqlQuery query;
    query.prepare("select * from employees inner join COMPTES on employees.cin = COMPTES.cin where COMPTES.email=:email");
    query.bindValue(":email",email);
    query.exec();
    return query;
}
