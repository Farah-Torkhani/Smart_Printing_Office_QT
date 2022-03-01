#ifndef COMMANDES_H
#define COMMANDES_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

namespace Ui {
class GestCommandes;
}

class GestCommandes : public QDialog
{
    Q_OBJECT

public:
    explicit GestCommandes(QWidget *parent = nullptr);
    ~GestCommandes();

private:
    Ui::GestCommandes *ui;
};

#endif // COMMANDES_H
