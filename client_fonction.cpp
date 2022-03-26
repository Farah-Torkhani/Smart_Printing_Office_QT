#include "client_fonction.h"
#include "connection.h"

#include <QSqlQuery>
#include <QDebug>

Client_fonction::Client_fonction(int cinClient, QString nomClient, QString prenomClient, QString emailClient, int telClient)
{
    this->cinClient = cinClient;
    this->nomClient = nomClient;
    this->prenomClient = prenomClient;
    this->emailClient = emailClient;
    this->telClient = telClient;

}

Client_fonction::Client_fonction(QString nomClient)
{
    this->nomClient = nomClient;
}

bool Client_fonction::ajouter()
{
    QSqlQuery query;



    query.prepare("Insert into clients(cinClient, telClient, prenomClient, nomClient, emailClient)"
                  "Values( :cinClient, :telClient, :prenomClient, :nomClient, :emailClient)");
    query.bindValue(":cinClient", cinClient);
    query.bindValue(":nomClient", nomClient);
    query.bindValue(":prenomClient", prenomClient);
    query.bindValue(":emailClient", emailClient);
    query.bindValue(":telClient", telClient);

    return query.exec();

}


QSqlQuery Client_fonction::afficherCilents()
{
    QSqlQuery query;
    query.exec("select * from clients");
    return query;
}



bool Client_fonction::supprimerClient(int cinClient)
{
QSqlQuery query;

QString cin = QString::number(cinClient);

query.prepare("Delete from clients where CINCLIENT=:cinClient");
query.bindValue(":cinClient",cin);
return query.exec();
}



QSqlQuery Client_fonction::afficherCilent(int cinClient)
{
    QSqlQuery query;
    query.prepare("select * from clients where cinClient=:cinClient");
    query.bindValue(":cinClient",cinClient);

    query.exec();
    return query;
}

bool Client_fonction::modifierClient()
{
    QSqlQuery query;
    query.prepare("update clients set cinClient=:cinClient, nomClient=:nomClient, prenomClient=:prenomClient, emailClient=:emailClient, telClient=:telClient  where cinClient=:cinClient");
    query.bindValue(":cinClient",cinClient);
    query.bindValue(":nomClient",nomClient);
    query.bindValue(":prenomClient",prenomClient);
    query.bindValue(":emailClient",emailClient);
    query.bindValue(":telClient",telClient);

    return query.exec();


}


//**************************recherche*****************************
QSqlQuery Client_fonction::rechercherClient(QString chaine)
{

    QSqlQuery query;


    query.exec("SELECT * from clients where nomClient LIKE'%"+chaine+"%' OR prenomClient LIKE'%"+chaine+"%' OR emailClient LIKE'%"+chaine+"%' OR telClient LIKE'%"+chaine+"%'   ");
    return query;


}


QStringList Client_fonction::rechercherClients()
{

    QSqlQuery query;
    QStringList cblist;

    query.prepare("select * from clients ");
    query.exec();

    QString n;
    while(query.next())
            {
               // if (query.isValid())
                cblist.push_back(query.value(0).toString() );
                cblist.push_back(query.value(1).toString() );
                cblist.push_back(query.value(2).toString() );
                cblist.push_back(query.value(3).toString() );
                cblist.push_back(query.value(4).toString() );
             //   qDebug() << "test";

            }


    return  cblist;


}

//**************************recherche*****************************




QSqlQuery Client_fonction::trierCilent(QString test)
{
    QSqlQuery query;
    if(test == "par défaut"){
        query.exec("select * from clients");
    }
    else if(test =="nom")
    {
        query.exec("select * from clients order by nomClient asc");
    }
    else if(test =="date_ajout")
    {
        query.exec("select * from clients order by date_ajout desc");
    }
    else if(test =="prenom")
    {
        query.exec("select * from clients order by prenomClient asc");
    }
    return query;
}

//**********************************controle de saisie email*****************************************
bool Client_fonction::is_email_valid(QString email)
{
    QRegularExpression regex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}\\b");

    return regex.match(email).hasMatch();
}


//*******************************statistique Client********************************************************

int Client_fonction::statistiqueCilents(int month)
{
    QSqlQuery query;
    query.prepare("select count(*) from clients where extract(month from date_ajout)=:month ");
    query.bindValue(":month",month);
    query.exec();

    int count =50;



        QString cblist;

            while(query.next())
                    {
                        cblist=query.value(0).toString() ;
                     //   qDebug() << "test";
                        count = cblist.toInt();
//                        qDebug() << "count=" << count ;
                    }

    return count;

}

