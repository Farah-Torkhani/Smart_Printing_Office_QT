#ifndef SMS_H
#define SMS_H

#include <QDialog>

namespace Ui {
class Sms;
}

class Sms : public QDialog
{
    Q_OBJECT

public:

    explicit Sms(QWidget *parent = nullptr);
    ~Sms();

    void setCinClient(int cin){this->cinClient = cin;}
    int getCinClient(){return  cinClient;}

private slots:
    void on_sendSmsBtn_clicked();
    void setSmsInfo();

private:
    Ui::Sms *ui;
    int cinClient;
};

#endif // SMS_H
