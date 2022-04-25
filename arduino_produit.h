#ifndef ARDUINO_PRODUIT_H
#define ARDUINO_PRODUIT_H

#include <QDialog>
#include"arduino.h"
#include "popup.h"

namespace Ui {
class Arduino_Produit;
}

class Arduino_Produit : public QDialog
{
    Q_OBJECT

public:
    explicit Arduino_Produit(QWidget *parent = nullptr);
    ~Arduino_Produit();

private slots:
   // void update_label();
    void refreshHistorique();

private:
    Ui::Arduino_Produit *ui;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

    PopUp *popUp;

};

#endif // ARDUINO_PRODUIT_H
