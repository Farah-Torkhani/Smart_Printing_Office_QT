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

private slots:
    void on_chatBtn_clicked();

private:
    Ui::GestionEmp *ui;
};

#endif // GESTIONEMP_H
