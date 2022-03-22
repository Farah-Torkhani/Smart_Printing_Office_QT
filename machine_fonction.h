#ifndef machine_FONCTION_H
#define machine_FONCTION_H
#include <QString>
#include <QDateEdit>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>


class machine_fonction
{
private:
    int machineID;
    QString nomMachine;
    QString etat;
    QString emailmachine;
    int prix;
    QDate date_entretin;


public:
    machine_fonction();
    machine_fonction(int machineID, QString nomMachine, QString etat,int prix);

    int getmachineID(){return machineID;}
    QString getnomMachine(){return nomMachine;}
    QString getetat(){return etat;}
    int getprix(){return prix;}
   // QDate getdate_entretin(){return date_entretin;}

    bool ajouter();
    QSqlQuery affichermachine();
    bool supprimermachine(int machineID);



};

#endif // machine_FONCTION_H


