#ifndef DATE_FIN_H
#define DATE_FIN_H

#include <QDialog>

namespace Ui {
class Date_fin;
}

class Date_fin : public QDialog
{
    Q_OBJECT

public:
    explicit Date_fin(QWidget *parent = nullptr);
    ~Date_fin();
    int idCommande;

private slots:
    void setDate();



private:
    Ui::Date_fin *ui;
};

#endif // DATE_FIN_H
