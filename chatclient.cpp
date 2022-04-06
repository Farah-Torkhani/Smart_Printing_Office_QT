#include "chatclient.h"
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QByteArray>
#include <iostream>

ChatClient::ChatClient(QObject* parent): QObject(parent)
{

}

ChatClient::~ChatClient()
{
}

void ChatClient::connectTo(QString address, QString port)
{
    if (socket.isOpen()) socket.close();
    std::cout << "Connceting to " << address.toStdString() << std::endl;
    QHostAddress addr(address);
    socket.connectToHost(addr, port.toShort());
}

void ChatClient::startTransfer(QString message)
{
    if (!socket.isValid()) std::cout << "WE HAS PROBLEM, NO CONNECTION!" << std::endl;
    std::cout << "Starting transfer..." << std::endl;
    QByteArray messageArray;
    messageArray.append(message);

    socket.write(messageArray);
}
