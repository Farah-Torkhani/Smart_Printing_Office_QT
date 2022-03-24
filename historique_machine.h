#ifndef HISTORIQUE_MACHINE_H
#define HISTORIQUE_MACHINE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

namespace Ui {
class Historique_machine;
}

class Historique_machine : public QWidget
{
    Q_OBJECT

public:
    explicit Historique_machine(QWidget *parent = nullptr);
    int machineId;
    void reject();

    ~Historique_machine();

private slots:
    void refreshHistorique();

private:
    Ui::Historique_machine *ui;
};

#endif // HISTORIQUE_MACHINE_H
