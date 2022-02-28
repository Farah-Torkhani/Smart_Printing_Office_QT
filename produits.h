#ifndef PRODUITS_H
#define PRODUITS_H

#include <QMainWindow>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSeries>
#include <QPieSlice>
#include "fonctionproduits.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QString>


QT_BEGIN_NAMESPACE
namespace Ui { class produits; }
QT_END_NAMESPACE

class produits : public QMainWindow
{
    Q_OBJECT

public:
    produits(QWidget *parent = nullptr);
    ~produits();
    Produits Pr;

private slots:
    void on_valider_b_clicked();
    void setFormulaire();

    void on_refreshBtn_clicked();

    void on_modifier_b_clicked();

private:
    Ui::produits *ui;

};
#endif // PRODUITS_H
