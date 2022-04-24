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
#include <QDirModel>

#include "arduino.h"

//Gestion Client***
#include "client_fonction.h"
#include "duscene.h"
#include "client_row_table.h"
#include "email.h"
#include "sms.h"
#include "arduino_client.h"
#include "arduino.h"
#include "callard.h"
#include <QScrollArea>
#include <QDate>
#include <QCoreApplication>
#include <QDebug>
#include <QSslSocket> //To use QSslSocket Class
//Gestion Client***


//Gestion Machine***
#include <QFileInfo>
#include "machine_fonction.h"
#include "machine_row_table.h"
#include "historiques_machine.h"
#include "arduino_machine.h"
//Gestion Machine***

//Gestion Commande***
#include "commandes.h"
#include "commandes_row_table.h"
#include <qtranslator.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QSqlQuery>
#include "descreption_commande.h"
#include "date_fin.h"
#include <imprimer_recu.h>
//Gestion Commande***


namespace Ui {
class Integration;
}

class DuScene;

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

    //gestion Client***************
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
    //gestion Client***************

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
//***************************************************************************************************************
    //gestion Client***************
    void on_ajouter_client_clicked();
    void on_refreshClientBtn_clicked();//updated
    void on_modifier_client_clicked();
    void setClientFormulaire();//updated
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
    //gestion Client***************

//-----------------------------------------------------------------------------------------------------------------------

    //gestion Machine********************************
    void on_ajouter_machine_clicked();
    void on_refreshBtnMachine_clicked();
    void on_modifier_machine_clicked();
    void setFormulaireMachine();
    void on_clear_machine_clicked();
    void on_search_machine_clicked();
    void on_search_input_machine_textChanged(const QString &arg1);
    void on_trier_machine_clicked();
    void on_statMachine_clicked();
    void on_excel_btn_clicked();
    void on_add_imageBtn_clicked();
    void on_arduinoM_btn_clicked();
    //gestion Machine*********************************

//-----------------------------------------------------------------------------------------------------------------------

    //gestion Commande********************************
    void setCommandeFormulaire();
    void on_ajouter_commande_clicked();
    void on_modifier_commande_clicked();
    void on_refreshCommandeBtn_clicked();
    void on_clear_commande_clicked();
    void on_chercher_commande_textChanged(const QString &arg1);
    void on_search_commandeBtn_clicked();
    void on_statCommande_clicked();
    void setCinClient_combo();
    void on_trie_commande_clicked();
    //gestion Commande********************************

private:
    Ui::Integration *ui;
    //gestion Client***************
    DuScene *mScene;
    //gestion Client***************
    QCompleter *stringCompleter;
    QCompleter *ModelCompleter;
};

#endif // INTEGRATION_H
