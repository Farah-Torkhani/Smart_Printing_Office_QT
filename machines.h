#ifndef MACHINES_H
#define MACHINES_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include <QVBoxLayout>

namespace Ui {
class Machines;
}

class Machines : public QDialog
{
    Q_OBJECT

public:
    explicit Machines(QWidget *parent = nullptr);
    ~Machines();

private slots:
    void on_ajouter_machine_clicked();

    void on_refreshBtn_clicked();

    void on_modifier_machine_clicked();

    void setFormulaire();

    void on_clear_machine_clicked();

private:
    Ui::Machines *ui;
};

#endif // MACHINES_H
