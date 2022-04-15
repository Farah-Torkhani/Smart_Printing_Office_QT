#include "chat.h"
#include "ui_chat.h"
#include <QtDebug>

#include <QLabel>
#include "chatservice.h"
#include <QDateTime>
#include "login.h"


Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    connect(ui->btnSendMessage,SIGNAL(clicked()),this,SLOT(click_btnSendMessage()));
    ui->localIP->setText("Your local IP: " + ChatService::getLocalIP());

    QFont font;
    font.setPixelSize(DEFAULT_MESSAGE_FONT_SIZE);
    ui->browserMessage->setFont(font);

    chat = new ChatService;


    connect(chat,SIGNAL(messageShowReady(ChatService::message_t,QString,QString)),
            this,SLOT(showMessage(ChatService::message_t,QString,QString)) );

    connect(chat,SIGNAL(onlineUsersUpdateReady(QSet<QString>)),
            this,SLOT(updateOnlineUsers(QSet<QString>)) );


    click_btnLogin();
}

Chat::~Chat()
{
    chat->sendJson(ChatService::MT_LOGOUT,currentEmp.getNom() +" "+ currentEmp.getPrenom());
    delete ui;
}


void Chat::showMessage(ChatService::message_t type, QString hint, QString content)
{
    QDateTime now = QDateTime::currentDateTime();
    if(type == ChatService::MT_LOGIN || type == ChatService::MT_LOGOUT || type == ChatService::MT_SYSTEM)
    {
        ui->browserMessage->setTextColor(QColor(190,190,190));
        ui->browserMessage->append(hint + now.toString("  hh:mm:ss"));
        ui->browserMessage->append(content);
    }
    else if(type == ChatService::MT_CHAT)
    {
        ui->browserMessage->setTextColor(QColor(70,130,180));
        ui->browserMessage->append(hint + now.toString("  hh:mm:ss"));
        ui->browserMessage->setTextColor(QColor(0,0,0));
        ui->browserMessage->append(content);
    }
}

void Chat::updateOnlineUsers(QSet<QString> set)
{
    ui->listOnlineUser->clear();
    ui->listOnlineUser->insertItem(0,tr("Online Users:"));
    int i = 1;
    for(auto it = set.begin();it!= set.end() ;it++)
        ui->listOnlineUser->insertItem(i++,*it);
}

void Chat::click_btnSendMessage()
{
    chat->setMask("255.255.255.255");
    chat->sendJson(ChatService::MT_CHAT,currentEmp.getNom() +" "+ currentEmp.getPrenom(),ui->edtMessage->toPlainText());
    ui->edtMessage->clear();
}

void Chat::click_btnLogin()
{
    chat->setMask("255.255.255.255");
    chat->sendJson(ChatService::MT_LOGIN,currentEmp.getNom() +" "+ currentEmp.getPrenom());
    chat->setStatus(ChatService::ST_OFFLINE);
    chat->setUserName("nabil mersni");
}

void Chat::click_btnLogout()
{
        //setLocalUserEnable(false);
        //setWidgetState(Remove);

        chat->setMask("255.255.255.255");
        chat->sendJson(ChatService::MT_LOGOUT,currentEmp.getNom() +" "+ currentEmp.getPrenom());
        chat->setStatus(ChatService::ST_OFFLINE);
}

void Chat::reject()
{
    click_btnLogout();
    QDialog::reject();
    this->hide();
}
