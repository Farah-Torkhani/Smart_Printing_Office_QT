#ifndef IMPRIMER_RECU_H
#define IMPRIMER_RECU_H

#include <QDialog>

namespace Ui {
class imprimer_recu;
}

class imprimer_recu : public QDialog
{
    Q_OBJECT

public:
    explicit imprimer_recu(QWidget *parent = nullptr);
    ~imprimer_recu();
int idComm;
private slots:
void setRecuInfo();
void on_valider_clicked();

private:
    Ui::imprimer_recu *ui;
};

#endif // IMPRIMER_RECU_H
