#ifndef COMMANDES_ROW_TABLE_H
#define COMMANDES_ROW_TABLE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class commandes_row_table :  public QLabel
{ Q_OBJECT
public:
    explicit commandes_row_table(QWidget *parent, QString dateC, QString Quantite_Couleur, QString Quantite_sans_couleur,QString id, QString etat);

       QLabel *row_container = new QLabel(this);
       QLabel *dateC_label= new QLabel();
       QLabel *QuantiteCouleur_label = new QLabel();
       QLabel *QuantiteSansCouleur_label = new QLabel();
       QPushButton *editBtn = new QPushButton();
       QPushButton *deleteBtn = new QPushButton();
       QPushButton *imprimerBtn = new QPushButton();
       QPushButton *etatBtn = new QPushButton();
       QPushButton *descreptionBtn = new QPushButton();
       QPushButton *repaireBtn = new QPushButton();


private slots:
    void deleteBtn_clicked();
    void updateBtn_clicked();
    void imprimerBtn_clicked();
    void etatBtn_clicked();
    void descreptionBtn_clicked();
    void repaireBtn_clicked();

};

#endif // COMMANDES_ROW_TABLE_H
