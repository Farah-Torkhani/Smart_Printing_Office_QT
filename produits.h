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
#include "popup.h"

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
    void setQR();
    void on_refreshBtn_clicked();

    void on_modifier_b_clicked();

    void on_b_searsh_clicked();

    void on_excel_clicked();
    void on_pushButton_clicked();
    void on_statP_clicked();
    void on_statP1_clicked();



    void on_qrcode_pt_clicked();

    void on_edit_r_textChanged(const QString &arg1);

private:
    Ui::produits *ui;
    PopUp *popUp;


};
#endif // PRODUITS_H
