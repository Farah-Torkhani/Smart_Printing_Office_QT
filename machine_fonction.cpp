#include "machine_fonction.h"
#include "connection.h"

#include <QSqlQuery>
#include <QDebug>


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




QSqlQuery Machine_fonction::trierMachines(QString test)
{
    QSqlQuery query;
    if(test == "par défaut"){
        query.exec("select * from machines");
    }
    else if(test =="nom")
    {
        query.exec("select * from machines order by nomMachine asc");
    }
    else if(test =="etat")
    {
        query.exec("select * from machines order by etatMachine desc");
    }
    else if(test =="prix")
    {
        query.exec("select * from machines order by prixMachine asc");
    }
    else if(test =="date_achat")
    {
        query.exec("select * from machines order by date_achat desc");
    }
    return query;
}




QStringList Machine_fonction::rechercherMachines_completer()
{

    QSqlQuery query;
    QStringList cblist;

    query.prepare("select * from machines ");
    query.exec();

    QString n;
    while(query.next())
            {
                cblist.push_back(query.value(1).toString() );//nomMachine
                cblist.push_back(query.value(3).toString() );//prixMachine
             //   qDebug() << "test";

            }


    return  cblist;


}

QSqlQuery Machine_fonction::rechercherMachine(QString chaine)
{

    QSqlQuery query;

    query.exec("select * from machines where nomMachine LIKE'%"+chaine+"%' OR prixMachine LIKE'%"+chaine+"%' ");
    return query;

}


//*******************************statistique Client********************************************************

int Machine_fonction::statistiqueMachine(int etat)
{
    QSqlQuery query;
    query.prepare("select count(*) from machines where etatMachine=:etat ");
    query.bindValue(":etat",etat);
    query.exec();

    int count =-1;



        QString cblist;

            while(query.next())
                    {
                        cblist=query.value(0).toString() ;
                     //   qDebug() << "test";
                        count = cblist.toInt();
                     //     qDebug() << "count=" << count ;
                    }

    return count;

}




QSqlQueryModel * Machine_fonction::afficherMachineForExcel()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT nomMachine,prixMachine,etatMachine,to_char(date_achat,'dd-MM-yyyy')as date_achat from machines ");

    return model ;
}



bool Machine_fonction::entretienMachine(int machineId)
{
    QSqlQuery query;
    query.prepare("select etatMachine from machines where machineId=:machineId ");
    query.bindValue(":machineId",machineId);
    query.exec();

    query.next();
    int etatMachine = query.value(0).toInt();
    if(etatMachine == 1)
    {
        return false;
    }
    else
    {
        query.prepare("update machines set etatMachine=:etatMachine where machineId=:machineId");
        query.bindValue(":etatMachine",1);
        query.bindValue(":machineId",machineId);
        query.exec();


        query.prepare("Insert into historiques(machId)"
                      "Values( :machId)");
        query.bindValue(":machId", machineId);
        query.exec();

        return true;
    }


}


int Machine_fonction::historiqueCount(int machineId)
{
    QSqlQuery query;
    query.prepare("select count(*) from historiques where machId=:machineId");
    query.bindValue(":machineId",machineId);

    query.exec();
    query.next();

    return query.value(0).toInt();
}

QSqlQuery Machine_fonction::afficherHistorique(int machineId)
{
    QSqlQuery query;
    query.prepare("select to_char(historique_date, 'dd-MM-yyyy') from historiques where machId=:machineId");
    query.bindValue(":machineId",machineId);

    query.exec();
    return query;
}
