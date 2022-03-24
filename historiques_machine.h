#ifndef HISTORIQUES_MACHINE_H
#define HISTORIQUES_MACHINE_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

namespace Ui {
class Historiques_machine;
}

class Historiques_machine : public QDialog
{
    Q_OBJECT

public:
    explicit Historiques_machine(QWidget *parent = nullptr);
    ~Historiques_machine();

    int machineId;
    void reject();

private slots:
    void refreshHistorique();

private:
    Ui::Historiques_machine *ui;
};

#endif // HISTORIQUES_MACHINE_H
