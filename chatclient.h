#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QObject>
#include <QTcpSocket>

class QTcpSocket;
class QString;


class ChatClient: public QObject
{
Q_OBJECT
public:
    ChatClient(QObject *parent = 0);
    ~ChatClient();

public slots:
    void startTransfer(QString message);
    void connectTo(QString address, QString port);

private:
    QTcpSocket socket;
};

#endif // CHATCLIENT_H
