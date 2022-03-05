#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

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
    bool addMessage(int cin, QString message);
    QSqlQuery afficherAllMessage();
    void reject();

private slots:
    void on_sendMessBtn_clicked();
    void refreshMessageList();

private:
    Ui::Chat *ui;
//    int messageId;
//    QString messageContent;
//    int cin;
//    QString dateSend;
};

#endif // CHAT_H
