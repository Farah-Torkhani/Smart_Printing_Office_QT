#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QTextEdit>
#include <chatservice.h>


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
    void click_btnLogin();
    void click_btnLogout();
    void reject();

signals:


private slots:
    void showMessage(ChatService::message_t type,QString hint,QString content);
    void updateOnlineUsers(QSet<QString> set);
    void click_btnSendMessage();


private:
    Ui::Chat *ui;
    const qint8 DEFAULT_MESSAGE_FONT_SIZE = 14;
    ChatService * chat;
};

#endif // CHAT_H
