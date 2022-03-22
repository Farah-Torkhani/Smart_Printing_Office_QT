#ifndef machine_ROW_TABLE_H
#define machine_ROW_TABLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


class machine_row_table : public QLabel
{
    Q_OBJECT
public:
    explicit machine_row_table(QWidget *parent,QString machineID, QString nomMachine, QString etat, QString prix);

    QLabel *row_container = new QLabel(this);
    QLabel *nom_label = new QLabel();
    QLabel *etat_label = new QLabel();
    QLabel *id_label = new QLabel();
    QLabel *prix_label = new QLabel();
    QPushButton *editBtn = new QPushButton();
    QPushButton *deleteBtn = new QPushButton();

private slots:
    void deleteBtn_clicked();



};

#endif // machine_ROW_TABLE_H
