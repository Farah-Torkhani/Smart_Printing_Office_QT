#ifndef COMMANDES_ROW_TABLE_H
#define COMMANDES_ROW_TABLE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class commandes_row_table :  public QLabel
{ Q_OBJECT
public:
    explicit commandes_row_table(QWidget *parent,QString descreption,QString etat,QString dateC, QString Quantite_Couleur, QString Quantite_sans_couleur,QString id);
    QLabel *row_container = new QLabel(this);
       QLabel *descreption_label = new QLabel();
        QLabel *etat_label = new QLabel();
QLabel *dateC_label= new QLabel();
       QLabel *QuantiteCouleur_label = new QLabel();
       QLabel *QuantiteSansCouleur_label = new QLabel();
       QPushButton *editBtn = new QPushButton();
       QPushButton *deleteBtn = new QPushButton();

private slots:
    void deleteBtn_clicked();
    void updateBtn_clicked();

};

#endif // COMMANDES_ROW_TABLE_H
