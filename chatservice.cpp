#include "chatservice.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

ChatService::ChatService(QObject *parent) : QObject(parent)
{
    messageSender = new QUdpSocket();
    messageReader = new QUdpSocket();

    messageReader->bind(DEFAULT_MESSAGE_PORT,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint );
    connect(messageReader,SIGNAL(readyRead()),this,SLOT(readAllMessage()));
}


void ChatService::sendJson(message_t type, QString nick_name, QString content)
{
    QJsonObject obj;



    if(type == MT_CHAT)
        obj.insert("type","chat");
    else if(type == MT_LOGIN)
        obj.insert("type","login");
    else if(type == MT_LOGOUT)
        obj.insert("type","logout");
    else if(type == MT_INVOLVE)
        obj.insert("type","involved");


    if( !content.isEmpty() )
        obj.insert("content",content);

    obj.insert("nick-name",nick_name);

    QJsonDocument doc;
    doc.setObject(obj);

    QByteArray data = doc.toJson();

    messageSender->writeDatagram(data.data(),data.size(),QHostAddress(MASK),DEFAULT_MESSAGE_PORT);
}

void ChatService::readAllMessage()
{
    while (messageReader->hasPendingDatagrams())
    {
        QByteArray data;
        data.resize(messageReader->pendingDatagramSize());
        QHostAddress source;
        messageReader->readDatagram(data.data(),data.size(),&source);

        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(data,&jsonError);
        if(jsonError.error == QJsonParseError::NoError && doc.isObject())
        {
            QJsonObject obj = doc.object();
            if(obj.contains("type") && obj.contains("nick-name"))
            {
                QJsonValue type = obj.take("type");
                QString info = obj.take("nick-name").toString() + "(" + ChatService::toIPv4(source.toIPv4Address()) + ")" ;
                if(type.toString() == "chat" && obj.contains("content"))
                {
                    emit messageShowReady(ChatService::MT_CHAT,info,obj.take("content").toString());
                }
                else if(type.toString() == "login")
                {

                    if( !onlineUsersSet.contains(info) )
                        onlineUsersSet.insert(info);
                    if( currentStatusType == ST_ONLINE)
                        sendJson(ChatService::MT_INVOLVE,USER_NAME);
                    emit messageShowReady(ChatService::MT_LOGIN,info,tr(" -- enter the chat room"));
                }
                else if(type.toString() == "logout")
                {

                    if(onlineUsersSet.contains(info))
                        onlineUsersSet.remove(info);
                    emit messageShowReady(ChatService::MT_LOGOUT,info,tr(" -- quit the chat room"));
                }
                else if(type.toString() == "involved")
                {

                    if(!onlineUsersSet.contains(info))
                        onlineUsersSet.insert(info);
                }
            }
            emit onlineUsersUpdateReady(onlineUsersSet);
        }
    }

}


QString ChatService::toIPv4(quint32 arg)
{
    QString res;
    int bits[4],cnt = 0;
    while (arg)
    {
        bits[cnt] = arg % 256;
        arg /= 256;
        cnt++;
    }
    for(int i=3;i>=0;i--)
        res.append(QString::number(bits[i]).append(i==0?"":"."));
    return res;
}

QString ChatService::getLocalIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress in,list)
    {
        if(in.protocol() == QAbstractSocket::IPv4Protocol && in.toString().contains("192.168"))
            return in.toString();
    }
    return QString::null;
}
