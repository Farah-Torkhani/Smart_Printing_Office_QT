#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <QMainWindow>
#include "chat.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include "employees.h"
#include "row_table.h"
#include <QMessageBox>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>
#include <regex>
#include "login.h"
#include <QDebug>
#include <QProcess>
#include <QCompleter>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include "chatclient.h"

namespace Ui {
class Integration;
}

class Integration : public QMainWindow
{
    Q_OBJECT

public:
    explicit Integration(QWidget *parent = nullptr);
    ~Integration();

    //GESTION EMP***
    bool is_email_valid(QString email);
    void test();
    //GESTION EMP***

private slots:
    //GESTION EMP***
    void on_chatBtn_clicked();
    void on_addBtn_clicked();
    void on_refreshBtn_clicked();
    void setFormulaire();
    void on_clearBtn_clicked();
    void on_updateBtn_clicked();
    void on_chercheBtn_clicked();
    void on_formationBtn_clicked();
    void on_logoutBtn_clicked();
    void on_me_formationBtn_clicked();
    void on_me_setForm_clicked();
    void refreshAccountInfo();
    void on_me_updateBtn_clicked();
    void on_me_deleteBtn_clicked();
    void refreshCurrentEmp();
    void on_me_chatBtn_clicked();
    void testChercheInput();
    void on_chercheInput_textChanged(const QString &arg1);
    void chartEmp();
    //GESTION EMP***

private:
    Ui::Integration *ui;
};

#endif // INTEGRATION_H
