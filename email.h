#ifndef EMAIL_H
#define EMAIL_H

#include <QDialog>

#include "smtp.h"
#include <QWidget>
#include <QtWidgets/QMessageBox>
#include "client_fonction.h"

namespace Ui {
class Email;
}

class Email : public QDialog
{
    Q_OBJECT

public:
    int cinClient;
    explicit Email(QWidget *parent = nullptr);
    ~Email();

private:
    Ui::Email *ui;

private slots:
    void sendMail();
    void mailSent(QString);

    void on_sendMailBtn_clicked();

    void setEmail();
};

#endif // EMAIL_H
