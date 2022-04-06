#include "chat.h"
#include "ui_chat.h"
#include <QtDebug>
#include "login.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTimer>
#include <QLabel>
#include "chatclient.h"
#include <QTextEdit>



QVBoxLayout layouttt ;
//QTimer timerRefreshMessList;

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);

    connect(ui->adressIp, SIGNAL(textChanged(QString)), this, SLOT(connectionChange()));
    connect(ui->port, SIGNAL(textChanged(QString)), this, SLOT(connectionChange()));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *testLayout = new QHBoxLayout();


    mainLayout->addLayout(testLayout);
    mainLayout->addWidget(ui->chatBox);

//    setLayout(mainLayout);

    ui->adressIp->setText("127.0.0.1");
    ui->port->setText("12349");

}

Chat::~Chat()
{
    delete ui;
}


void Chat::on_sendMessBtn_clicked()
{
    QString message(ui->messageQline->text());
    emit sendMessage(message);
    ui->chatBox->append("Me: " + message);

}

void Chat::displayNewMessage(QString message, QString sender) {
    QString msg("<b>" + sender + ":</b> ");

    ui->chatBox->append("<b>" + sender + ":</b> "+message);
}

void Chat::connectionChange() {
    emit connectToChanged(ui->adressIp->text(), ui->port->text());
}



















//void Chat::on_sendMessBtn_clicked()
//{
//    qDebug()<< currentEmp.getNom();
//    QString message = ui->lineEdit_3->text();
//    bool test = addMessage(currentEmp.getCin(),message);

//    if(test){
//        ui->lineEdit_3->setText("");
//        refreshMessageList();
//    }else {
//        QMessageBox::critical(nullptr, QObject::tr("message status"),QObject::tr("message not sent.\nClick Cancel to exit."), QMessageBox::Cancel);
//    }
//}

//bool Chat::addMessage(int cin, QString message)
//{
//    QSqlQuery query;
//    query.prepare("INSERT INTO messages (MESSAGEID, messageContent, cin) VALUES (MESSAGEID.nextval, :messageContent, :cin) ");

//    query.bindValue(":messageContent",message);
//    query.bindValue(":cin",cin);
//    return query.exec();
//}

//QSqlQuery Chat::afficherAllMessage()
//{
//    QSqlQuery query;
//    query.exec("select * from messages inner join employees on messages.cin = employees.cin order by DATESEND");
//    return query;
//}

//void Chat::refreshMessageList()
//{
//    while(!layouttt.isEmpty()){
//        QLayoutItem* item = layouttt.itemAt(0);
//        layouttt.removeItem(item);
//        QWidget* widgett = item->widget();
//        if(widgett)
//            {
//                delete widgett;
//            }
//    }

//    QSqlQuery messList = afficherAllMessage();
//    while (messList.next()) {
//        QLabel *l = new QLabel();
//        l->setText(messList.value(5).toString()+" "+messList.value(6).toString()+" :"+messList.value(2).toString() +">>"+ messList.value(1).toString());
//        l->setMinimumHeight(40);
//        layouttt.addWidget( l );
//    }
//}


//void Chat::reject()
//{
//    disconnect(&timerRefreshMessList, SIGNAL(timeout()), this, SLOT(refreshMessageList()));
//    QDialog::reject();
//    this->hide();
//}
