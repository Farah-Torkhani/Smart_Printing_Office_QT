 #include "machine_fonction.h"
#include "connection.h"

#include <QSqlQuery>


Machine_fonction::Machine_fonction(QString nomMachine, QString machineImg, int prixMachine, int etatMachine)
{
    this->nomMachine = nomMachine;
    this->machineImg = machineImg;
    this->prixMachine = prixMachine;
    this->etatMachine = etatMachine;

}

bool Machine_fonction::ajouter()
{
    QSqlQuery query;



    query.prepare("Insert into machines(nomMachine, machineImg, prixMachine, etatMachine)"
                  "Values( :nomMachine, :machineImg, :prixMachine, :etatMachine)");
    query.bindValue(":nomMachine", nomMachine);
    query.bindValue(":machineImg", machineImg);
    query.bindValue(":prixMachine", prixMachine);
    query.bindValue(":etatMachine", etatMachine);

    return query.exec();

}


QSqlQuery Machine_fonction::afficherMachines()
{
    QSqlQuery query;
    query.exec("select * from machines");
    return query;
}


bool Machine_fonction::supprimerMachine(int machineId)
{
QSqlQuery query;

QString id = QString::number(machineId);

query.prepare("Delete from machines where machineId=:machineId");
query.bindValue(":machineId",id);
return query.exec();
}


QSqlQuery Machine_fonction::afficherMachine(int machineId)
{
    QSqlQuery query;
    query.prepare("select * from machines where machineId=:machineId");
    query.bindValue(":machineId",machineId);

    query.exec();
    return query;
}

bool Machine_fonction::modifierMachine(int machineId)
{
    QSqlQuery query;
    query.prepare("update machines set nomMachine=:nomMachine, machineImg=:machineImg, prixMachine=:prixMachine, etatMachine=:etatMachine where machineId=:machineId");
    query.bindValue(":nomMachine",nomMachine);
    query.bindValue(":machineImg",machineImg);
    query.bindValue(":prixMachine",prixMachine);
    query.bindValue(":etatMachine",etatMachine);
    query.bindValue(":machineId",machineId);

    return query.exec();


}














