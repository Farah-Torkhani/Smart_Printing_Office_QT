#include "machine_fonction.h"
#include "connection.h"

#include <QSqlQuery>

machine_fonction::machine_fonction(int machineID, QString nomMachine, QString etat, int prix)
{
    this->machineID = machineID;
    this->nomMachine = nomMachine;
    this->etat = etat;
    this->prix = prix;

}

bool machine_fonction::ajouter()
{
    QSqlQuery query;



    query.prepare("Insert into machines(machineID, prix, etat, nomMachine, emailmachine)"
                  "Values( :machineID, :prix, :etat, :nomMachine, :emailmachine)");
    query.bindValue(":machineID", machineID);
    query.bindValue(":nomMachine", nomMachine);
    query.bindValue(":etat", etat);
    query.bindValue(":emailmachine", emailmachine);
    query.bindValue(":prix", prix);

    return query.exec();

}


QSqlQuery machine_fonction::affichermachine()
{
    QSqlQuery query;
    query.exec("select * from machines");
    return query;
}



bool machine_fonction::supprimermachine(int machineID)
{
QSqlQuery query;

QString id = QString::number(machineID);

query.prepare("Delete from machines where machineID=:machineID");
query.bindValue(":machineID",id);
return query.exec();
}

