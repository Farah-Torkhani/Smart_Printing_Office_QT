#ifndef DESCREPTION_COMMANDE_H
#define DESCREPTION_COMMANDE_H

#include <QDialog>

namespace Ui {
class Descreption_commande;
}

class Descreption_commande : public QDialog
{
    Q_OBJECT

public:
    explicit Descreption_commande(QWidget *parent = nullptr);
    ~Descreption_commande();

    int idCommande;

private slots:
    void setDescreptionInfo();

private:
    Ui::Descreption_commande *ui;
};

#endif // DESCREPTION_COMMANDE_H
