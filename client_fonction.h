#ifndef CLIENT_FONCTION_H
#define CLIENT_FONCTION_H
#include <QString>
#include <QDateEdit>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


class Client_fonction
{
private:
    int cinClient;
    QString nomClient;
    QString prenomClient;
    QString emailClient;
    int telClient;
    QDate date_ajout;


public:
    Client_fonction();
    Client_fonction(int cinClient, QString nomClient, QString prenomClient, QString emailClient, int telClient);

    int getcinClient(){return cinClient;}
    QString getnomClient(){return nomClient;}
    QString getprenomClient(){return prenomClient;}
    QString getemailClient(){return emailClient;}
    int gettelClient(){return telClient;}
   // QDate getdate_ajout(){return date_ajout;}

    bool ajouter();
    QSqlQuery afficherCilents();
    bool supprimerClient(int cinClient);

    QSqlQuery afficherCilent(int cinClient);
    bool modifierClient();



};

#endif // CLIENT_FONCTION_H


