#ifndef MACHINE_FONCTION_H
#define MACHINE_FONCTION_H
#include <QString>
#include <QDateEdit>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Machine_fonction
{
private:
    int machineId;
    QString nomMachine;
    QString machineImg;
    int prixMachine;
    int etatMachine;
    QDate date_achat;
 //   QDate date_entretien;

public:
    Machine_fonction();
    Machine_fonction(QString nomMachine, QString machineImg, int prixMachine, int etatMachine);

    bool ajouter();
    QSqlQuery afficherMachines();
    bool supprimerMachine(int machineId);

    QSqlQuery afficherMachine(int machineId);
    bool modifierMachine(int machineId);

};

#endif // MACHINE_FONCTION_H
