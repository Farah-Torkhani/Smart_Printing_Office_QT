#ifndef GESTIONEMP_H
#define GESTIONEMP_H

#include <QMainWindow>

namespace Ui {
class GestionEmp;
}

class GestionEmp : public QMainWindow
{
    Q_OBJECT

public:
    explicit GestionEmp(QWidget *parent = nullptr);
    ~GestionEmp();
    bool is_email_valid(QString email);
    void test();


private slots:
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

private:
    Ui::GestionEmp *ui;
};

#endif // GESTIONEMP_H
