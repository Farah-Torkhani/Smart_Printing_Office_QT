#ifndef STATISQUES_COMMANDE_H
#define STATISQUES_COMMANDE_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
namespace Ui {
class Statistiques_commande;
}
        class Statitisques_commande : public QDialog
{
            Q_OBJECT

           public:
               explicit Statistiques_commande(QWidget *parent = nullptr);
               ~Statistiques_commande();

           private slots:
               void on_ajouter_commande_clicked();

           private:
               Ui::Statistiques_commande *ui;
};

#endif // STATISQUES_COMMANDE_H


