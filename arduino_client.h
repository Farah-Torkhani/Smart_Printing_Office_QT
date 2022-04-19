#ifndef ARDUINO_CLIENT_H
#define ARDUINO_CLIENT_H
#include "arduino.h"
#include <QDialog>


namespace Ui {
class Arduino_client;
}

class Arduino_client : public QDialog
{
    Q_OBJECT

public:
    explicit Arduino_client(QWidget *parent = nullptr);
    ~Arduino_client();
    void reject();


private slots:

    void on_refreshEmpArdBtn_clicked();
    void test_call();

private:
    Ui::Arduino_client *ui;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // ARDUINO_CLIENT_H
