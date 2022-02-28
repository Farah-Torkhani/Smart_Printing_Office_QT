#ifndef ROW_TABLE_H
#define ROW_TABLE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


class Row_table : public QLabel
{
    Q_OBJECT
public:
    explicit Row_table(QWidget *parent,QString cin,QString nom,QString prenom,QString dateEmb,QString salaire,QString role);

    QLabel *row_container = new QLabel(this);
    QLabel *cin_label = new QLabel();
    QLabel *nom_label = new QLabel();
    QLabel *prenom_label = new QLabel();
    QLabel *dateEmb_label = new QLabel();
    QLabel *salaire_label = new QLabel();
    QLabel *role_label = new QLabel();
    QPushButton *editBtn = new QPushButton();
    QPushButton *chatBtn = new QPushButton();
    QPushButton *deleteBtn = new QPushButton();

private slots:


signals:


};

#endif // ROW_TABLE_H
