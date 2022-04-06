#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QTextEdit>


namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT


public:
    explicit Chat(QWidget *parent = nullptr);
    Chat(int cin, QString messageContent);
    ~Chat();

signals:
    void sendMessage(QString message);
    void connectToChanged(QString address, QString port);

private slots:
    void on_sendMessBtn_clicked();
    void displayNewMessage(QString message, QString sender);
    void connectionChange();

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
