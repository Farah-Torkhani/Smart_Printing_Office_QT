#ifndef ROW_TABLE_PRODUITS_H
#define ROW_TABLE_PRODUITS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


class row_table_produits : public QLabel
{
    Q_OBJECT
public:
    explicit row_table_produits();
    explicit row_table_produits(QWidget *parent,QString id,QString nomP,QString quantite,QString type,QString prixU);

    QLabel *row_container = new QLabel(this);
    QLabel *id_label = new QLabel();
    QLabel *nomP_label = new QLabel();
    QLabel *type_label = new QLabel();
    QLabel *quantite_label = new QLabel();
    QLabel *prixU_label = new QLabel();
    QPushButton *editBtn = new QPushButton();
    QPushButton *deleteBtn = new QPushButton();
    QPushButton *qrGBtn = new QPushButton();

private slots:
    void deleteBtn_clicked();
    void editBtn_clicked();
    void qrGBtn_clicked();


signals:


};

#endif // ROW_TABLE_PRODUITS_H
