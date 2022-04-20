#ifndef CALLARD_H
#define CALLARD_H
#include "arduino.h"
#include <QDialog>
#include <QString>

namespace Ui {
class CallArd;
}

class CallArd : public QDialog
{
    Q_OBJECT

public:
    explicit CallArd(QWidget *parent = nullptr);
    ~CallArd();
    QString call_numIn;
    void reject();

private slots:
    void on_acceptCall_Btn_clicked();

    void on_CancelCall_Btn_clicked();

    void setCallNumberArd();

private:
    Ui::CallArd *ui;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // CALLARD_H
