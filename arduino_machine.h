#ifndef ARDUINO_MACHINE_H
#define ARDUINO_MACHINE_H
#include "arduino.h"
#include <QDialog>

namespace Ui {
class Arduino_machine;
}

class Arduino_machine : public QDialog
{
    Q_OBJECT

public:
    explicit Arduino_machine(QWidget *parent = nullptr);
    ~Arduino_machine();

    QString nomMachine="ttttt";




private slots:
    void on_showLCD_btn_clicked();

    void on_mute_btn_clicked();

    void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
    // ce slot est lancé à chaque réception d'un message de Arduino

    void on_refreshBtn_clicked();
    void setNomMachine();

private:
    Ui::Arduino_machine *ui;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // ARDUINO_MACHINE_H
