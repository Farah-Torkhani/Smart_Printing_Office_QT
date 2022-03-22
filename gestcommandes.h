#ifndef GESTCOMMANDES_H
#define GESTCOMMANDES_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>


namespace Ui {
class Gestcommandes;
}

class Gestcommandes : public QDialog
{
    Q_OBJECT

public:
    explicit Gestcommandes(QWidget *parent = nullptr);
    ~Gestcommandes();

private slots:


    void setFormulaire();
    void on_ajouter_clicked();

    void on_modifier_commande_clicked();

    void on_refreshBtn_clicked();

    void on_clear_commande_clicked();

   // void on_comboBox_7_activated(const QString &arg1);

    void on_chercher_commande_textChanged(const QString &arg1);

    void on_search_commandeBtn_clicked();
    void on_statCommande_clicked();

    void on_checkBox_7_stateChanged(int arg1);

private:
    Ui::Gestcommandes *ui;

    QCompleter *stringCompleter;
    QCompleter *ModelCompleter;
};

#endif // GESTCOMMANDES_H
