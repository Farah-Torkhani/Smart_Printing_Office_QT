#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>

#include <QVBoxLayout>


#include <QCompleter>
#include <QDirModel>


namespace Ui {
class Clients;
}
class DuScene;

class Clients : public QDialog
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();


private slots:
    void on_ajouter_client_clicked();
    void on_refreshBtn_clicked();
    void on_modifier_client_clicked();

    void setFormulaire();

    void on_clear_client_clicked();

    void on_pdfBtn_clicked();

    void on_search_client_clicked();

    void on_search_input_textChanged(const QString &arg1);


private:
    Ui::Clients *ui;
    DuScene *mScene;

    QCompleter *stringCompleter;
    QCompleter *ModelCompleter;
};

#endif // CLIENTS_H
