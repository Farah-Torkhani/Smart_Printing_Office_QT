#ifndef MACHINES_H
#define MACHINES_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include <QVBoxLayout>
#include <QCompleter>
#include <QDirModel>

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

    void on_search_machine_clicked();

    void on_search_input_machine_textChanged(const QString &arg1);

    void on_trier_machine_clicked();

    void on_statMachine_clicked();

    void on_excel_btn_clicked();

    void on_add_imageBtn_clicked();

private:
    Ui::Machines *ui;

    QCompleter *stringCompleter;
    QCompleter *ModelCompleter;
};

#endif // MACHINES_H
