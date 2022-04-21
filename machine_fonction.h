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
    QSqlQuery trierMachines(QString test);
    QStringList rechercherMachines_completer();
    QSqlQuery rechercherMachine(QString chaine);
    int statistiqueMachine(int etat);

    QSqlQueryModel *afficherMachineForExcel();
    bool entretienMachine(int machineId);

    QSqlQuery afficherHistorique(int machineId);
    int historiqueCount(int machineId);

};

#endif // MACHINE_FONCTION_H
