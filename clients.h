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
#include "arduino.h"

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
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

private slots:
    void on_ajouter_client_clicked();
    void on_refreshBtn_clicked();
    void on_modifier_client_clicked();

    void setFormulaire();

    void on_clear_client_clicked();

    void on_pdfBtn_clicked();

    void on_search_client_clicked();

    void on_search_input_textChanged(const QString &arg1);

    void on_stat_clicked();


    void on_trie_client_clicked();

    void on_Alerte_btn_clicked();

    void test_callArd();

    void on_call_testBtn_clicked();


    void on_recive_callBtnTimer_clicked();

private:
    Ui::Clients *ui;
    DuScene *mScene;

    QCompleter *stringCompleter;
    QCompleter *ModelCompleter;


};

#endif // CLIENTS_H
