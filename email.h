#ifndef EMAIL_H
#define EMAIL_H

#include "smtp.h"
#include <QWidget>
#include <QtWidgets/QMessageBox>

#include "client_fonction.h"
namespace Ui {
class Email;
}

class Email : public QWidget
{
    Q_OBJECT

public:
    int cinClient;

    explicit Email(QWidget *parent = nullptr);
    ~Email();


private slots:
    void sendMail();
    void mailSent(QString);

    void on_sendMailBtn_clicked();

    void setEmail();

private:
    Ui::Email *ui;

  //  Client_fonction c;
};

#endif // EMAIL_H
