#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <QObject>
#include <QUdpSocket>

class ChatService : public QObject
{
    Q_OBJECT
public:
    explicit ChatService(QObject *parent = nullptr);

    enum message_t{MT_CHAT,MT_LOGIN,MT_LOGOUT,MT_INVOLVE,MT_SYSTEM};  //聊天、登录、退出、在线、系统信息
    enum status_t{ST_ONLINE,ST_OFFLINE};

    void setMask(QString mask) { MASK = mask; }
    void setStatus(status_t status) { currentStatusType = status; }
    void setUserName(QString name) { USER_NAME = name; }

    status_t status() { return currentStatusType; }

    void sendJson(message_t type, QString nick_name, QString content="");

    static QString toIPv4(quint32 arg);
    static QString getLocalIP();

private:

    QString MASK;
    QString USER_NAME;

    status_t currentStatusType;

    QSet<QString> onlineUsersSet;

    QUdpSocket * messageSender,* messageReader;
    const qint16 DEFAULT_MESSAGE_PORT = 6108; // 默认信息端口

signals:

    void messageShowReady(ChatService::message_t type, QString hint, QString content);
    void onlineUsersUpdateReady(QSet<QString> set);

private slots:

    void readAllMessage();


};

#endif // CHATSERVICE_H
