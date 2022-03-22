#ifndef machine_H
#define machine_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include <QVBoxLayout>

namespace Ui {
class machine;
}
class DuScene;

class machine : public QDialog
{
    Q_OBJECT

public:
    explicit machine(QWidget *parent = nullptr);
    ~machine();

private slots:
    void on_ajouter_machine_clicked();
    void on_refreshBtn_clicked();



private:
    Ui::machine *ui;
    DuScene *mScene;
};

#endif // machine_H
