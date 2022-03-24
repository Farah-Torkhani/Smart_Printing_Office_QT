#ifndef MACHINE_ROW_TABLE_H
#define MACHINE_ROW_TABLE_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Machine_row_table : public QLabel
{
    Q_OBJECT
public:
    explicit Machine_row_table(QWidget *parent,QString machineId,QString nomMachine, QString machineImg, QString prixMachine, QString etatMachine);

    QLabel *row_container = new QLabel(this);
    QLabel *img_label = new QLabel();
    QLabel *nom_label = new QLabel();
    QLabel *prix_label = new QLabel();
    QLabel *etat_label = new QLabel();

    QPushButton *repaireBtn = new QPushButton();
    QPushButton *historiqueBtn = new QPushButton();
    QPushButton *editBtn = new QPushButton();
    QPushButton *deleteBtn = new QPushButton();

private slots:
    void deleteBtn_clicked();
    void updateBtn_clicked();

};

#endif // MACHINE_ROW_TABLE_H
